#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool isLeaf;
	Node ()
	{
		fill (next, next + Letters, NA);
		isLeaf = false;
	}


};


typedef vector<Node> trie;

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

trie build_trie(const vector<string>& patterns) {
	trie result;
	Node headNode;
	result.push_back(headNode);
	int currentNode = 0, currentIndex = 0, letterIndex; 
	char c;
	string curString;
	for (auto iter = patterns.begin(); iter != patterns.end(); ++iter) {
		currentNode = 0;
		curString = *iter;
		for (int i = 0; i < curString.size(); ++i) {
			c = curString[i];		
			letterIndex = letterToIndex(c);
			if (result[currentNode].next[letterIndex] == -1) {
				++currentIndex;
				result[currentNode].next[letterIndex] = currentIndex;
				Node newNode;
				result.push_back(newNode);
				currentNode = currentIndex;
			}
			else {
				currentNode = result[currentNode].next[letterIndex];
			}
			if (i == curString.size() - 1) {
				result[currentNode].isLeaf = true;
			}
		}
	}
	return result;
}

bool search_trie(trie t, const string& text) {
	int currentNode=0, search, letterIndex;
	for (const char & c: text) {
		letterIndex = letterToIndex(c);
		search = t[currentNode].next[letterIndex];
		if (search == -1) {
			return false;
		}
		else {
			currentNode = search;
			if (t[currentNode].isLeaf) {
				return true;
			}
		}
	}
	return false;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	trie t = build_trie(patterns);	
	// write your code here
	bool hit = false;
	for (int i = 0; i < text.size(); ++i) {
		hit = search_trie(t, text.substr(i));
		if (hit) {
			result.push_back(i);
		}
	}	
	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
