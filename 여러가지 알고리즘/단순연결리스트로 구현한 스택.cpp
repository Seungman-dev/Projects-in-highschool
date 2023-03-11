#include <iostream>

using namespace std;

//push, peek, pop, print

struct Node {
	int item = NULL;
	Node* down = NULL;
};

class Stack {
public:
	Node* top = NULL;
	int list_size = 0;
	void push(int item) {
		if (list_size == 0) {
			top = new Node;
		}
		else {
			Node* temp = top;
			top = new Node;
			top->down = temp;
		}
		top->item = item;
		list_size++;
	}
	int peek() {
		if (list_size > 0) {
			return top->item;
		}
		else {
			return -1;
		}
	}
	int pop() {
		if (list_size > 0) {
			Node* temp = top;
			top = top->down;
			list_size--;
			return temp->item;
		}
		else {
			return -1;
		}
	}
	void printList() {
		if (list_size >= 0) {
			Node* iter = top;
			for (int i = 0; i < list_size; i++) {
				cout << iter->item << endl;
				if (i != list_size - 1) iter = iter->down;
			}
		}
	}
};

int main() {
	Stack test;
	cout << test.peek() << endl;
	test.printList();
	test.push(5);
	test.push(4);
	test.push(3);
	cout << test.peek() << endl;
	test.printList();
	cout << test.pop() << endl;
	cout << test.pop() << endl;
	cout << test.peek() << endl;
	test.printList();
	return 0;
}