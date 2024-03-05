#include <iostream>
#include <unordered_map>
#include <list>
#include <chrono>
#include <memory>

#include "utility/dump.hpp"

using namespace std;
using namespace std::chrono;

namespace p12_03 {

    void test_chrono() {
        unsigned long long ns1 = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
        cout << ns1 << endl;
        unsigned long long ns2 = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
        cout << ns2 << endl;
        cout << (ns1 < ns2 ? "ns1 is old" : "ns1 is not old") << endl;        
    }

    struct BookRef {
        BookRef(string _isbn, int _price) :
            isbn {_isbn}, price {_price}, ts {0UL} {}
        string isbn;
        int price;
        unsigned long long ts = 0UL;        
    };

    template <typename OutputStream>
    inline OutputStream& operator<<(OutputStream& os, const BookRef boot_ref) {
        os << "BookRef {";
        os << "isbn: " << boot_ref.isbn << ", ";
        os << "price: " << boot_ref.price << ", ";
        os << "ts: " << boot_ref.ts;
        os << "}";
        return os;
    }

    class IsbnCache {
        public:
            bool insert(shared_ptr<BookRef> book_ptr) {
                if (map.find(book_ptr->isbn) == map.end()) {

                    if (map.size() >= max_size) {
                        erase_lru();
                    }
                    map.emplace(book_ptr->isbn, book_ptr);
                    book_ptr->ts = get_ts();
                    insert_q(book_ptr);
                    return true;
                } else {
                    return false;
                }
            }

            bool erase(string isbn) {
                if (map.find(isbn) == map.end()) {
                    return false;
                }
                shared_ptr<BookRef> book_ptr = map[isbn];
                erase_q(book_ptr);
                return map.erase(isbn);
            }

            void erase_lru() {
                if (queue.size()) {
                    shared_ptr<BookRef> book_ptr = queue.back();
                    map.erase(book_ptr->isbn);
                    queue.pop_back();
                    cout << "erase_lru: " << *book_ptr << endl;
                }
            }

            shared_ptr<BookRef> lookup(string isbn) {
                if (map.find(isbn) == map.end()) {
                    return nullptr;
                } else {
                    shared_ptr<BookRef> book_ptr = map[isbn];
                    book_ptr->ts = get_ts();
                    erase_q(book_ptr);
                    insert_q(book_ptr);
                    return book_ptr;
                }
            }

            void dump() {
                std::cout << "map   (" << map.size() <<") {";
                for (auto p: map) {
                    std::cout << "(" << p.first << " ," << *p.second << "), ";
                }
                std::cout << "}";
                std::cout << std::endl;

                std::cout << "queue (" << queue.size() <<") {";
                for (auto &v: queue) {
                    std::cout << *v << ", ";
                }
                std::cout << "}";
                std::cout << std::endl;

            }
        private:
            unsigned long long get_ts() {
                return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();;
            }

            void insert_q(shared_ptr<BookRef> book_ptr) {
                list<shared_ptr<BookRef>>::iterator iter = queue.begin();
                for(; iter != queue.end(); iter++) {
                    shared_ptr<BookRef> e_ptr = *iter;
                    if (e_ptr->ts < book_ptr->ts) {
                        break;
                    }                    
                }
                queue.insert(iter, book_ptr);
            }

            shared_ptr<BookRef> erase_q(shared_ptr<BookRef> book_ptr) {
                list<shared_ptr<BookRef>>::iterator iter = queue.begin();
                for ( ; iter != queue.end(); iter++) {
                    if (book_ptr == *iter) {
                        queue.erase(iter);
                        return book_ptr;
                    }
                }
                return nullptr;
            }

            unordered_map<string, shared_ptr<BookRef>> map;
            list<shared_ptr<BookRef>> queue;
            size_t max_size = 3;
    };

    void test() {
        IsbnCache isbn_cache;
        isbn_cache.dump();
        cout << endl;
        cout << "insert: " << 
            isbn_cache.insert(make_shared<BookRef>("12345", 10000)) << endl;
        cout << "insert: " << 
            isbn_cache.insert(make_shared<BookRef>("12346", 10000)) << endl;
        cout << "insert: " << 
            isbn_cache.insert(make_shared<BookRef>("12347", 10000)) << endl;
        isbn_cache.dump();
        cout << endl;
        shared_ptr<BookRef> book = isbn_cache.lookup("12345");
        if (book) {
            cout << "lookup: " << *book << endl;
        }
        cout << "insert: " << 
            isbn_cache.insert(make_shared<BookRef>("12348", 10000)) << endl;
        isbn_cache.dump();
        cout << endl;

        cout << "erase: " << 
            isbn_cache.erase("12345") << endl;
        isbn_cache.dump();
    }

}

void test_p12_03_isbn_cache() {
    PRINT_FUNC_NAME;
    //p12_03::test_chrono();
    p12_03::test();
}