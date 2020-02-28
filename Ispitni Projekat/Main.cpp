#include"Compiler.h"
#include"Machine.h"
#include"Memory.h"

int main() {

	//Program treba da se prosledi Prevodiocu koji iscitava .txt i od njega pravi .imif fajl. Ispomoc je to da se od jednacine napravi postfix oblik.

	Compiler* cmp = new Compiler();
	
	bool ima_ime= true;
	 
	while (ima_ime) 
	{
		std::cout << "Unesite ime programa." << endl;
		std::string ime_,ime_txt;
		std::cin >> ime_;
		ime_txt= ime_ + ".txt";

		cmp->obradiProgram(ime_,ime_txt);

		std::cout << "Da li zelite da nastavite? D/N" << endl;
		char provera_;
		std::cin >> provera_;

		ima_ime = false;

		if (provera_ == 'D' || provera_ == 'd')
		{
			ima_ime == true;
		}
		
	}


	delete cmp;
	return 0;
}