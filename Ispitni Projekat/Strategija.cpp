#include "Strategija.h"
#include<iostream>

void Program::citajProg(fstream& program,vector<char>& postfix)
{
	char dodeli;
	char c;
	//Cita se ona prom. u koju se upise vr. celog izraza sa desne strane.
	program >>dodeli>> c;
	postfix_.push_back(dodeli);
	//Specijalni slucaaj kada je potrebno da se ubaci negacija broja
	if (program.peek() == '-')
	{
		program >> c;
		postfix_.push_back(' ');
		postfix_.push_back(c);
		
	}

	infixPostfix(program);

	//Da ne bih vukao po referenci ja cu na kraju samo izvrsiti prepisivanje iz lokalnog izraza
	prepisi(postfix);
	
}

bool Program::isOperator(const char c) const
{
	if (c == '^' || c == '*' || c == '/' || c == '+' || c == '-')
		return true;
	return false;
}

bool Program::isOperand(const char c) const
{
	if ((c >= 'a' && c <= 'z')|| (c >= 'A' && c <= 'Z')|| (c >= '1' && c <= '9'))
		return true;
	return false;
}

int Program::prioritet(const char c) const
{
	if (stack_.empty())
		return 0;
	else if (c == '(')
		return 4;
	else if (c == '^')
		return 3;
	else if (c == '*' || c=='/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
}

void Program::infixPostfix(fstream& program)
{
	char c;
	char b;
	//Svaki od operanda ce u infix vekotru biti zapisan kao svoja slika u ogledalu.
	//Izmedju svakog od operanadai operator  mora biti jedan ' '.
	
	bool vec_citao = false;
	
	while (program.peek() != '\n')
	{
		if (!vec_citao)
		{
			//Ako se dalje u programu bude nailazilo na opcije koje ne zahtevaju da se cita znak unapred da bi se znao uslov za njihov izlazak!!!
			vec_citao = false;
			program >> c;
		}

		//Ako je operand recimo {A,B,C.. 1,2,3..} samo se stavi u vektor.
		//Medjutim sta ako mi je operand visecifreni broj{X=123+B}? Zbog togo moram da napravim sliku u ogledalu. Takodje moram i da citam sve dok se ne dodje do operatora.
		if (isOperand(c))
		{
			string operand;
			operand += c;
			program >> c;
			vec_citao = true;
			while (program.peek() != '\n' && !(isOperator(c)))
		
				operand += c;
	
		
			slikaOgledalo(operand);
		}
		
		//Ako se u izrazu naidje na ')' potrebno je da se sve sa steka ispise dok se ne naidje na '(', a onda se ona izbrise.
		else if (c == ')')
		{
		    //Treba da mi izmedju svaka dva operatora takodje bude razmak
			while (stack_.top() != '(')
			{
				b = stack_.top();
				postfix_.push_back(' ');
				postfix_.push_back(b);
				stack_.pop();
			}
			stack_.pop();
		}
		
		//Ako se naidje na operator treba da se proveri sledece. Ako je veceg prioriteta
		else if (isOperator(c))
		{
			if (c == '(')
				stack_.push(c);
			else if (stack_.empty())
			{
				stack_.push(c);
			}
			else if (prioritet(c) > prioritet(stack_.top()))
			{
				stack_.push(c);
			}
			else if ( prioritet(c) < prioritet(stack_.top()))
			{
				
				postfix_.push_back(' ');
				postfix_.push_back(stack_.top());
				stack_.pop();
				
				while (!stack_.empty() && prioritet(c) < prioritet(stack_.top())) 
				{
					postfix_.push_back(' ');
					postfix_.push_back(stack_.top());
					stack_.pop();
				}
			}
			else if (prioritet(c) == prioritet(stack_.top()))
			{
				//Asocijativnost. Ako je sleva na desno stampam top() i pop-ujem. Ako je sa desna na levo onda push(){Sto je samo slucaj sa ^}
				if (c == '^')
					stack_.push(c);
				//Asocijativnost je sleva na desno stampam i izbrisem  vrh steka pa dodam novi procitani operator.
				else
				{
					postfix_.push_back(' ');
					postfix_.push_back(stack_.top());
					stack_.pop();
					stack_.push(c);
				}
			}
		
		}
	}
	//Ispisuje sve operatore koji su ostali na stack-u ako ih ima 
	while (!stack_.empty()) 
	{
		c = stack_.top();
		stack_.pop();
		postfix_.push_back(c);
	}
}

void Program::prepisi(vector<char>& postfix) const
{
	//Svrha metode je da prepise ovo jer me mrzi da svud u metodama prenosim ovaj vektor iz Compiler-a, a zbog prava pristupa cu koristiti lokalni za ovu klasu!!!
	
	if (!postfix.empty())
		postfix.clear();
	
	if(!postfix_.empty())
	for (int i = 0; i < postfix_.size(); i++)
		postfix.push_back(postfix_[i]);
	//Znak koji ce mi reci da sam dosao do kraja vektora je znak za dodelu vrednosti '='
	postfix.push_back(' ');
	postfix.push_back('=');
}

void Program::slikaOgledalo(string& operand)
{
	//Hocu da mi se izmedu bilo koja dva da li operanda nalazi razmak ' '.Ali ako je prvi operand koji se upisuje ispred njega mi nije potreban razmak.
	char c;
	if(postfix_.size()!=0 && isOperand(postfix_.back()))
		postfix_.push_back(' ');

	int l = operand.length();
	for (int i = l - 1; i >= 0; i--)
		postfix_.push_back(operand[i]);
}

void Konfiguracija::citajKonf(const string& ime_fajla,vector<int>& konfiguracija)
{
	//*****-------------------------------------------*****
	//TREBA JE RAZBITI NA VISE METODA RADI RAZUMLJIVOSTI!!!!
	fstream konf_fajl(ime_fajla, ios::in);
	while (konf_fajl.peek() != EOF) 
	{
		char t;
		konf_fajl >> t;
		
			if (t == 'T')
			{
				citajKasnjenje(konf_fajl,konfiguracija);
				
			}
			else if (t=='N') 
			{
				konf_fajl >> t>>t;
				konfiguracija.push_back(citajVrednosti(konf_fajl));
				
			}
			else if (t == 'c') 
			{
				bool desno = false,simple=true;
				string kompilacija;

				while (konf_fajl.peek() != EOF) 
				{  
					if (t == '=') desno = true;
					if(!desno)
					    konf_fajl >> t;
					else 
					{
						konf_fajl >> t;
						kompilacija += t;
						if (kompilacija == "advanced")
							simple= false;
					}
				}
				konfiguracija.push_back(int(simple));
			}
			
		
	}
	for (int i = 0; i < 6; i++)
		std::cout << konfiguracija[i];
	std::cout << endl;
	konf_fajl.close();
}

int Konfiguracija::citajVrednosti(fstream& ulazni_fajl) const
{
	string broj;
	char c;
	while (ulazni_fajl.peek() != '\n')
	{
		ulazni_fajl >> c;
		broj += c;
	}
	int vrati = 0;
	int stepen = 1; int l = broj.length();
	for (int i = 0; i < broj.length(); i++) 
	{
		vrati += (broj[l-i-1] - '0')*stepen;
		stepen *= 10;
	}
	return vrati;
}

void Konfiguracija::citajKasnjenje(fstream& ulazni_fajl, vector<int>& konfiguracija)
{
	char operacija;
	char t;
	//Citanje operacije i znaka '='
	ulazni_fajl >> operacija >> t;

	int b = citajVrednosti(ulazni_fajl);
	konfiguracija.push_back(b);
}

static int i = 0;

void NojmanIspis::pisi(fstream& imf, vector<char>& podaci)
{
	//U ovom vektoru se u sledecem formatu naleze podaci --[posl. token u koji se upisuje nesto]'blanko'[Ako je prvi oerand negiran{-}Moze biti, a i nemora]'blanko'[operadni[blanko]operatori[blanko]....]

	i = 0;
	int duzina = podaci.size();

	string dodeli;
	dodeli += podaci[i];

	string prvi, drugi;
	string ne_pisi = "nema tokena";

	while (podaci[i] != '=') 
	{
		if (i == 2 && podaci[i] == '-')
		{
			i = 2;
			while (podaci[i] != ' ')
				stack_.push(podaci[i++]);
			stack_.push('-');
			i++;
		}
		else if (podaci[i] != '+' && podaci[i] != '-' && podaci[i] != '/' && podaci[i] != '^' && podaci[i] != '=') 
		{
			if (!stack_.empty())
				stack_.push(' ');
		
			while (podaci[i] != ' ') 
				stack_.push(podaci[i++]);
			i++;
		}
		else if(podaci[i] != '+' && podaci[i] != '-' && podaci[i] != '/' && podaci[i] != '^')
		{
			char operacija = podaci[i];
			i += 2;
			
			string token = "t";
			token += IDTokena;
			
			ispisiStek(prvi);
			ispisiStek(drugi);
			ispisiPoFormatu(imf,operacija,token,prvi,drugi);
			prvi.clear();
			drugi.clear();

			int l = token.length();
			stack_.push(' ');

			for (int i = l - 1; i >= 0; i--)
				stack_.push(token[i]);
		}

	}
	ispisiStek(drugi);
	ispisiPoFormatu(imf,'=',dodeli,drugi,ne_pisi);

}

void NojmanIspis::ispisiPoFormatu(fstream& fajl, char operacija, string& prviToken, string& drugiToken, string& treciToken)
{
	if (treciToken == "nema tokena")

		fajl << '[' << IDReda << ']' << ' ' << operacija << ' ' << prviToken << ' ' << drugiToken << endl;
	else
		fajl << '[' << IDReda << ']' << ' ' << operacija << ' ' << prviToken << ' ' << drugiToken << ' ' << treciToken << endl;

	IDReda++;
}

void NojmanIspis::ispisiStek(string& token)
{
	while (!stack_.empty() && stack_.top() != ' ')
	{
		token += stack_.top();
		stack_.pop();
	}
	if (!stack_.empty())
		stack_.pop();
}
