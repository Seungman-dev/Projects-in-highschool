#include <iostream>

using namespace std;

struct Node {
	int item = NULL;
	Node* next = NULL;
};

class Queue {
public:
	Node* head = NULL;
	Node* tail = NULL;
	int list_size = 0;
	void add(int item) {
		if (list_size == 0) {
			head = new Node;
			head->item = item;
			tail = head;
		}
		else {
			tail->next = new Node;
			tail->next->item = item;
			tail = tail->next;
		}
		list_size++;
	}
	int remove() {
		if (list_size > 0) {
			int temp = head->item;
			head = head->next;
			list_size--;
			return temp;
		}
	}
	void printQueue() {
		Node* iter = head;
		for (int i = 0; i < list_size; i++) {
			cout << iter->item;
			if (i != list_size - 1) {
				cout << " -> ";
				iter = iter->next;
			}
		}
	}
};

int main() {
	Queue test;
	test.add(5);
	test.add(4);
	test.add(3);
	test.printQueue();
	cout << endl;
	cout << test.remove() << endl;
	cout << test.remove() << endl << endl;
	test.printQueue();
	return 0;
}