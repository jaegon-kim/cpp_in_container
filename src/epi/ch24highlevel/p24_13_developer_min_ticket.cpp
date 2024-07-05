#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <utility/dump.hpp>
using namespace std;
namespace p24_13 {

	template <typename T>
	void dump_vec(const vector<T> & v, bool nl) {
		cout << "{";
		for (const auto & e : v) {
			cout << e << ", ";
		}
		cout << "}";
		if (nl) {
			cout << endl;
		}
	}

	static inline unsigned long long make_key(unsigned int c, unsigned int prev_ticket) {
		return ((unsigned long long) c) << 32 | prev_ticket;
	}

	static inline unsigned int get_c(unsigned long long key) {
		return (key & 0xFFFFFFFF00000000UL) >> 32;
	}

	static inline unsigned int get_prev_ticket(unsigned long long key) {
		return key & (0xFFFFFFFFUL);
	}

	unsigned int min_ticket(const vector<unsigned int> & loc_v, unsigned int c, unsigned int prev_loc, unsigned int prev_ticket, 
								unordered_map<unsigned long long, pair<unsigned int, unsigned int>> & cache) {
		if (c == loc_v.size()) {
			return 0;
		}

		unsigned long long key = make_key(c, prev_ticket);

		if (cache.find(key) != cache.end()) {
			return cache[key].first;
		}

		unsigned int t = 0, min_t_sum = numeric_limits<unsigned int>::max(), min_t = 0;
		if (prev_loc == loc_v[c]) {
			t = min_ticket(loc_v, c + 1, loc_v[c], prev_ticket, cache);
			if (t != numeric_limits<unsigned int>::max()) {
				t += prev_ticket;
				if (t < min_t_sum) {
					min_t_sum = t;
					min_t = prev_ticket;
				}
			}
		} else if (prev_loc < loc_v[c]) {
			for (unsigned int i = prev_ticket + 1; i <= (unsigned int) loc_v.size(); i++) {
				t = min_ticket(loc_v, c + 1, loc_v[c], i, cache);
				if (t == numeric_limits<unsigned int>::max()) {
					continue;
				}
				t += i;
				if (t < min_t_sum) {
					min_t_sum = t;
					min_t = i;
				}
			}
		} else { // prev_loc > loc_v[c]
			if (prev_ticket == 1) {
				return numeric_limits<unsigned int>::max();
			}

			for (unsigned int i = 1; i < prev_ticket; i++) {
				t = min_ticket(loc_v, c + 1, loc_v[c], i, cache);
				if (t == numeric_limits<unsigned int>::max()) {
					continue;
				}
				t += i;
				if (t < min_t_sum) {
					min_t_sum = t;
					min_t = i;
				}
			}
		}
		if (min_t_sum != numeric_limits<unsigned int>::max()) {
			cache.emplace(key, make_pair(min_t_sum, min_t));
		}

		return min_t_sum;
	}

	void dump_cache(unordered_map<unsigned long long, pair<unsigned int, unsigned int>> & cache, unsigned int size, bool nl) {
		unsigned int c = 0, prev_ticket = 0;
		cout << "{";
		for (; c < size; c++) {
			unsigned long long key = make_key(c, prev_ticket);
			auto p = cache[key];
			cout << p.second << ", ";
			prev_ticket = p.second;
		}
		cout << "}";
		if (nl) {
			cout << endl;
		}
	}

	void test(const vector<unsigned int> & loc_v) {
		dump_vec(loc_v, true);
		unordered_map<unsigned long long, pair<unsigned int, unsigned int>> cache;
		unsigned int r = min_ticket(loc_v, 0, 0, 0, cache);
		dump_cache(cache, loc_v.size(), true);
		cout << "min tickets = " << r << endl;
	}
}

void test_p24_13_developer_min_ticket() {
    PRINT_FUNC_NAME;
  	cout << sizeof(unsigned long) << endl;
	cout << sizeof(unsigned long long) << endl;
	//p24_13::test(vector<unsigned int> {300, 400});
	//p24_13::test(vector<unsigned int> {300, 400, 500, 200});
	//p24_13::test(vector<unsigned int> {300, 400, 500, 200, 150, 100});
	//p24_13::test(vector<unsigned int> {600, 400, 500, 200, 150, 100});
	p24_13::test(vector<unsigned int> {600, 400, 500, 200, 120, 110, 100, 90, 150, 100});
}