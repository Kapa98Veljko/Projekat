#include "Compiler.h"



//void Compiler::infiksPostfiks(fstream& ulazni_fajl)
//{
//
//	while (ulazni_fajl.peek() != '\n') 
//	{
//		char c;
//		//Citanje blanko znaka
//		ulazni_fajl >> c;
//		//Citanje sledeceg ne blanko znaka.
//		ulazni_fajl >> c;
//
//		//Ako se u citanju naidje na operdane ipisi ih u izlazni vektor.
//		if ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
//		{
//			postfix_.push_back(c);
//		}
//		//Ako je znak operand samo ga upisem u vektor znakova.
//
//		//Ako nije onda ovo
//		else if (c=='+' || c=='-' || c=='*' || c=='^') 
//		{
//			//Ako je stek prazan upisi na stek
//			if (stack_.empty())
//			{
//				stack_.push(c);
//			}
//			//Ako nije 
//			else 
//			{   // i operand je manjeg prioriteta od onog na vrhu ispisi sa steka dok ne dodjes  do operanda manjeg prioriteta. 
//				if (veciPrioritet(stack_.top(),c)) 
//				{
//					//Sve dok je prioritet operanda na steku veci uspisuj ono sa steka u vektor.
//					while (veciPrioritet(stack_.top(), c)&& !stack_.empty()) 
//					{
//						postfix_.push_back(stack_.top());
//					}
//					//Upis na stek.
//					stack_.push(c);
//				}
//			}
//		}
//	}
//}

void Compiler::strategijaBiranje(Strategija* strategija)
{
	delete strategija_;
	strategija_= strategija;
}


void Compiler::kompajluj(const string& ime,int tip =0)
{
	
	//tip=0 -config.txt, tip=1 -program.txt
	//Napomena uvek ce se prvo iscitati konfiguracioni fajl.
	int b = tip;
	if (b==0) 
	{
		strategija_->citajKonf(ime+".txt", konfiguracija_);
		
	}
	else 
	{
		//Zelim da stalno menjam strategiju pri citanju programskog fajla.
		//Da se nakon svakog reda citanja izvrsi ipis u .imf fajl u zavisnosti sta se nalazi u tom redu programskog fajla.
		
		int kompilacija = konfiguracija_[0];
	
		//Napomena 0=advanced a=simple
		//Shodno tome se zove strategija koja ce izvrsiti stvaranje .imf fajla.

		if (kompilacija == 0)
			ispisiImfAdvanced(ime);

		else if (kompilacija == 1)
			ispisiImfSimple(ime);
	}

	
}

void Compiler::ispisiImfSimple(const string& ime)
{
	fstream program(ime + ".txt", ios::in);
	
	
	while (program.peek() != EOF) 
	{
		//Za svaki red koji se procita treba da se izvrsi ispis u imf fajl.
		strategijaBiranje(new Program());
		strategija_->citajProg(program,postfix_);
		strategijaBiranje(new NojmanIspis());
		strategija_->pisi(ime);
	}

	program.close();

}

void Compiler::ispisiImfAdvanced(const string& ime)
{
	fstream fajl(ime + ".txt", ios::in);
	fstream program(ime + ".imf", ios::out);
	fajl.close();
	program.close();
}


