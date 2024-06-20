#include <iostream>
#include <vector>
#include <unordered_map>
#include "utility/dump.hpp"
using namespace std;
namespace p24_03 {

    struct Trade {
        size_t b_idx;
        size_t s_idx;
        int max_profit;
    };

    static inline unsigned long make_key(unsigned int start_idx, unsigned int k) {
        unsigned long ret = start_idx;
        return (ret << 32) | k; 
    }

    static inline unsigned int get_start_idx(unsigned long key) {
        return key >> 32;
    }

    static inline unsigned int get_k(unsigned long key) {
        return key & 0xffffffff;
    }

    int trade(const vector<int> & prices, unsigned int start_idx, unsigned int k, unordered_map<unsigned long, Trade> & cache) {
        unsigned int prices_size = (unsigned int) prices.size();
        if (!k) {
            return 0;
        }

        if (start_idx >= (prices_size - 1)) {
            return 0;
        }

        int max_profit = 0;
        Trade max_trade = {0, 0, 0};

        unsigned long key = make_key(start_idx, k);
        if (cache.find(key) != cache.end()) {
            return cache[key].max_profit;
        }

        for (unsigned int i = start_idx; i < prices_size; i++) {
            for (unsigned int j = i + 1; j < prices_size; j++) {
                int ret_profit = trade(prices, j + 1, k - 1, cache);

                int trade_profit = prices[j] - prices[i];
                ret_profit += trade_profit;

                if (ret_profit > max_profit) {
                    max_profit = ret_profit;
                    max_trade = {i, j, ret_profit};
                }
            }
        }

        cache.emplace(key, max_trade);
        return max_profit;
    }

    void dump_trade(const Trade & t) {
        cout << "(" << t.b_idx << ", " << t.s_idx << "): " << t.max_profit << ", ";
    }

    void dump_trade_prices(const vector<int> & prices, const Trade & t) {
        cout << "(";
        for(size_t i = t.b_idx; i <= t.s_idx; i++) {
            cout << prices[i] << ", ";
        }
        cout << "): " << t.max_profit << ", ";
    }

    void dump_cache(const vector<int> & prices, unordered_map<unsigned long, Trade> & cache, unsigned int start_idx, unsigned int k) {
        while(true) {
            unsigned long key = make_key(start_idx, k);
            if (cache.find(key) == cache.end()) {
                break;
            }

            Trade & t = cache[key];
            //dump_trade(t);
            dump_trade_prices(prices, t);
            start_idx = t.s_idx + 1;
            k--;
        }
        cout << endl;

    }

    void test_all_range(const vector<int> & prices, unsigned int k) {
        PRINT_FUNC_NAME;
        unordered_map<unsigned long, Trade> cache;
        trade(prices, 0, k, cache);
        //cout << ret_profit << endl;
        dump_vec_with_idx(prices, true);
        dump_cache(prices, cache, 0, k);
    }

    void test_distilled(const vector<int> & prices, unsigned int k) {
        PRINT_FUNC_NAME;
        vector<int> distilled_prices;
        size_t prices_size = prices.size();

        if (prices_size >= 2 && prices[0] < prices[1]) {
            distilled_prices.push_back(prices[0]);
        }

        size_t i = 1;
        for (; i < (prices_size - 1); i++) {
            if (prices[i - 1] < prices[i] || prices[i] < prices[i + 1]) {
                distilled_prices.push_back(prices[i]);
            }
        }

        if (i < prices_size) {
            if (prices[i - 1] < prices[i]) {
                distilled_prices.push_back(prices[i]);
            }
        }

        unordered_map<unsigned long, Trade> cache;
        trade(distilled_prices, 0, k, cache);
        //cout << ret_profit << endl;
        dump_vec_with_idx(distilled_prices, true);
        dump_cache(distilled_prices, cache, 0, k);
    }


    void test(const vector<int> & prices, unsigned int k) {
        cout << endl;
        test_all_range(prices, k);
        test_distilled(prices, k);
    }

}

void test_p24_03_stock_trading_k() {
    PRINT_FUNC_NAME;
    p24_03::test(vector<int> {10, 20, 0, 35, 40, 0, 5}, 3);

    p24_03::test(vector<int> {
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,
        }, 100);

    p24_03::test(vector<int> {
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240, 225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240, 225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240, 225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240, 225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240, 225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240, 225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240, 225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,
        225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240, 225, 220, 230, 245, 235, 230, 250, 260, 210, 200, 245, 255, 240,

        }, 100);
}