#ifndef _STRATEGIJA_H_
#define _STRATEGIJA_H_

#include<fstream>
#include<iomanip>
#include<stack>
#include<string>
#include<vector>

using namespace std;
//Poslednji ispisani red da bih pamtio dokle sam stigao sa ispisom
static int IDReda = 1;
static int IDTokena = 1;

class Strategija {
public:
	//Za citanje konfiguracije
	virtual void citajKonf(const string&,vector<int>&) {};
	//Za citanje programa
	virtual void citajProg(fstream&,vector<char>&) {}

	//Za odabrani nacin stvaranja .imf fajla.
	virtual void pisi(fstream&,vector<char>&) {};
};

class Program :public Strategija {
public:
	virtual void citajProg(fstream&, vector<char>&) override;
	bool isOperator(const char) const;
	bool isOperand(const char)const;
	int prioritet(const char) const;
	void infixPostfix(fstream&);
	void prepisi(vector<char>&)const;
	void slikaOgledalo(string&);
	void citajOperand(fstream&);
private:
	stack<char> stack_;
	vector<char> postfix_;
};

class Konfiguracija :public Strategija {
public:

	virtual void citajKonf(const string&,vector<int>&) override;
	int citajVrednosti(fstream&) const;
	void citajKasnjenje(fstream&,vector<int>&);

};

static int token = 1;

class NojmanIspis :public Strategija {
public:
	virtual void pisi(fstream&,vector<char>&) override;
	void ispisiPoFormatu(fstream&,char,string&,string&,string&);
	void ispisiStek(string&);
	//void ispisi();
private:
	
	stack<char> stack_; //Stek koji ce mi pomoci da vrsim ispis!!!

};

class ProtocniIspis :public Strategija {
public:

};
#endif//! _STRATEGIJA_H_