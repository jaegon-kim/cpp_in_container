#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include "utility/dump.hpp"

using namespace std;

namespace p5_16 {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis;

    size_t sum = 0;
    unordered_map<int, int> m;

    void init_random_generator(const vector<int> & ratio) {
        
        sum = 0;
        //unordered_map<int, int> m;
        for (size_t i = 0; i < ratio.size(); i++) {
            for (size_t j = sum + 1; j <= (sum + ratio[i]); j++) {
                m[j] = i;
            }
            sum += ratio[i];
        }

        //dump_map<int, int>(m, true);
        dis = uniform_int_distribution<int> (1, sum);
    }

    pair<int, int> gen_random(const vector<int> & nums)  {

        int r = dis(gen);
        int idx = m[r];
        return make_pair(idx, nums[idx]);
    } 

    void test(const vector<int> & nums, const vector<int> & ratio) {
        
       init_random_generator(ratio);
        vector<int> cnt(nums.size(), 0);

        int repeat = 100000000;
        for (int i = 0; i < repeat; i++) {
            pair<int, int> p = gen_random(nums);
            cnt[p.first]++;
        }

        cout << "expecting ratio: ";
        for (size_t i = 0; i < ratio.size(); i++) {
            cout << "[" << i << "]" << ((double) ratio[i])/sum << ", ";
        }
        cout << endl;

        cout << "tested ratio: ";
        for (size_t i = 0; i < cnt.size(); i++) {
            cout << "[" << i << "]" << ((double) cnt[i])/repeat << ", ";
        }
        cout << endl;


        //cout << "r: " << r << endl;
    }



}

void test_p5_16_non_uniform_random() {
    PRINT_FUNC_NAME;

    p5_16::test(vector<int> {3, 5, 7, 11}, vector<int> { 9, 6, 2, 1});

}
