#include "Compiler.h"

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
		IDReda = 1;
	}
	else 
	{
		//Zelim da stalno menjam strategiju pri citanju programskog fajla.
		//Da se nakon svakog reda citanja izvrsi ipis u .imf fajl u zavisnosti sta se nalazi u tom redu programskog fajla.
		
		int kompilacija = konfiguracija_[5];
	
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
		strategija_->pisi(ime,postfix_);
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


