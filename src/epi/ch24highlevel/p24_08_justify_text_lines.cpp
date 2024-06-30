#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/dump.hpp"
using namespace std;
namespace p24_08 {

    vector<string> tokenize(const string & txt) {
        vector<string> tokens;
        stringstream s(txt);
        string token;
        while(getline(s, token, ' ')) {
            tokens.push_back(token);
        }
        return tokens;
    }

    vector<string> justify_lines(const vector<string> & tokens, const size_t width) {

        vector<string> rlines;
        size_t w_1 = 0;
        size_t w_0 = 0;
        vector<string> line;
        for (auto token: tokens) {
            if (!line.size()) {
                if (token.length() <= width) {
                    w_1 += token.length();
                    w_0 += (token.length());
                    line.push_back(token);
                } else {
                    w_1 = 0, w_0 = 0;
                    line.clear();
                    rlines.push_back(token);
                    //cout << " flush: " << token << endl;
                }
            } else {
                if ((w_1 + 1 + token.length()) > width) {
                    //cout << "w_1: " << w_1 << endl;
                    //cout << "t_l: " << token.length() << endl;

                    size_t empty = width - w_0;
                    size_t line_size = (line.size() == 1? 1: line.size() - 1);
                    size_t d = empty / line_size;
                    size_t m = empty % line_size;

                    for (size_t i = 0; i < line_size; i++) {
                        line[i].append(d, '_');
                        if (m) {
                            line[i].append(1, '_');
                            m--;
                        }
                    }
                    //dump_vec(line, true);
                    string str = "";
                    for (size_t i = 0; i < line.size(); i++) {
                        str += line[i];
                    }

                    rlines.push_back(str);
                    //cout << " flush: " << str << endl;

                    w_1 = 0, w_0 = 0;
                    line.clear();
                    if (token.length() <= width) {
                        w_1 += (token.length());
                        w_0 += (token.length());
                        line.push_back(token);
                    } else {
                        w_1 = 0, w_0 = 0;
                        line.clear();
                        rlines.push_back(token);
                        //cout << " flush: " << token << endl;

                    }

                } else {
                    if (token.length() <= width) {
                        w_1 += (1 + token.length());
                        w_0 += (token.length());
                        line.push_back(token);
                    } else {
                        w_1 = 0, w_0 = 0;
                        line.clear();
                        rlines.push_back(token);
                        //cout << " flush: " << token << endl;

                    }
                }

            }

            //cout << "[token: " << token << "]" << endl;
            //cout << "line: ";
            //dump_vec(line, true);           

        }

        if (line.size() > 0) {
            for (size_t i = 1; i < line.size(); i++) {
                line[i - 1].append(1, '_');
            }
            string str = "";
            for (size_t i = 0; i < line.size(); i++) {
                str += line[i];
            }
            //cout << "str = " << str << endl;
            rlines.push_back(str);
            //dump_vec(line, true);
        }
        return rlines;
    }

    void test(const string & txt, const size_t width) {
        vector<string> tokens = tokenize(txt);
        //tokens[0].append(3, '_');
        cout << "input: ";
        dump_vec(tokens, true);
        auto r = justify_lines(tokens, width);
        for (auto l: r) {
            cout << l << endl;
        }

    }    
}

void test_p24_08_justify_text_lines() {
    PRINT_FUNC_NAME;
    const string txt = "The dominant sequence transduction models are based on complex recurrent or "
            "convolutional neural networks that include an encoder and a decoder. The best ";

    //const string txt = "12345 12 12345 12 12345 12";

    p24_08::test(txt, 30);

    const string txt2 = "The dominant sequence transduction models are based on complex recurrent or "
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

        p24_08::test(txt2, 100);
}