#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include "utility/dump.hpp"
using namespace std;
namespace p24_09 {

	void dump_list_with_iterator(const list<int> & l, bool nl) {
		cout << "{";
		for (list<int>::const_iterator i = l.begin(); i != l.end(); i++) {
			cout << *i << ", ";
		}

		cout << "}";
		if (nl) {
			cout << endl;
		}
	}

	void test_iterator() {
		cout << "vector iterator " << endl;
		const vector<int> cv = { 1, 2, 3, 4 };
		vector<int>::const_iterator v_i = cv.begin();
		cout << v_i[0] << ", " << v_i[1] << endl;
		v_i++;
		v_i += 2;
		cout << *v_i << endl;

		cout << "list iterator " << endl;
		const list<int> cl = { 1, 2, 3, 4, 5 };
		list<int> l = cl;
		dump_list_with_iterator(l, true);

		list<int>::iterator p = l.begin();
		p++; cout << *p << endl;
		//cout << p[0] << endl; // not allowed in list
		//p += 1;				// not allowed in list

		list<int>::iterator p2 = p;
		p2++; 
		p2++; cout << *p2 << endl;
		int t_v = *p;
		l.erase(p); cout << "erase p" << endl;
		dump_list_with_iterator(l, true);

		l.insert(p2, t_v);cout << "insert v at p2" << endl;
		dump_list_with_iterator(l, true);
	}

	template <typename T>
	struct Node {
		Node(T _d) : data(_d) {}
		T data;
		shared_ptr<Node<T>> next = nullptr;
	};

	template <typename T>
	struct List {

		void add(T d) {
			shared_ptr<Node<T>> n = make_shared<Node<T>>(d);
			if (!front) {
				front = n;
				back = n;
			} else {
				back->next = n;
				back = n;
			}
			count++;
		}

		void dump(bool nl) {
			shared_ptr<Node<T>> n = front;
			cout << "{";
			while (n) {
				cout << n->data << ", ";
				n = n->next;
			}
			cout << "}";
			if (nl) {
				cout << endl;
			}
		}

		shared_ptr<Node<T>> zip_even(shared_ptr<Node<T>> node, int depth) {
			if (!depth) {
				back = node;
				return node;
			}

			shared_ptr<Node<T>> n_node = zip_even(node->next, depth - 1);
			shared_ptr<Node<T>> nn_node = n_node->next;

			if (node->next != n_node) {
				n_node->next = node->next;
			}

			node->next = n_node;
			return nn_node;
		}

		shared_ptr<Node<T>> zip_odd(shared_ptr<Node<T>> node, int depth) {
			//cout << "[" << depth << "] " << node->data << endl;
			if (!depth) {
				back = node;
				//cout << "[" << depth << "] return " << node->next->data << endl;
				return node->next;
			}

			shared_ptr<Node<T>> n_node = zip_odd(node->next, depth - 1);
			//cout << "[" << depth << "] " << n_node->data << endl;
			shared_ptr<Node<T>> nn_node = n_node->next;

			n_node->next = node->next;
			node->next = n_node;

			return nn_node;
		}

		void zip() {
			if (!(count % 2)) {
				zip_even(front, count / 2);
			}
			else {
				zip_odd(front, count / 2);
			}
			back->next = nullptr;
		}


		shared_ptr<Node<T>> front = nullptr;
		shared_ptr<Node<T>> back = nullptr;
		size_t count = 0;
	};

	void test(const vector<int> & v) {

		List<int> list;
		for (const auto & e : v) {
			list.add(e);
		}
		list.dump(false);
		//list.zip_even(list.front, list.count / 2);
		//list.zip_odd(list.front, list.count / 2);
		//list.back->next = nullptr;
		list.zip();
		cout << "->";
		list.dump(true);
	}
}

void test_p24_09_zipping() {
    PRINT_FUNC_NAME;;
	//p24_09::test_iterator();
	p24_09::test(vector<int> {1, 2});
	p24_09::test(vector<int> {1, 2, 3, 4});
	p24_09::test(vector<int> {1, 2, 3, 4, 5, 6});
	p24_09::test(vector<int> {1, 2, 3, 4, 5, 6, 7, 8});
	p24_09::test(vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
	p24_09::test(vector<int> {1, 2, 3});
	p24_09::test(vector<int> {1, 2, 3, 4, 5});
	p24_09::test(vector<int> {1, 2, 3, 4, 5, 6, 7});
	p24_09::test(vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9});
    
}





