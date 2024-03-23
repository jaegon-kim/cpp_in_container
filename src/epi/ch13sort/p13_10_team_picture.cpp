#include <iostream>
#include <vector>
#include <algorithm>
#include <utility/dump.hpp>

using namespace std;

namespace p13_10 {

    bool compare(int a, int b) {
        return a < b;
    }


    // t1: behind line (taller)
    // t2: front line
    bool check_team_picture_available(vector<int> t1, vector<int> t2) {
        sort(t1.begin(), t1.end(), compare);
        sort(t2.begin(), t2.end(), compare);

        dump_vec(t1, true);
        dump_vec(t2, true);


        int i1 = t1.size() - 1;
        int i2 = t2.size() - 1;

        while((i1 - 1) >= 0) {
            if (t1[i1 - 1] <= t2[i2]) {
                break;
            }
            i1--;
        }

        if (!i1) {
            return true;
        }

        while(i1 >= 0) {
            if (t1[i1] <= t2[i2]) {
                return false;
            }

            i1--;
            i2--;
        }
        return true;
    }

    void test(const vector<int> & t1, const vector<int> & t2) {
        cout << check_team_picture_available(t1, t2) << endl;
    }
}

void test_p13_10_team_picture() {
    PRINT_FUNC_NAME;

    p13_10::test(
        vector<int> {2, 3, 6, 9},
        vector<int> {1, 2, 5, 8} 
    );


    p13_10::test(
        vector<int> {2, 3, 6, 9},
        vector<int> {1, 5, 5, 8} 
    );

}
