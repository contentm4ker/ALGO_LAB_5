#include <string>
#include <vector>

using namespace std;

vector<int> Prefix_Function(const string& pattern);

void KMP(const string& S, const string& pattern, vector<int>& positions);
