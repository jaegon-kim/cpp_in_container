#include <iostream>
#include <vector>
#include <memory>
#include "utility/dump.hpp"
using namespace std;

namespace p24_10 {

	template <typename T>
	struct Node;

	template <typename T>
	void dump(shared_ptr<Node<T>> n, bool nl) {
		cout << "{";
		while (n) {
			cout << n->data << "(";
			if (n->jump) {
				cout << n->jump->data;
			}
			cout << "), ";
			n = n->next;
		}
		cout << "}";
		if (nl) {
			cout << endl;
		}
	}

	template <typename T>
	struct Node {
		Node(T _data) : data(_data) {}		
		T data;
		shared_ptr<Node<T>> next = nullptr;
		shared_ptr<Node<T>> jump = nullptr;
	};

	template <typename T>
	shared_ptr<Node<T>> copy(shared_ptr<Node<T>> r) {

		shared_ptr<Node<T>> c = r;
		shared_ptr<Node<T>> new_r = make_shared<Node<T>>(r->data);
		shared_ptr<Node<T>> new_c = new_r;

		while (true) {
			new_c->jump = c->jump;
			c->jump = new_c;

			c = c->next;
			if (!c) {
				break;
			}

			shared_ptr<Node<T>> new_t = make_shared<Node<T>>(c->data);
			new_c->next = new_t;
			new_c = new_c->next;
		}

		c = r;
		new_c = new_r;

		while (c) {
			shared_ptr<Node<T>> t = new_c->jump;
			if (t) {
				new_c->jump = t->jump;
			}
			c->jump = t;

			c = c->next;
			new_c = new_c->next;
		}

		return new_r;
	}


	void test() {
		shared_ptr<Node<char>> na = make_shared<Node<char>>('a');
		shared_ptr<Node<char>> nb = make_shared<Node<char>>('b');
		shared_ptr<Node<char>> nc = make_shared<Node<char>>('c');
		shared_ptr<Node<char>> nd = make_shared<Node<char>>('d');

		shared_ptr<Node<char>> root = na;
		na->next = nb;
		na->jump = nc;
		nb->next = nc;
		nb->jump = nd;
		nc->next = nd;
		nc->jump = nb;
		nd->jump = nd;

		dump(root, true);
		shared_ptr<Node<char>> new_root = copy(root);
		dump(new_root, true);
	}
}

void test_p24_10_jump_list_copy() {
	PRINT_FUNC_NAME;
	p24_10::test();

}