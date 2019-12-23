#pragma once
#include "List.h"
#include <iostream>
#include <string>

using namespace std;

class Monom
{
public:
	Monom(const Monom& copyMonom);
	Monom(string Coeff, string Power);
	Monom(double Coeff, int Power);
	friend bool operator==(const Monom&, const Monom&);
	Monom operator+(const Monom& right);
	Monom operator-(const Monom& right);
	Monom operator*(const Monom& right);
	double getCoeff() const { return coeff; }
	int getPower() const { return power; }
	void setCoeff(double Coeff) { coeff = Coeff; }
	void setPower(int Power) { power = Power; }
private:
	double coeff;
	int power;
};


class Polynom
{
public:
	Polynom(const Polynom& copyPol);
	Polynom() : size(0) {}
	friend istream& operator>> (istream& in, Polynom& obj);
	friend ostream& operator<< (ostream& out, const Polynom& obj);
	Polynom& operator=(const Polynom&);
	Polynom operator+(const Polynom& right);
	Polynom operator-(const Polynom& right);
	Polynom operator*(const Polynom& right);
	double calculate(int x);
	int getSize() const { return size; }
	void setPol(string pol);
	Monom returnMonom(int index) const;
private:
	List<Monom> data;
	int size;
	void addMonom(Monom);
};

