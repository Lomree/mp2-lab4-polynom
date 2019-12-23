#include <iostream>
#include "Polynom.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Format: 1*x^2+1.5*x^0\n";
	Polynom pol1;
	cout << "¬ведите первый полином:\n";
	cin >> pol1;
	Polynom pol2;
	cout << "¬ведите второй полином:\n";
	cin >> pol2;
	cout << "Enter x:\n";
	double x;
	cin >> x;
	cout << "—умма: " << pol1 + pol2;
	cout << "\nDifference: " << pol1 - pol2;
	cout << "\nMultiply: " << pol1 * pol2;
	cout << "\nPolynom1(x) = " << pol1.calculate(x);
	cout << "\nPolynom2(x) = " << pol2.calculate(x) << "\n";
	system("pause");
}