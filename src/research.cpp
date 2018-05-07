#include "../include/kmp_functions.hpp"
#include <utility>
#include <iomanip>
#include <random>

random_device rd;
mt19937 gen(rd());

pair<size_t, size_t> ComparisonOfComplexities(string S, string P) {
    vector<int> positions;
    vector<size_t> counts;
    auto pr = std::make_pair(KMP(S, P, positions), SimpleSearch(S, P, positions));
    if(S.size() < 100) {
        cout << "Text: '" << S <<"'\n";
        cout << "Pattern: '" << P <<"'\n";
        cout << "Number of chars comparisons:\n";
        cout << "-> KMP: " << pr.first <<endl;
        cout << "-> Simple search: " << pr.second <<endl;
        cout <<"____________________________________\n";
    }

    return pr;
}


pair<size_t, size_t> GenRandomStrAndRunCompar(size_t len1, size_t len2) {
    srand (time(NULL));
    string str1, str2;
    string alphanum = "abcdefghijklmnopqrstuvwxyz";
    uniform_int_distribution<> dist(0, alphanum.size() - 1);
    for (size_t i = 0; i < len1; ++i) {
        str1 += alphanum[dist(gen)];
        if(len2) {
            str2 += alphanum[dist(gen)];
            len2--;
        }
    }
    return ComparisonOfComplexities(str1, str2);
}

int main() {

    //ComparisonOfComplexities("aabaabaaaabaabaaab", "aabaa");
    //ComparisonOfComplexities("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "b");

    int patt_size = 4; //изначальный размер шаблона
    for (size_t i = 0; i < 6; i++){
            //счетчики суммы кол-ва сравнений символов
            size_t ss_count = 0;
            size_t kmp_count = 0;

            int text_size = 1000; //изначальный размер текста
            vector<size_t> text_sizes;

            if(patt_size <= text_size)
                text_sizes.push_back(text_size);

            for (size_t k = 0; k < 5; k++){
                if(patt_size <= text_size) {
                    auto pr = GenRandomStrAndRunCompar(text_size, patt_size);
                    kmp_count += pr.first;
                    ss_count += pr.second;
                    text_size *= 10; //увеличиваем текст в 10 раз
                    text_sizes.push_back(text_size);
                }
                else text_size *= 10;
            }

            //выводим среднее значение
            cout << fixed;
            cout.precision(1);
            cout << "RESULTS:\nPatt size = " << patt_size <<endl;
            cout << "Text sizes = ( ";
            for(const auto& item : text_sizes) {
                cout << item <<" ";
            }
            cout << ")\nKMP average num of chars comparison = "
            << (kmp_count / (double)text_sizes.size()) <<endl;
            cout << "Simple search average num of chars comparison = "
            << (ss_count / (double)text_sizes.size()) <<endl;
            cout <<"------------------------\n";

            patt_size *= 4; //увеличиваем шаблон в 4 раза
    }
    return 0;
}
