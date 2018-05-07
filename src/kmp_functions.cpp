#include "../include/kmp_functions.hpp"

vector<int> Prefix_Function(const string& pattern) {
    vector<int> pi;
    if(pattern.length()) {
    	pi.resize(pattern.length());
		pi[0] = 0;
		for (size_t k = 0, i = 1; i < pattern.length(); ++i) {

			while ((k > 0) && (pattern[i] != pattern[k]))
				k = pi[k-1];

			if (pattern[i] == pattern[k])
				k++;

			pi[i] = k;
		}
    }
	return pi;
}

size_t KMP(const string& S, const string& pattern, vector<int>& positions)
{
	size_t compl_counter = 0;
	positions.resize(0);

	if(pattern.length() && S.length()) {
		vector<int> pi = Prefix_Function(pattern);

		for (size_t k = 0, i = 0; i < S.length(); ++i)
		{
			compl_counter++;

			while ((k > 0) && (pattern[k] != S[i]))
				k = pi[k-1];

			if (pattern[k] == S[i])
				k++;

			if (k == pattern.length())
				positions.push_back(i - pattern.length() + 1);
		}
	}

	if(positions.size() == 0)
	    positions.push_back(-1);

	return compl_counter;
}

int KMP_Returning_First_Pos(const string& S, const string& pattern)
{
	if(S.length() == 2*pattern.length()) {
		vector<int> pi = Prefix_Function(pattern);

		for (size_t k = 0, i = 0; i < S.length(); ++i)
		{
			while ((k > 0) && (pattern[k] != S[i]))
				k = pi[k-1];

			if (pattern[k] == S[i])
				k++;

			if (k == pattern.length())
				return (i - pattern.length() + 1);
		}
	}

    return -1;
}

size_t SimpleSearch(string text, string patt, vector<int> positions)
{
	size_t compl_counter = 0;
	for (int i = 0; i < (int)(text.length() - patt.length() + 1); ++i) {
		for (int j = 0;; ++j) {
			compl_counter++;
			if (!patt[j]) positions.push_back(i);
			if(text[i+j] != patt[j]) break;
		}
	}
	if(!positions.size())
		positions.push_back(-1);
	return compl_counter;
}