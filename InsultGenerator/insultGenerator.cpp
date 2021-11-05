/*
File: insultGenerator.cpp
Author: Logan Copeland
Description: Implementation file for a Shakespearian Insult Generator
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
#include <set>

#include "insultGenerator.h"

using namespace std;

// default null constructor
InsultGenerator::InsultGenerator() {}

void InsultGenerator::initialize() {
    string line;
    string word1, word2, word3;
    ifstream file;
    istringstream ss;

    file.open("InsultsSource.txt");

    // throw exception if file cannot be opened
    if (file.fail()) {
		throw FileException("Unable to read file!");
	}
    
    // read each line from the file and store each word in the associated column vector
    while (!file.eof()) {
        getline(file, line);
        ss.str(line);
        ss >> word1;
        ss >> word2;
        ss >> word3;
        column1.push_back(word1);
        column2.push_back(word2);
        column3.push_back(word3);
        ss.clear();
    }

    file.close();
}

int InsultGenerator::randInt() {
    // generate a seed using steady_clock
    unsigned long long int seed = chrono::steady_clock::now().time_since_epoch().count();
    // use the seed to generate a random number
    default_random_engine engine(seed);
    // map the random number to a uniform distribution between 0 and 49 inclusive
    uniform_int_distribution<int> distribution(0,49);

    return distribution(engine);
}

string InsultGenerator::talkToMe() {
    string insult = "Thou " + column1[randInt()] + " " + column2[randInt()] + " " + column3[randInt()] + "!";

    return insult;
}

vector<string> InsultGenerator::generate(int numInsults) {
    set<string> insultListSet;

    // check that numInsults falls within the acceptable range
    if (numInsults < 1 || numInsults > 10000) {
		throw NumInsultsOutOfBounds("Invalid number of insults!");
	}

    // generate insults and store them in the set insultListSet
    int i = 0;
    while (i < numInsults) {
        string insult = talkToMe();
        
        // check if the generated insult already belongs to the set
        if (insultListSet.find(insult) == insultListSet.end()) {
            insultListSet.insert(insult); // sets store strings alphabetically
            i++; // only increment i when an insult is added to the set
        }
    }

    // copy the set to a vector
    vector<string> insultListVector(insultListSet.begin(), insultListSet.end());

    return insultListVector;
}

void InsultGenerator::generateAndSave(string fileName,int numInsults) {
    vector<string> insultList = generate(numInsults); // generate insults
    ofstream file;

    // open or create file fileName
    file.open(fileName);

    // throw exception if file cannot be written
    if (file.fail()) {
		throw FileException("Unable to write to " + fileName + "!");
	}

    // output insults to file line by line
    for (int i = 0; i < (insultList.size() - 1); i++) {
        file << insultList[i] << endl;
    }
    file << insultList[insultList.size() - 1]; // output the last insult without a newline character

    file.close();
}

FileException::FileException(const string& message) {
    errorMessage = message;
}

string FileException::what() const {
    return errorMessage;
}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) {
    errorMessage = message;
}

string NumInsultsOutOfBounds::what() const {
    return errorMessage;
}