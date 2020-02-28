#ifndef __COMPILER_H_
#define __COMPILER_H_

#include<fstream>
#include<iomanip>
#include<iostream>
#include<stack>
#include<string>
#include<vector>

using namespace std;

class Compiler {

public:

	Compiler()=default;

	void obradiProgram(const string&,const string&);
	void napraviIme(const string&);
	void infiksPostfiks(fstream&);
	bool veciPrioritet(char,char) const;
	int prioritet(char) const;
	void ispisiPostfiks(const fstream&)const;

protected:
	//Moguca protected sekcija
private:

	//Postfix oblik izraza se cuva kao niz znakova.
	vector<char> postfix_izraz_;
	//Stack koji ce mi posluziti za prebacivanje izraza u njegov postiksni ekvivalent.
	stack<char> stack_;
	//Ime izlaznog imf fajla.
	string novo_ime_;
};

#endif // ! __COMPILER_H_