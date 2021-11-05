/*
File: testFractionCalculator
Author: Logan Copeland
Description: Test file for fractionCalculator.cpp
*/

#include <iostream>
using namespace std;

#include "fractionCalculator.h"

int main() {
	
	Fraction sum(0);
	Fraction fin;
	cout << "\nSumming fractions..." << endl;
	cout << "Enter fractions as \"x/y\" or a single integer." << endl;
	cout << "Enter zero to end the sum.\n" << endl;
	do {
		cout << "Enter a fraction to add to the sum: ";
		try {
			cin >> fin;
			sum += fin;
		} catch (FractionException &e) {
			cout << e.what() << endl;
		}
	} while (fin != 0);
	cout << "Sum is: " << sum << "\n" << endl;

	return 0;

}
