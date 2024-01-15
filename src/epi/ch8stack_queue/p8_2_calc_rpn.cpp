#include <iostream>
#include <memory>
#include <list>
#include <unordered_map>

#include "utility/dump.hpp"

using namespace std;

namespace p8_2 {

    unordered_map<string, char> op_map;

    void init_op_map() {
        op_map["+"] = '+';
        op_map["-"] = '-';
        op_map["*"] = '*';
        op_map["/"] = '/';
    }

    char get_op(const string & token) {
        if (op_map.find(token) == op_map.end()) {
            return '#';
        }
        return op_map[token];
    }

    int s2i(const string & strnum) {
        int len = strnum.size();
        int num = strnum[len - 1] - '0';
        for(int i = len - 2; i >= 0; i--) {
            char n = strnum[i] - '0';
            num += n;
        }
        return num;
    }


    int calc_rpn(const vector<string> & rpn) {
        list<int> vs;
        list<char> os;
        int len = rpn.size();
        for (int i = len - 1; i >= 0; i--) {
            char op = get_op(rpn[i]);
            if (op == '#') {
                int num = s2i(rpn[i]);
                vs.push_front(num);
            } else {
                os.push_front(op);
            }
        }

        int rslt = 0;
        while(os.begin() != os.end()) {
            int v1 = vs.front();
            vs.pop_front();

            int v2 = vs.front();
            vs.pop_front();

            char op = os.front();
            os.pop_front();

            switch(op) {
                case '+':
                    rslt = v1 + v2;
                    break;
                case '-':
                    rslt = v1 - v2;
                    break;
                case '*':
                    rslt = v1 * v2;
                    break;
                case '/':
                    rslt = v1 / v2;
                    break;                
            }
            //cout << v1 << " " << op << " " << v2 << " = " << rslt << endl;
            vs.push_front(rslt);
        }

        return rslt;
    }

    void test(const vector<string> & rpn, int expect) {
        init_op_map();
        dump_vec(rpn, false);
        int rslt = calc_rpn(rpn);
        cout << " = " << rslt << " " << (rslt == expect? "[success]" : "[failed]") << endl;
    }
}

void test_p8_2_calc_rpn() {

    // c++ list usage
    list<char> l;
    for (char c = 'a'; c <= 'z'; c++) {
        l.push_front(c);
    }

    while(l.begin() != l.end()) {
        cout << l.front() << ", ";
        l.pop_front();
    }
    cout << endl;

    PRINT_FUNC_NAME;
    p8_2::test(vector<string>{"3", "4", "+", "2", "*", "1", "+"}, 15);
}
