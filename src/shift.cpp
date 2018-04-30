#include "../include/kmp_functions.hpp"

int main() {
    string A, B;
    getline(cin, A);
    getline(cin, B);
    cout << KMP_Returning_First_Pos(A + A, B) << endl;
    return 0;
}