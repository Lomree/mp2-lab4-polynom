#include "Polynom.h"
#include <string>
#include <cmath>

Monom::Monom(const Monom& copyMonom) :
	coeff(copyMonom.coeff), power(copyMonom.power) {}

Monom::Monom(std::string Coeff, std::string Power)
{
	coeff = stod(Coeff);
	power = stoi(Power);
}

Monom::Monom(double Coeff, int Power)
{
	coeff = Coeff;
	power = Power;
}

Monom Monom::operator+(const Monom& right)
{
	Monom temp = *this;
	temp.setCoeff(coeff + right.coeff);
	return temp;
}

Monom Monom::operator-(const Monom& right)
{
	Monom temp = *this;
	temp.setCoeff(coeff - right.coeff);
	return temp;
}

Monom Monom::operator*(const Monom& right)
{
	Monom temp = *this;
	temp.setCoeff(coeff * right.coeff);
	temp.setPower(power + right.power);
	return temp;
}

bool operator==(const Monom& leftMon, const Monom& rightMon)
{
	if (leftMon.coeff == rightMon.coeff && leftMon.power == rightMon.power)
		return true;
	return false;
}

Polynom::Polynom(const Polynom& copyPol) :
	size(copyPol.size), data(copyPol.data) {}

Polynom& Polynom::operator=(const Polynom& copyPol)
{
	if (this == &copyPol)
		return *this;
	size = copyPol.size;
	data = copyPol.data;
	return *this;
}

Polynom Polynom::operator+(const Polynom& right)
{
	Polynom temp = *this;
	bool* isRightMonomUsed = new bool[right.size - 1];
	for (int i = 0; i < right.size; i++)
		isRightMonomUsed[i] = 0;
	for (int i = 0; i < temp.size; i++)
	{
		int power = temp.data.getElement(i).getPower();
		for (int j = 0; j < right.size; j++)
			if (right.data.getElement(j).getPower() == power)
			{
				temp.data.changeElement(i, temp.data.getElement(i) + right.data.getElement(j));
				isRightMonomUsed[j] = 1;
				break;
			}
	}
	for (int i = 0; i < right.size; i++)
		if (isRightMonomUsed[i] == 0)
			temp.addMonom(right.returnMonom(i));
	return temp;
}

Polynom Polynom::operator-(const Polynom& right)
{
	Polynom temp = *this;
	bool* isRightMonomUsed = new bool[right.size - 1];
	for (int i = 0; i < right.size; i++)
		isRightMonomUsed[i] = 0;
	for (int i = 0; i < temp.size; i++)
	{
		int power = temp.data.getElement(i).getPower();
		for (int j = 0; j < right.size; j++)
			if (right.data.getElement(j).getPower() == power)
			{
				temp.data.changeElement(i, temp.data.getElement(i) - right.data.getElement(j));
				isRightMonomUsed[j] = 1;
				break;
			}
	}
	for (int i = 0; i < right.size; i++)
		if (isRightMonomUsed[i] == 0)
		{
			Monom temp2 = right.returnMonom(i);
			temp2.setCoeff(-temp2.getCoeff());
			temp.addMonom(temp2);
		}
	return temp;
}



Polynom Polynom::operator*(const Polynom& right)
{
	Polynom temp;
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < right.size; j++)
			temp.addMonom(this->returnMonom(i) * right.returnMonom(j));
	
	Polynom tmp;
	for (int i = 0; i < temp.getSize(); i++) {
		double k = temp.returnMonom(i).getCoeff();
		for (int j = i + 1; j < temp.getSize(); j++) {
			if (temp.returnMonom(i).getPower() == temp.returnMonom(j).getPower()) {
				k += temp.returnMonom(j).getCoeff();
			}
		}
		Monom p(k, temp.returnMonom(i).getPower());
		tmp.addMonom(p);
		//if (tmp.getSize() == 0) {
		//	tmp.addMonom(p);
		//}
		//else {
		//	int flag = 0;
		//	for (int h = 0; h < tmp.getSize(); h++) {
		//		if (temp.returnMonom(i).getPower() == tmp.returnMonom(h).getPower()) {
		//			flag = 1;
		//		}
		//	}
		//	if (flag == 0) {
		//		tmp.addMonom(p);
		//	}
		//}
	}

	Polynom trmp;
	trmp.addMonom(tmp.returnMonom(0));
	for (int i = 1; i < tmp.getSize(); i++) {
		int flag = 0;
		for (int j = 0; j < trmp.getSize(); j++) {
			if (tmp.returnMonom(i).getPower() == trmp.returnMonom(j).getPower()) {
				flag = 1;
			}
		}
		if (flag == 0) {
			trmp.addMonom(tmp.returnMonom(i));
		}
	}

	return trmp;
}

double Polynom::calculate(int x)
{
	double result = 0;
	for (int i = 0; i < size; i++)
		result += data.getElement(i).getCoeff() * pow(x, data.getElement(i).getPower());
	return result;
}

void Polynom::setPol(std::string pol)
{
	int i = 0;
	while (i < pol.size())
	{
		std::string coeff = "";
		std::string power = "";
		while (pol[i] != '*')
			coeff += pol[i++];
		i += 3;
		while ((pol[i] != '+' && pol[i] != '-') && i != pol.size())
			power += pol[i++];
		data.push_back(Monom(coeff, power));
		size++;
	}
}

Monom Polynom::returnMonom(int index) const
{
	if (index < 0 || index >= getSize())
		throw("Wrong index");
	return Monom(data.getElement(index).getCoeff(), data.getElement(index).getPower());
}

void Polynom::addMonom(Monom mon)
{
	data.push_back(mon);
	size++;
}

std::istream& operator>>(std::istream& in, Polynom& obj)
{
	std::string pol;
	in >> pol;
	int i = 0;
	while (i < pol.size())
	{
		std::string coeff = "";
		std::string power = "";
		while (pol[i] != '*')
			coeff += pol[i++];
		i += 3;
		while ((pol[i] != '+' && pol[i] != '-') && i != pol.size())
			power += pol[i++];
		obj.data.push_back(Monom(coeff, power));
		obj.size++;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Polynom& obj)
{
	int flag = 0;
	for (int i = 0; i < obj.size; i++)
	{
		if (obj.data.getElement(i).getCoeff() != 0) {
			out << obj.data.getElement(i).getCoeff() << "*x^"
				<< obj.data.getElement(i).getPower();
			flag = 1;

			if (i != obj.size - 1 && obj.data.getElement(i + 1).getCoeff() >= 0)
				out << "+";
		}
	}
	if (flag == 0) {
		out << "0";
	}
	return out;
}
