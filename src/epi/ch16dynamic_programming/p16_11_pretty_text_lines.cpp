#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include "utility/dump.hpp"
using namespace std;

namespace p16_11 {

    void test_sstream() {
        string s = "Hello World" " Nice To See You";
        string token;
        stringstream ss(s);
        while(getline(ss, token, ' ')) {
            cout << token << endl;
        }
    }

    vector<string> tokenize(const string & txt) {
        vector<string> t_v;
        stringstream sstream(txt);
        string token;
        while(getline(sstream, token, ' ')) {
            t_v.push_back(token);
        }
        return t_v;
     }

    // token vector to token len vector
    vector<size_t> token_vec2token_len_vec(const vector<string> & t_v) {
        vector<size_t> t_len_v;
        for (auto t: t_v) {
            t_len_v.push_back(t.length());
        }
        return t_len_v;
    }

    void print_pretty_text(const vector<string> & t_v, const list<pair<size_t, size_t>> & l, size_t width) {
        for (auto p: l) {
            size_t s_w = 0;
            for(size_t i = 0; i < p.second; i++) {
                if (i) {
                    cout << "_";
                    s_w++;
                }                
                cout << t_v[p.first + i];
                s_w += t_v[p.first + i].length();
            }

            size_t empty_len = width - s_w;
            for (size_t i = 0; i < empty_len; i++) {
                    cout << "_";
            }

            cout << endl;
        }
    }

    list<pair<size_t, size_t>> const_idx_list(unordered_map<size_t, pair<size_t, size_t>> & cache, size_t s) {
        list<pair<size_t, size_t>> l;
        while(true) {
            if (cache.find(s) == cache.end()) {
                break;
            }
            auto p = cache[s];
            l.push_back(make_pair(s, p.second));
            s = s + p.second;
        }
        return l;
    }

    size_t dirty_c(vector<size_t> & t_len_v, size_t c, size_t width, unordered_map<size_t, pair<size_t, size_t>> & cache) {

        if (c == t_len_v.size()) {
            return 0;
        }

        if (cache.find(c) != cache.end()) {
            return cache[c].first;
        }

        size_t s_w = 0, d = 0, min_d = 0x7fffffff;
        size_t min_idx = c;
        list<pair<size_t, size_t>> min_l;

        for (size_t i = c; c < t_len_v.size(); i++) {
            if (i == c) {
                s_w += t_len_v[i];
            } else {
                s_w += (t_len_v[i] + 1);
            }

            if (s_w > width) {
                break;
            }

            size_t empty = width - s_w;
            d = dirty_c(t_len_v, i + 1, width, cache);
            d = d + empty * empty;

            if (d < min_d) {
                min_d = d;
                min_idx = i;
            }
        }

        cache[c] = make_pair(min_d, min_idx - c + 1);

        return min_d;
    }





    void test(const string & txt, size_t width) {
        vector<string> t_v = tokenize(txt);
        dump_vec(t_v, true);
        vector<size_t> t_len_v = token_vec2token_len_vec(t_v);
        dump_vec(t_len_v, true);

        unordered_map<size_t, pair<size_t, size_t>> cache;
        size_t r_d_c = dirty_c(t_len_v, 0, width, cache);
        cout << r_d_c << endl;
        list<pair<size_t, size_t>> r_l_c = const_idx_list(cache, 0);
        dump_list_of_pair(r_l_c, true);
        print_pretty_text(t_v, r_l_c, width);

    }


}

void test_p16_11_pretty_text_lines() {
    PRINT_FUNC_NAME;
    //p16_11::test_sstream();

    const string txt = "The dominant sequence transduction models are based on complex recurrent or "
                "convolutional neural networks that include an encoder and a decoder. The best "
                "performing models also connect the encoder and decoder through an attention "
                "performing models also connect the encoder and decoder through an attention "
                "mechanism. We propose a new simple network architecture, the Transformer, "
                "based solely on attention mechanisms, dispensing with recurrence and convolutions "
                "entirely. Experiments on two machine translation tasks show these models to "
                "be superior in quality while being more parallelizable and requiring significantly "
                "less time to train. Our model achieves 28.4 BLEU on the WMT 2014 Englishto-German "
                "performing models also connect the encoder and decoder through an attention "
                "mechanism. We propose a new simple network architecture, the Transformer, "
                "translation task, improving over the existing best results, including "
                "less time to train. Our model achieves 28.4 BLEU on the WMT 2014 Englishto-German "
                "performing models also connect the encoder and decoder through an attention "
                "mechanism. We propose a new simple network architecture, the Transformer, "
                "translation task, improving over the existing best results, including "
                "ensembles, by over 2 BLEU. On the WMT 2014 English-to-French translation task, "
                "mechanism. We propose a new simple network architecture, the Transformer, "
                "our model establishes a new single-model state-of-the-art BLEU score of 41.0 after "
                "training for 3.5 days on eight GPUs, a small fraction of the training costs of the "
                "performing models also connect the encoder and decoder through an attention "
                "performing models also connect the encoder and decoder through an attention "
                "mechanism. We propose a new simple network architecture, the Transformer, "
                "based solely on attention mechanisms, dispensing with recurrence and convolutions "
                "entirely. Experiments on two machine translation tasks show these models to "
                "be superior in quality while being more parallelizable and requiring significantly "
                "less time to train. Our model achieves 28.4 BLEU on the WMT 2014 Englishto-German "
                "performing models also connect the encoder and decoder through an attention "
                "mechanism. We propose a new simple network architecture, the Transformer, "
                "translation task, improving over the existing best results, including "
                "less time to train. Our model achieves 28.4 BLEU on the WMT 2014 Englishto-German "
                "performing models also connect the encoder and decoder through an attention "
                "mechanism. We propose a new simple network architecture, the Transformer, "
                "translation task, improving over the existing best results, including "
                "ensembles, by over 2 BLEU. On the WMT 2014 English-to-French translation task, "
                "mechanism. We propose a new simple network architecture, the Transformer, "
                "our model establishes a new single-model state-of-the-art BLEU score of 41.0 after "
                "training for 3.5 days on eight GPUs, a small fraction of the training costs of the "                
                "best models from the literature."
                "Recurrent models typically factor computation along the symbol positions of the input and output "
                "sequences. Aligning the positions to steps in computation time, they generate a sequence of hidden "
                "states ht, as a function of the previous hidden state ht−1 and the input for position t. This inherently "
                "sequential nature precludes parallelization within training examples, which becomes critical at longer "
                "sequence lengths, as memory constraints limit batching across examples. Recent work has achieved "
                "significant improvements in computational efficiency through factorization tricks [18] and conditional "
                "computation [26], while also improving model performance in case of the latter. The fundamental "
                "constraint of sequential computation, however, remains."
                ;
    p16_11::test(txt, 130);

}