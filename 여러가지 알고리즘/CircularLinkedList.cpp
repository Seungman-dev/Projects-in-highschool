#include <iostream>

using namespace std;

struct Node {
	Node* next = NULL;
	int item = 0;
};

class CircularLinkedList {
private:
	Node* last = NULL;
	int list_size = 0;
public:
	int size() { return list_size; }
	bool is_empty() { return list_size == 0; }
	void insertFront(int item) {
		if (list_size == 0) {
			last = new Node;
			last->item = item;
			last->next = last;
		}
		else {
			Node* temp = last->next;
			last->next = new Node;
			last->next->next = temp;
			last->next->item = item;
		}
		list_size++;
	}
	void deleteFront() {
		if (is_empty() == true) { return; }
		if (list_size == 1) {
			last = NULL;
		}
		else {
			last->next = last->next->next;

		}
		list_size--;
	}
	void printList() {
		Node* iter = last;
		for (int i = 0; i < list_size; i++) {
			iter = iter->next;
			if (iter == last) {
				cout << iter->item;
			}
			else {
				cout << iter->item << " -> ";
			}
		}
		cout << endl;
	}
	void printList(int num) {
		Node* iter = last;
		for (int i = 0; i < num; i++) {
			iter = iter->next;
			if (i == num - 1) {
				cout << iter->item;
			}
			else {
				cout << iter->item << " -> ";
			}
		}
		cout << endl;
	}
};


int main() {
	CircularLinkedList test;
	test.insertFront(3);
	test.insertFront(2);
	test.insertFront(1);
	test.printList();
	test.insertFront(0);
	test.printList();
	test.printList(10);
	test.deleteFront();
	test.printList();
	test.printList(10);
	return 0;
}