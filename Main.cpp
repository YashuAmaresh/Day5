
#include <iostream>
#include "ScrabbleDict.h"
using namespace std;

int main(int argc, char **argv) {
	 if(argc < 2) {
	 cerr << "USAGE " << argv[0] << " DICTFILE" << endl;
	 return -1;
	 }
	string inputFile = argv[1];
	ScrabbleWordFinder wordFinder(inputFile);


	string lettersInHand;
	cout << "Enter your rack: ";
	std::getline (std::cin,lettersInHand);
	string maxScoreWord = wordFinder.getMaxScoreWord(lettersInHand);
	cout << maxScoreWord <<endl;
	return 0;
}
