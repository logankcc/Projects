/*
File: insultGenerator.h
Author: Logan Copeland
Description: Header file for a Shakespearian Insult Generator
*/

#pragma once

#include <vector>

using namespace std;

class InsultGenerator {
public:
    InsultGenerator();
    void initialize();
    string talkToMe();
    vector<string> generate(int numInsults);
    void generateAndSave(string fileName,int numInsults);

private:
    vector<string> column1, column2, column3;
    int randInt();
};

class FileException {
public:
    FileException(const string& message);
	string what() const;

private:
    string errorMessage;
};

class NumInsultsOutOfBounds {
public:
    NumInsultsOutOfBounds(const string& message);
	string what() const;

private:
    string errorMessage;
};