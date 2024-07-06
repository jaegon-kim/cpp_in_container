#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"
using namespace std;
namespace p24_14 {



	template <typename T>
	struct Vec {

		Vec(const vector<T> & _v) 
			: v(_v) {
			sort(v.begin(), v.end());
		}

		int b_search(size_t s_idx, size_t e_idx, T key) {
			if (s_idx == e_idx) {
				if (v[s_idx] == key) {
					return s_idx;
				}
				return -1;
			}

			size_t m_idx = (s_idx + e_idx) / 2;

			if (v[m_idx] == key) {
				return m_idx;
			}
			else if (v[m_idx] < key) {
				return b_search(m_idx + 1, e_idx, key);
			}
			else {
				return b_search(s_idx, m_idx, key);
			}

		}

		int get(T key) {
			size_t start = 0;
			size_t inc = 2;

			//for (size_t i = 0; i < 10; i++) {
			while (true) {
				size_t tmp_end = start + inc;
				//cout << "start: " << start << ", tmp_end: " << tmp_end << endl;

				if (tmp_end >= v.size()) {
					inc /= 2;
					continue;
				}

				if (v[tmp_end] < key) {
					inc *= 2;
					start = tmp_end;
					continue;
				}

				if (key <= v[tmp_end]) {
					return b_search(start, tmp_end, key);
				}
			}

			return -1;
		}

		void dump(bool nl) {
			cout << "{";
			for (const auto & e: v) {
				cout << e << ", ";
			}
			cout << "}";
			if (nl) {
				cout << endl;
			}
		}

		vector<T> v;
	};



	void test(const vector<int> & v, int key) {
		Vec<int> a = Vec<int>(v);
		a.dump(true);
		//auto r = a.b_search(0, v.size() - 1, key);
		auto r = a.get(key);

		if (r != -1) {
			cout << r << "(" << v[r] << ")" << endl;
		}
		else {
			cout << "not found(" << key << ")" << endl;
		}
	
	}
}


void test_p24_14_b_search_unkonw_end() {
    PRINT_FUNC_NAME;
	for (int i = 0; i < 6; i++) {
		p24_14::test(vector<int> {2, 4, 5}, i);
	}
	//p24_14::test(vector<int> {2, 3, 4}, 4);
	p24_14::test(vector<int> {3, 4, 6, 1, 2, 4, 6, 7, 8, 9}, 7);
}