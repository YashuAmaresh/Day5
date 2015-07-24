//============================================================================
// Name        : Scrabble.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ScrabbleDict.h"


using namespace std;

int main(int argc, char **argv) {
	 if(argc < 2) {
	 cerr << "USAGE " << argv[0] << " DICTFILE" << endl;
	 return -1;
	 }
	string inputFile = argv[1];
	ScrabbleDict scrabbledict(inputFile);


	string charsInHand;
	cout << "Enter your rack: ";
	std::getline (std::cin,charsInHand);
	string validWord = scrabbledict.getMaxScoreWord(charsInHand);
	cout << validWord <<endl;
	return 0;
}
