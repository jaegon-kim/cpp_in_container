#include <iostream>
#include <string>
#include <vector>
#include "utility/dump.hpp"

using namespace std;

namespace p6_12 {

    int ctoi(char c) {
        if (c == ' ') {
            return 27;
        } else {
            return c - 'a';
        }
    }

    int rabin_karp_search(const string & t, const string & k) {
        size_t k_len = k.length();

        int base = 27; // small alphabet(26) + ' '
        int hash_t = 0;
        int hash_k = 0;
        int mr_base = 1;

        hash_t = ctoi(t[0]);
        hash_k = ctoi(k[0]);
        for (size_t i = 1; i < k_len; i++) {
            mr_base *= base;
            hash_t = hash_t * base + ctoi(t[i]);
            hash_k = hash_k * base + ctoi(k[i]);  
        }

        //cout << "initial hash_t:" << hash_t << endl;
        //cout << "initial hash_k:" << hash_k << endl;
        //cout << "       mr_base:" << mr_base << endl;
        if (hash_t == hash_k) {
            if (!t.compare(0, k_len, k)) {
                return 0;
            }
        }

        size_t t_len = t.length();
        for (size_t i = k_len; i < t_len; i++) {

            hash_t -= (ctoi(t[i - k_len]) * mr_base);
            hash_t *= base;
            hash_t += ctoi(t[i]);
            //cout << "hash_t(" << i - k_len + 1 <<"): " << hash_t << endl;
            if (hash_t == hash_k) {
                if (t.compare(i - k_len + 1, k_len, k) == 0) {
                    return i - k_len + 1;
                }                
            }
        }
        return -1;
     }


    void test(const string & t, const string & k, int expected_idx) {
        int idx = rabin_karp_search(t, k);
        cout << t << endl;
        cout << " - found (" << k <<") at: " << idx << " " << (idx == expected_idx? "[success]": "[failed]") << endl;
    }
}

void test_p6_12_rabin_karp_search() {
    PRINT_FUNC_NAME;

    //p6_12::test("bcdef", "de");
    p6_12::test("the history of the lands that became the united states", "became", 30);
    p6_12::test("the history of the lands that became the united states began with the arrival of the first people in the americas around bc numerous indigenous cultures formed  and many saw transformations in the   th century away from more densely populated lifestyles and towards reorganized polities elsewhere  the european colonization of the americas began in the late   th century  although most colonies in what would later become the united states were settled after       by the     s  the thirteen british colonies contained     million people and were established along the atlantic coast east of the appalachian mountains  the southern colonies built an agricultural system on slave labor  enslaving millions from africa for this purpose  after defeating france  the british government imposed a series of taxes  including the stamp act of       rejecting the colonists' constitutional argument that new taxes needed their approval  resistance to these taxes  especially the boston tea party in       led to parliament issuing punitive laws designed to end self-government  armed conflict began in massachusetts in"
            , "self-government", 1053);

}
