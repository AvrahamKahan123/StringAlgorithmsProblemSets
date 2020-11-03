#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>


using std::cout;
using std::endl;
using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;
using std::sort;

vector<char> * getAllChars(const string & bwt) {
	vector<char> * allChars = new vector<char>();
	bool containsChar[26] = { 0 };

	for (const char & c: bwt) {
		if (c == '$') {
			continue;
		}
		containsChar[c - 65] = 1;
	}	
	for (int i = 0; i < 26; ++i) {
		if (containsChar[i]) {
			allChars->push_back(i+65);
		}
	}
	return allChars;
}

void fillOccCount(map<char, vector<int> > & occ_count_before, const vector<char> * allChars, size_t bwtSize) {

	for (const char & c: *(allChars)) {
		vector<int> * newVector = new vector<int>;
		occ_count_before.insert({c, *(newVector)}); 
		for (size_t i = 0; i < bwtSize; ++i) {
			occ_count_before[c].push_back(0);
		}
	}
}

void fillNextColumn(map<char, vector<int> > & occ_count_before, vector<char> * allChars, int column) {
	for (const char & c: *(allChars)) {
		occ_count_before[c][column] = occ_count_before[c][column-1];
	}
}
void calcOccCount(map<char, vector<int> > & occ_count_before, const string & bwt) {

	vector<char> * allChars = getAllChars(bwt);
	fillOccCount(occ_count_before, allChars, bwt.size());
	occ_count_before[bwt[0]][0] = 1;
	for (size_t i = 1; i < bwt.size(); ++i) {
		fillNextColumn(occ_count_before, allChars, i);	
		if (bwt[i] != '$') {
			occ_count_before[bwt[i]][i]+=1;
		}
	}
}

void calcStarts(map<char, int>& starts, const string & bwt) {
	map<char, int>::iterator hit; //searches map if char already exists
	for (size_t i = 0; i < bwt.size(); ++i) {
		hit = starts.find(bwt[i]);
		if (hit == starts.end()) {
			starts.insert({bwt[i], i});
		}
	}
}	

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
	string bwtSorted = bwt;
	sort(bwtSorted.begin(), bwtSorted.end());
	calcStarts(starts, bwtSorted);  
	calcOccCount(occ_count_before, bwt);
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const map<char, int>& starts, 
                     const map<char, vector<int> >& occ_count_before) {
  int top = 0;
  int bottom = bwt.size()-2;
  int patternIndex = pattern.size()-1;
  char c;
  while (top<=bottom) {
	 if (patternIndex >= 0) {
		 
		c=pattern[patternIndex];
		--patternIndex;
//		cout << "starts at: " << starts.at(c) << " occ_count_before: " << occ_count_before.at(c)[bottom+1] << " occc top " << occ_count_before.at(c)[top];
		top = starts.at(c) + occ_count_before.at(c)[top];
		bottom = starts.at(c) + occ_count_before.at(c)[bottom+1]-1;
		//top = starts[c] + occ_count_before[c][top];
//		bottom = starts[c] + occ_count_before[c][bottom+1]-1;
	 }
	 else {
		 return bottom-top+1;
	 }
  }
  return 0; 
}
     

int main() {
 string A = "SPNMBNNAAAAA$A";
 map<char, int> starts;
 map<char, vector<int> > occ_count_before;
 PreprocessBWT(A, starts, occ_count_before);
 cout << CountOccurrences("ANA", A, starts, occ_count_before) << endl;
 
	/*
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
  */
}
