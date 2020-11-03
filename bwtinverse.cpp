#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::sort;
using std::vector;
using std::size_t;
using std::malloc;

struct BWTLetter {
	char letter; // not strictly neccesary; used for code clarity
	int nextLoc;
	BWTLetter() { letter = '\0', nextLoc=-1;} // only used so array can be instatiated. will be replaced with call to malloc
	BWTLetter(const char letter, int nextLoc) { 
		this->letter = letter;
		this->nextLoc = nextLoc; // either holds number of occurences or next row
	}
};

vector<BWTLetter*> * createLetterLookup(const string & bwt) {
  vector<BWTLetter*> * letterLookup = new vector<BWTLetter*>[26]; 
  int currentLetterIndex; // 0-26
  bool hasVector[26]= { false };
  for (size_t i = 0; i < bwt.size(); ++i) {
	currentLetterIndex = bwt[i] - 65; // A=0, in ASCII A=65 
	if (!(hasVector[currentLetterIndex])) {
		vector<BWTLetter*> * newVector = new vector<BWTLetter*>();
		letterLookup[currentLetterIndex] = *(newVector);
		hasVector[currentLetterIndex] = true; 
	}
  	BWTLetter * newLetter = new BWTLetter(bwt[i], i);
	letterLookup[currentLetterIndex].push_back(newLetter);
  }
  return letterLookup;
}

BWTLetter * createSequentialBWT(const string & bwt) {
	BWTLetter * sequence = (BWTLetter*) malloc(sizeof(BWTLetter)*bwt.size());
	int counter[26] = { 0 };
	for (size_t i = 0; i<bwt.size(); ++i)  {
		sequence[i] = *(new BWTLetter(bwt[i], counter[bwt[i] - 65]));
		counter[bwt[i] - 65]+=1;
	}
	return sequence;
}	
		
string InverseBWT(const string& bwt) {
  size_t bwtSize = bwt.size();
  char * result = new char[bwtSize];
  string sortedBWT = bwt; // makes a copy 
  sort(sortedBWT.begin(), sortedBWT.end());
  vector<BWTLetter*> * letterLookup = createLetterLookup(sortedBWT); 
  BWTLetter * BWTSequence = createSequentialBWT(bwt);
  result[bwtSize - 1] = '$';
  BWTLetter currentBWTLetter; 
  int currentRow = 0;
  for (int i = bwtSize - 2; i >= 0; --i) {
	currentBWTLetter = BWTSequence[currentRow];	
	result[i] = currentBWTLetter.letter;
	currentRow = letterLookup[currentBWTLetter.letter - 65][currentBWTLetter.nextLoc]->nextLoc;
  }	
  delete[] BWTSequence;
  delete[] letterLookup; 
  string text(result);
  delete[] result;
  return text;
}

int main() {
  string bwt="AC$A";
  //cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
