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

class Strategija {
public:
	//Za citanje konfiguracije
	virtual void citajKonf(const string&,vector<int>&) {};
	//Za citanje programa
	virtual void citajProg(fstream&,vector<char>&) {}

	//Za odabrani nacin stvaranja .imf fajla.
	virtual void pisi(const string&) const {};
};

class Program :public Strategija {
public:
	virtual void citajProg(fstream&, vector<char>&) override;
	bool isOperator(char) const;
	bool isOperand(char)const;
	int prioritet(char) const;
	void infixPostfix(vector<char>&,fstream&);
private:
	stack<char> stack_;
};

class Konfiguracija :public Strategija {
public:

	virtual void citajKonf(const string&,vector<int>&) override;
	int citajVrednosti(fstream&) const;
	void citajKasnjenje(fstream&,vector<int>&);

};

class NojmanIspis :public Strategija {
public:
	virtual void pisi(const string&) const override;
private:

};

class ProtocniIspis :public Strategija {
public:

};

#endif//! _STRATEGIJA_H_