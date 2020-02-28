#include "Compiler.h"

void Compiler::obradiProgram(const string& ime_,const string& ime_txt)
{
	//Otvaranje fajla i iscitavanje.
	fstream ulazni_fajl_(ime_txt,ios::in);

	napraviIme(ime_);

	//Otvaranje fajla za upis.
	fstream izlazni_fajl_(novo_ime_, ios::out);

	while (ulazni_fajl_.peek()!=EOF) 
	{
		int i = 1;
		char dodeli_vrednost_;
		char jednako_;

		ulazni_fajl_ >> dodeli_vrednost_;
		ulazni_fajl_ >> jednako_;

		//Prebacivanje iz infiks u postiks oblik izraza.
		infiksPostfiks(ulazni_fajl_);

		ispisiPostfiks(ulazni_fajl_);


	} 

	//Zatvaranje fajlova.
	ulazni_fajl_.close();
	izlazni_fajl_.close();

}

//Stvara se izlazni fajl na osnovu imena ulaznog fajla.
void Compiler::napraviIme(const string& ime)
{
	novo_ime_ = ime + ".imf";
	
}

void Compiler::infiksPostfiks(fstream& ulazni_fajl)
{

	while (ulazni_fajl.peek() != '\n') 
	{
		char c;
		//Citanje blanko znaka
		ulazni_fajl >> c;
		//Citanje sledeceg ne blanko znaka.
		ulazni_fajl >> c;

		//Ako se u citanju naidje na operdane ipisi ih u izlazni vektor.
		if ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
		{
			postfix_izraz_.push_back(c);
		}
		//Ako je znak operand samo ga upisem u vektor znakova.

		//Ako nije onda ovo
		else if (c=='+' || c=='-' || c=='*' || c=='^') 
		{
			//Ako je stek prazan upisi na stek
			if (stack_.empty())
			{
				stack_.push(c);
			}
			//Ako nije 
			else 
			{   // i operand je manjeg prioriteta od onog na vrhu ispisi sa steka dok ne dodjes  do operanda manjeg prioriteta. 
				if (veciPrioritet(stack_.top(),c)) 
				{
					//Sve dok je prioritet operanda na steku veci uspisuj ono sa steka u vektor.
					while (veciPrioritet(stack_.top(), c)&& !stack_.empty()) 
					{
						postfix_izraz_.push_back(stack_.top());
					}
					//Upis na stek.
					stack_.push(c);
				}
			}
		}
	}
}

bool Compiler::veciPrioritet(char c1, char c2) const
{
	int t1 = prioritet(c1);
	int t2 = prioritet(c1);

	if (t1 >= t2) return true;

	return false;
	
}

int Compiler::prioritet(char c) const
{
	switch (c) 
	{
	case'^':return 3; break;
	case'*':return 2; break;
	case'/':return 2; break;
	case'+':return 1; break;
	case'-':return 1; break;
	}
}

void Compiler::ispisiPostfiks(const fstream& izlazni_fajl) const
{
	int l = postfix_izraz_.size();
	for (int i = 0; i < l; i++)
		std::cout<<postfix_izraz_[i];
}
