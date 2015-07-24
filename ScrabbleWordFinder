

#ifndef SCRABBLE_WORD_FINDER_H_
#define SCRABBLE_WORD_FINDER_H_

#include <string>
#include <map>
using namespace std;

const int NCHAR = 26;

class ScrabbleWordFinder {
	int primes[NCHAR];
	int alphaWeight[NCHAR];
	map<unsigned long long, string> hashValWordMap;

	void insertInMap(unsigned long long key, string value);
	void loadDict(string inFile);
	void initPrimes();

	void updateMaxScore(string word) ;
	void processAllSubstrings(string str, bool present[],int index);


	struct {
		string words;
		int score;
	} maxScoreWord;


public:
	ScrabbleWordFinder(string FileName);
	void printDict();
	int calculateScore(string word);
	unsigned long long int getHash(string str);
	string getMaxScoreWord(string charsInHand);

};

#endif 
