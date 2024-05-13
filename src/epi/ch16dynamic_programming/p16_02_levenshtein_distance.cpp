#include <iostream>
#include <vector>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p16_02 {

    int min_d(vector<vector<int>> & d, size_t i, size_t j) {
        int min =  d[i - 1][j - 1];

        if (d[i - 1][j] < min) {
            min = d[i - 1][j];
        } 
        
        if (d[i][j - 1] < min) {
            min = d[i][j - 1];
        } 
        
        return min;
    }

    int levenshtein_distrance(const string & a, const string & b) {
        
        vector<vector<int>> d;

        for(size_t i = 0; i < (b.length() + 1); i++) {
            d.push_back(vector<int> (a.length() + 1, 0));
        }

        for (int i = 0; i < (int) (b.length() + 1); i++) {
            d[i][0] = i;
        }

        for (int i = 0; i < (int) (a.length() + 1); i++) {
            d[0][i] = i;
        }

        for (size_t i = 1; i < (b.length() + 1); i++) {
            for (size_t j = 1; j < (a.length() + 1); j++) {
                if (b[i - 1] == a[j - 1]) {
                    d[i][j] = d[i - 1][j - 1];
                } else {
                    d[i][j] = min_d(d, i, j) + 1;
                }
            }
        }
        return d[b.length()][a.length()];
    }
    void test(const string & a, const string & b) {
        int l_d = levenshtein_distrance(a, b);
        cout << "Levenshtein distance of '"<< a << "','" << b <<"' : " << l_d << endl;
    }
}

void test_p16_02_levenshtein_distance() {
    PRINT_FUNC_NAME;
    p16_02::test("Saturday", "Sunday");
    p16_02::test("Saturday", "Sundays");
    p16_02::test("Carthorse", "Orchestra");
    p16_02::test("adiddas", "adidas");
    p16_02::test("", "adidas");
}

