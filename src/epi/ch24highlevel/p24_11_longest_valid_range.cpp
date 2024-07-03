#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "utility/dump.hpp"
using namespace std;
namespace p24_11 {

	template <typename A, typename B>
	void dump_vec_pair(const vector<pair<A, B>> & v, bool nl) {
		cout << "{";
		for (const auto & p : v) {
			if (p.second == numeric_limits<size_t>::max()) {
				cout << "(" << p.first << ", -), ";
			}
			else {
				cout << "(" << p.first << ", " << p.second << "), ";
			}
		}
		cout << "}";
		if (nl) {
			cout << endl;
		}
	}

	pair<size_t, size_t> longest_valid_range(const string & str) {
		
		vector<pair<size_t, size_t>> s;
		for (size_t i = 0; i < str.length(); i++) {

			//cout << str[i];
			switch (str[i]) {
			case '(':
				s.push_back(make_pair(i, numeric_limits<size_t>::max()));
				break;
			case ')':
				if (!s.size()) {
					break;
				}

				if (s.back().second == numeric_limits<size_t>::max()) {
					s.back().second = i;

					if (s.size() >= 2 && s[s.size() - 2].second != numeric_limits<size_t>::max()) {
						if (s[s.size() - 2].second + 1 == s.back().first) {
							s[s.size() - 2].second = s.back().second;
							s.pop_back();
						}
					}
				}
				else {
					auto p = s.back();
					if (s.size() == 1) {
						break;
					}

					s.pop_back();
					if (p.second + 1 == i) {
						s.back().second = i;
					}
				}

				break;
			default:
				cout << "invalid input: " << str[i] << endl;
			}
		}
		
		//cout << " ";
		//dump_vec_pair(s, true);

		pair<size_t, size_t> longest;
		size_t longest_len = 0;

		for (const auto & p : s) {
			if (p.second != numeric_limits<size_t>::max()) {
				size_t len = p.second - p.first + 1;
				if (len > longest_len) {
					longest = p;
					longest_len = len;
				}
			}
		}

		return longest;
	}

	void test(const string & str) {
		cout << "input: " << str << ", ";
		auto r = longest_valid_range(str);
		
		cout << " longest: ";
		if (r.first != r.second) {
			for (size_t i = r.first; i <= r.second; i++) {
				cout << str[i];
			}
		}
		cout << endl;
	}
}

void test_p24_11_longest_valid_range() {
    PRINT_FUNC_NAME;
	p24_11::test("(");
	p24_11::test(")");
	p24_11::test("()");
	p24_11::test("((");
	p24_11::test("()(");
	p24_11::test(")()(");
	p24_11::test("((())()(()(");
	p24_11::test("((()))");
	p24_11::test(")((()))");
	p24_11::test(")((())))(((())))(");
	p24_11::test(")((())))(((())))()((())))((((()()))))()((())))(((())))()((())))(((())))(");
}