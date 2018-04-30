#include "../include/kmp_functions.hpp"
#include <iostream>
using namespace std;

int main() {
    string P, T;
    vector<int> entry_positions;
    getline(cin, P);
    getline(cin, T);

    size_t i = 0;
    for(const auto& pos : entry_positions) {
        cout <<pos;
        if(i != entry_positions.size() - 1) cout <<",";
        i++;
    }
    cout << endl;

    return 0;
}
