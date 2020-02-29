#ifndef _STRATEGIJA_H_
#define _STRATEGIJA_H_

#include<fstream>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;

class Strategija {
public:
	//Za citanje konfiguracije
	virtual void citajKonf(const string&,vector<int>&) {};
	//Za citanje programa
	virtual void citajProg(const string&,vector<char>&) {}

	//Za odabrani nacin stvaranja .imf fajla.
	virtual void pisi() const {};
};

class Program :public Strategija {
public:
	virtual void citajProg(const string&,vector<char>&) override;

};

class Konfiguracija :public Strategija {
public:

	virtual void citajKonf(const string&,vector<int>&) override;
	int citajVrednosti(fstream&) const;
	void citajKasnjenje(fstream&,vector<int>&);

};

class NojmanIspis :public Strategija {
public:
	virtual void pisi() const override;
};

class ProtocniIspis :public Strategija {
public:

};

#endif//! _STRATEGIJA_H_