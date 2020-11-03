#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;
using std::pair;

typedef map<char, int> edges;
typedef vector<edges> trie;


trie build_trie(vector<string> & patterns) {
	trie t;
  // write your code here
	edges rootNode;
	t.push_back(rootNode);
	int currentNode = 0, currentIndex=0; // current index is for adding edges
	string currentPattern;
	edges::iterator prefix; // for use in searching map
 	for (auto iter = patterns.begin(); iter != patterns.end(); ++iter) {
		currentPattern=*iter;
		currentNode=0;
		for (char & c: currentPattern) {
			prefix = t[currentNode].find(c);
			if (prefix != t[currentNode].end()) {
				currentNode = prefix->second; // should be position in vector trie of hit
			}
			else {
				++currentIndex;
				t[currentNode].insert(pair<char, int>(c, currentIndex));
				edges newEdge;
				t.push_back(newEdge);
				currentNode = currentIndex;
			}
		}
	}
	return t;
}


int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
  
}
