#ifndef _STRATEGIJA_H_
#define _STRATEGIJA_H_

#include<fstream>
#include<iomanip>
#include<string>

using namespace std;
class Strategija {
public:
	virtual void citaj(const string&) {};
	virtual void pisi() const {};
};

class Program :public Strategija {
public:
	virtual void citaj(const string&) override;

};

class Konfiguracija :public Strategija {
public:

	//Sada Masina moze da pristupi privatnim poljima.
	//friend class Machine;

	virtual void citaj(const string&) override;
	int citajVrednosti(fstream&) const;
	void citajKasnjenje(fstream&);
	void citajParalUpise(fstream&);

private:
	//Kasnjenja
	int ta_ = 0;
	int tm_ = 0;
	int tw_ = 0;
	int te_ = 0;
	//Kompilacija
	bool simple_ = true;
	//Paralelni upisi
	int nw_ = 0;
};

class KlasicanIspis :public Strategija {
public:
	virtual void pisi()const override;
};

class NapredanIspis :public Strategija {
public:
	virtual void pisi()const override;
};
#endif//! _STRATEGIJA_H_