#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"
using namespace std;
namespace p24_12 {

	template <typename A, typename B>
	void dump_vec_pair(const vector<pair<A, B>> & v, bool nl) {
		cout << "{";
		for (const auto &p : v) {
			cout << "(" << p.first << ", " << p.second << "), ";
		}
		cout << "}";
		if (nl) {
			cout << endl;
		}
	}

	bool compare(const pair<int, double> & a, const pair<int, double> & b) {
		return a.first < b.first;
	}

	vector<pair<int, double>> max_sliding_window(vector<pair<int, double>> v, int w_size) {
		sort(v.begin(), v.end(), compare);
		vector<pair<int, double>> mw_v(v.size());

		for (size_t i = 0; i < mw_v.size(); i++) {
			size_t c_idx = i;
			int c_loc = v[c_idx].first;
			while (c_loc <= (v[i].first + w_size)) {
                if (v[i].second < v[c_idx].second) {
                    break;
                }
				if (v[i].second >= mw_v[c_idx].second) {
					mw_v[c_idx].first = c_loc;
					mw_v[c_idx].second = v[i].second;
				}
				c_idx++;
				if (c_idx == mw_v.size()) {
					break;
				}
				c_loc = v[c_idx].first;
			}
		}

		return mw_v;
	}
	
	void test(const vector<pair<int, double>> & v, int w_size) {
		cout << "org     : ";
		dump_vec_pair(v, true);
		auto r = max_sliding_window(v, w_size);
		cout << "max_side: ";
		dump_vec_pair(r, true);
	}
}

void test_p24_12_max_sliding_window() {
    PRINT_FUNC_NAME;
	p24_12::test(vector<pair<int, double>> {
		{0, 1.3}, {2, 2.5}, {3, 3.7}, {5, 1.4}, {6, 2.6}, {8, 2.2}, {9, 1.7}, {14, 1.1}
	}, 3);
}