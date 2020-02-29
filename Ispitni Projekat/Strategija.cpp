#include "Strategija.h"
#include<iostream>

void Program::citajProg(const string& ime_fajla,vector<char>& postfiks)
{
	fstream fajl(ime_fajla,ios::in);

	fajl.close();
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

void Konfiguracija::citajKasnjenje(fstream& ulazni_fajl,vector<int>& konfiguracija)
{
	char operacija;
	char t;
    //Citanje operacije i znaka '='
	ulazni_fajl >> operacija>>t;

	int b= citajVrednosti(ulazni_fajl);
	switch (operacija)
	{
	case'a':konfiguracija[2]=b; break;
	case'm':konfiguracija[3] = b; break;
	case'e':konfiguracija[4] = b; break;
	case'w':konfiguracija[5]  = b; break;
	}
}


