/*
 * ScrabbleDict.cpp
 *
 *  Created on: Jul 23, 2015
 *      Author: test
 */

#include "ScrabbleDict.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

constexpr auto SPACE_DELIMITER = " ";
constexpr auto BLANK = " ";

ScrabbleDict::ScrabbleDict(string FileName) {
	initPrimes();
	loadDict(FileName);

}

unsigned long long int ScrabbleDict::getHash(string str) {
	unsigned long long int hash = 1;
	for (char c: str) {
		if(isalpha(c))
			hash *= primes[toupper(c) - 'A'];
	}
	return hash;
}


void ScrabbleDict::initPrimes(){
	int count = 1;
	primes[0] = 2;
	int curNum = 3;
	while (count < NCHAR) {
		bool isPrime = true;
		for (int i = 0; i < count && isPrime; i++) {
			if (curNum % primes[i] == 0) {
				isPrime = false;
			}
		}
		if (isPrime)
			primes[count++] = curNum;
		curNum += 2;
	}
}

void ScrabbleDict::loadDict(string inFile) {
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



void ScrabbleDict::insertInMap(unsigned long long key, string value) {
	map<unsigned long long, string>::iterator it;
	it = primeAnagram.find(key);
	bool hasKey = (it != primeAnagram.end());
	if (hasKey) {
		it->second = it->second + SPACE_DELIMITER + value;
	} else {
		primeAnagram.insert(std::pair<unsigned long long, string>(key, value));
	}
}


int ScrabbleDict::calculateScore(string word) {
	int wordScore = 0;
	int scoreArray[] = {1, 2, 4, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	for (char c: word) {
		int index = toupper(c) - 'A';
		wordScore += scoreArray[index];
	}
	return wordScore;
}


string ScrabbleDict::getMaxScoreWord(string charsInHand){
	int length = charsInHand.length();

	maxScoreWord.score = 0;
	maxScoreWord.words = "";
	bool present[length];

	processAllSubstrings(charsInHand,present,0);

	int index = maxScoreWord.words.find(SPACE_DELIMITER);

	if ( index == string::npos) {
		return maxScoreWord.words;
	} else {
		return maxScoreWord.words.substr(0,index);
	}
}

void ScrabbleDict::updateMaxScore(string word) {
	unsigned long long int hashVal = 0;
	int wordScore;
	hashVal = getHash(word);
	bool codeExists = primeAnagram.find(hashVal) != primeAnagram.end();
	if (codeExists) {
		wordScore = calculateScore(word);
		if (wordScore > maxScoreWord.score) {
			maxScoreWord.score = wordScore;
			maxScoreWord.words = primeAnagram[hashVal];
		}
		return;
	}
	if(word.find(BLANK) != string::npos) {
		//cout<<word<<word.find(BLANK)<<" "<<string::npos<<endl;
		string addedChars="";
		handleBlank(word,addedChars);
	}
}

void ScrabbleDict::handleBlank(string word, string addedChars) {
	int pos = word.find(BLANK);

	if (pos == string::npos)
		return;

	int wordScore;
	string current = word;
	word[pos] = '-';

	for(char c ='a'; c <= 'z'; c++) {
		unsigned long long int hashVal = getHash(word+c);
		bool codeExists = primeAnagram.find(hashVal) != primeAnagram.end();
		if (codeExists) {
			wordScore = calculateScore(word) - calculateScore(addedChars);
			if (wordScore > maxScoreWord.score) {
				maxScoreWord.score = wordScore;
				maxScoreWord.words = primeAnagram[hashVal];
			}
		} else {
			handleBlank(word,addedChars+c);

			//cout<<word<<addedChars+c<<endl;
		}
	}

}

void ScrabbleDict::printDict(){
	ofstream outFile("out.txt");
	for (map<unsigned long long, string>::iterator ii = primeAnagram.begin(); ii != primeAnagram.end(); ++ii) {
	    string s=(*ii).second;
		outFile << s << endl;
	}
	outFile.close();
}

void ScrabbleDict::processAllSubstrings(string str, bool present[],int index) {
	int length = str.length();
	if( index == length) {
		string word ="";
		for(int i = 0; i < length; i++ ) {
			if(present[i]) word += str[i];
		}
		updateMaxScore(word);
	} else {
		present[index] = true;
		processAllSubstrings(str,present,index+1);
		
		present[index] = false;
		processAllSubstrings(str,present,index+1);
	}
}
