#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::sort;

struct positionHolder { // holds character, and its initial position in the string
	int position;
	char letter;
	positionHolder(char letter, int position) {
		this->position = position;
		this->letter = letter;
	}
	bool operator < (const positionHolder & other) const {
		return letter < other.letter;
	}
};

string BWT(const string& text) { // const forces us to instantiate array to copy string
  // write your code here
  vector<positionHolder> allChars;
  for (int i = 0; i < text.size(); ++i) {
	  positionHolder p(text[i], i);
	  allChars.push_back(p);
  }
  sort(allChars.begin(), allChars.end());
  char * res = new char[text.size()+1];
  res[0] = text[text.size()-1]; // second to last element; always chosen first since $ comes before all
  int nextChar;
  for (int i = 1; i < text.size()+1; ++i) {
  	nextChar = allChars[i-1].position - 1;
	if (nextChar != -1) {
		res[i] = text[nextChar];
	}
	else {
		res[i] = '$';
	}
  }
  string result(res, text.size()+1);
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
