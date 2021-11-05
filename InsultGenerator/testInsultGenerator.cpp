/*
 * TestInsultGenerator.cpp
 *
 *      Author: Alan McLeod
 *      A testing program for CISC320 assignment 1.
 */

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "insultGenerator.h"

using namespace std;

int main() {

	InsultGenerator ig;
	vector<string> insults;
	clock_t start=0, finish=0;

	// load all the source phrases from the InsultsSource.txt
	try {
		ig.initialize();
	} catch (FileException& e) {
		cerr << e.what() << endl;
		return 1;
	}

	// generate 1000 insults and save them to SavedInsults.txt
	try {
		ig.generateAndSave("SavedInsults.txt", 1000);
	} catch (FileException& e) {
		cerr << e.what() << endl;
		return 1;
	}
	cout << "\nGenerated and saved 1000 insults to SavedInsults.txt" << endl;

	// test efficiency
	try {
		start = clock();
		insults = ig.generate(10000);
		finish = clock();
	} catch (NumInsultsOutOfBounds& e) {
		cerr << e.what() << endl;
	}
	cout << "\n" << insults.size() << " insults generated" << endl;
	cout << (1e3 * (finish - start)/CLOCKS_PER_SEC) << " ms to complete\n" << endl;

	return 0;

}
