#ifndef KMP_FUNCTIONS_H
#define KMP_FUNCTIONS_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> Prefix_Function(const string& pattern);

int KMP_Returning_First_Pos(const string& S, const string& pattern);

void KMP(const string& S, const string& pattern, vector<int>& positions);

#endif