#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include "utility/dump.hpp"

using namespace std;

class CustomerCredit {
    public:

        void add_user(string user, int credit) {
            s.emplace(make_pair(user, credit));
            m.emplace(user, credit);
        }

        void del_user(string user) {
            s.erase(make_pair(user, get_credit(user)));
            m.erase(user);
        }

        int get_credit(string user) {
            return m.at(user) + credit_offset;
        }

        void set_credit_offset(int offset) {
            credit_offset = offset;
        }

        string max_credit_user() {
            if (s.size() > 0) {
                return (*s.begin()).first;
            }
            return "-";
        }

        void dump(bool nl) {
            for(auto iter = s.begin(); iter != s.end(); iter++) {
                string user = (*iter).first;
                int credit = get_credit(user);
                cout << user << ":" << credit << ", ";
            }
            if (nl) {
                cout << endl;
            }
        }

    private:
        struct compare {
            bool operator() (const pair<string ,int> & p1, const pair<string, int> & p2) const {
                return p1.second > p2.second;
            }
        };

        set<pair<string, int>, compare> s;
        unordered_map<string, int> m;
        int credit_offset = 0;
};

namespace p14_011 {
    void test() {
        CustomerCredit c;
        c.add_user("aa", 1);
        c.add_user("ab", 2);
        c.add_user("ac", 3);
        c.dump(true);

        c.del_user("aa");
        c.dump(true);

        c.set_credit_offset(100);
        c.dump(true);

        cout << c.max_credit_user() << endl;
        c.add_user("ad", 5);
        cout << c.max_credit_user() << endl;

    }
}

void test_p14_011_customer_credit() {
    PRINT_FUNC_NAME;
    p14_011::test();
}