#include "../include/kmp_functions.hpp"

vector<int> Prefix_Function(const string& pattern) {
    vector<int> pi (pattern.length());
	pi[0] = 0;
	for (int k = 0, i = 1; i < pattern.length(); ++i) {

		while ((k > 0) && (pattern[i] != pattern[k]))
			k = pi[k-1];

		if (pattern[i] == pattern[k])
			k++;

		pi[i] = k;
	}
	return pi;
}

void KMP(const string& S, const string& pattern, vector<int>& positions)
{
    positions.resize(0);
	vector<int> pi = Prefix_Function(pattern);

	for (int k = 0, i = 0; i < S.length(); ++i)
	{
		while ((k > 0) && (pattern[k] != S[i]))
			k = pi[k-1];

		if (pattern[k] == S[i])
			k++;

		if (k == pattern.length())
			positions.push_back(i - pattern.length() + 1);
	}

	if(positions.size() == 0)
	    positions.push_back(-1);
}
