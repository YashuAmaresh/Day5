/*
 * ScrabbleDict.h
 *
 *  Created on: Jul 23, 2015
 *      Author: test
 */


#ifndef SCRABBLEDICT_H_
#define SCRABBLEDICT_H_

#include <string>
#include <map>
using namespace std;

const int NCHAR = 26;

class ScrabbleDict {
	int primes[NCHAR];
	int alphaWeight[NCHAR];
	map<unsigned long long, string> primeAnagram;

	void insertInMap(unsigned long long key, string value);
	void loadDict(string inFile);
	void initPrimes();

	void updateMaxScore(string word) ;
	void processAllSubstrings(string str, bool present[],int index);

	void handleBlank(string word, string addedChars);

	struct {
		string words;
		int score;
	} maxScoreWord;


public:
	ScrabbleDict(string FileName);
	void printDict();
	int calculateScore(string word);
	unsigned long long int getHash(string str);
	string getMaxScoreWord(string charsInHand);

};

#endif /* SCRABBLEDICT_H_ */
