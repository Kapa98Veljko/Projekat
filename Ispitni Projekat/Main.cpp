#include"Compiler.h"
#include"Machine.h"
#include"Memory.h"
#include"Strategija.h"

int main() {

	//Program treba da se prosledi Prevodiocu koji iscitava .txt i od njega pravi .imif fajl. Ispomoc je to da se od jednacine napravi postfix oblik.
	while (1)
	{
		Compiler* cmp = new Compiler();
		cmp->strategijaCitaj(new Konfiguracija());
		cmp->citaj("config.txt");
		std::cout << "Postojim!!!" << std::endl;
	}
	
	
	
	return 0;
}