
#include "ScrabbleWordFinder.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

constexpr auto SPACE_DELIMITER = " ";

ScrabbleWordFinder::ScrabbleWordFinder(string FileName) {
	initPrimes();
	loadDict(FileName);

}

void ScrabbleWordFinder::initPrimes() {
	int count = 1;
	primes[0] = 2;
	int currNum = 3;
	while (count < NCHAR) {
		bool isPrime = true;
		for (int i = 0; i < count && isPrime; i++) {
			if (currNum % primes[i] == 0) {
				isPrime = false;
			}
		}
		if (isPrime)
			primes[count++] = currNum;
		currNum += 2;
	}
}

void ScrabbleWordFinder::loadDict(string inFile) {
	string word;
	ifstream inputFile(inFile.c_str());
	if (inputFile.is_open()) {
		while (getline(inputFile, word)) {
			unsigned long long hash = getHash(word);
			insertInMap(hash, word);
		}
		inputFile.close();
	} else {
		cerr << "Unable to open file" << endl;
	}
}


unsigned long long int ScrabbleWordFinder::getHashValue(string str) {
	unsigned long long int hashValue = 1;
	for (char c: str) {
		if(isalpha(c))
			hashVal *= primes[toupper(c) - 'A'];
	}
	return hashVal;
}





void ScrabbleWordFinder::insertInMap(unsigned long long key, string value) {
	map<unsigned long long, string>::iterator it;
	it = hashValWordMap.find(key);
	bool hasKey = (it != hashValWordMap.end());
	if (hasKey) {
		it->second = it->second + SPACE_DELIMITER + value;
	} else {
		hashValWordMap.insert(std::pair<unsigned long long, string>(key, value));
	}
}


int ScrabbleWordFinder::calculateScore(string word) {
	int wordScore = 0;
	int scoreArray[] = {1, 2, 4, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	for (char c: word) {
		int index = toupper(c) - 'A';
		wordScore += scoreArray[index];
	}
	return wordScore;
}


string ScrabbleWordFinder::getMaxScoreWord(string IettersInHand){
	int length = lettersInHand.length();

	maxScoreWord.score = 0;
	maxScoreWord.words = "";
	bool present[length];
	processAllSubstrings(lettersInHand,present,0);
        return maxScoreWord.words;
}

void ScrabbleWordFinder::updateMaxScore(string word) {
	unsigned long long int hashVal = 0;
	int wordScore;
	hashVal = getHash(word);
	bool codeExists = hashValWordMap.find(hashVal) != hashValWordMap.end();
	if (codeExists) {
		wordScore = calculateScore(word);
		if (wordScore > maxScoreWord.score) {
			maxScoreWord.score = wordScore;
			maxScoreWord.words = hashValWordMap[hashVal];
		}
	}
}

void ScrabbleWordFinder::printDict(){
	for (map<unsigned long long, string>::iterator mapIterator = hashValWordMap.begin(); mapIterator != hashValWordMap.end(); ++mapIterator) {
		cout << (*mapIterator).second << endl;
	}
}

void ScrabbleWordFinder::processAllSubstrings(string str, bool present[], int index) {
	int length = str.length();
	if( index == length) {
		string word ="";
		for(int i = 0; i < length; i++ ) {
			if(present[i]) word += str[i];
		}
		updateMaxScore(word);
	} else {
		present[index] = true;
		processAllSubstrings(str, present, index+1);
		
		present[index] = false;
		processAllSubstrings(str, present, index+1);
	}
}
