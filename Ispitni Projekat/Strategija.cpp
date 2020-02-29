#include "Strategija.h"
#include<iostream>
void Program::citaj(const string& ime_fajla)
{
	fstream program(ime_fajla,ios::in);

	program.close();
}

void Konfiguracija::citaj(const string& ime_fajla)
{
	fstream konf_fajl(ime_fajla, ios::in);
	while (konf_fajl.peek() != EOF) 
	{
		char t;
		konf_fajl >> t;
		
			if (t == 'T')
			{
				citajKasnjenje(konf_fajl);
				
			}
			else if (t=='N') 
			{
				citajParalUpise(konf_fajl);
			}
			else if (t == 'c') 
			{
				bool desno = false;
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
							simple_ = false;
					}
				}
			
			}
			
		
	}

	std::cout << ta_ << ' ' << tm_ << ' ' << te_ << ' '<<tw_<<' ' <<nw_<<' '<<int(simple_)<< endl;
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

void Konfiguracija::citajKasnjenje(fstream& ulazni_fajl)
{
	char operacija;
	ulazni_fajl >> operacija;
	char t;
	
	ulazni_fajl >> t;
	int b= citajVrednosti(ulazni_fajl);
	switch (operacija)
	{
	case'a':ta_ = b; break;
	case'm':tm_ = b; break;
	case'e':te_ = b; break;
	case'w':tw_ = b; break;
	}
}

void Konfiguracija::citajParalUpise(fstream& fajl)
{
	char t;
	fajl >> t;
	fajl >> t;
	nw_=citajVrednosti(fajl);
}

void KlasicanIspis::pisi() const
{
}

void NapredanIspis::pisi() const
{
}
