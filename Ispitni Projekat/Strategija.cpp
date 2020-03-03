#include "Strategija.h"
#include<iostream>

void Program::citajProg(fstream& program,vector<char>& postfix)
{
	char dodeli;
	char c;
	//Cita se ona prom. u koju se upise vr. celog izraza sa desne strane.
	program >>dodeli>> c;

	postfix.push_back(dodeli);
	postfix.push_back(c);

	while (program.peek() != '\n')
	{
		program >> c;
		infixPostfix(postfix,c);
	}
}

bool Program::isOperator(char c)
{
	if (c == '^' || c == '*' || c == '/' || c == '+' || c == '-')
		return true;
	return false;
}

bool Program::isOperand(char c)
{
	if ((c >= 'a' && c <= 'z')|| (c >= 'A' && c <= 'Z')|| (c >= '1' && c <= '9'))
		return true;
	return false;
}

int Program::prioritet(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c=='/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
}

char Program::infixPostfix(vector<char>& postfix,char c)
{
	if (isOperand(c))
		postfix.push_back(c);
	else if (isOperator(c)) 
	{
		if (!stack_.empty())
			stack_.push(c);
	}
}

void Konfiguracija::citajKonf(const string& ime_fajla,vector<int>& konfiguracija)
{
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
				konfiguracija[1] = citajVrednosti(konf_fajl);
				
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

							konfiguracija[0] = int(simple);
					}
				}
			
			}
			
		
	}
	
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

void NojmanIspis::pisi(const string& ime) const
{
	fstream imf(ime+".imf",ios::out);

	imf.close();
}
