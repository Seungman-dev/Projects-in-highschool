#include <iostream>

using namespace std;

struct Node {
	Node* prev = NULL;
	Node* next = NULL;
	int item = NULL;
};

class Deque {
public:
	Node* head = new Node;
	Node* rear = new Node;
	int list_size = 0;
	void insertFront(int item) {
		if (list_size == 0) {
			head = new Node;
			rear = head;
		}
		else {
			Node* temp = head;
			head = new Node;
			head->next = temp;
			temp->prev = head;
		}
		head->item = item;
		list_size++;
	}
	void insertBack(int item) {
		if (list_size == 0) {
			head = new Node;
			rear = head;
		}
		else {
			rear->next = new Node;
			rear->next->prev = rear;
			rear = rear->next;
		}
		rear->item = item;
		list_size++;
	}
	void removeFront() {
		if (list_size > 0) {
			head = head->next;
			if(list_size > 1) head->prev = NULL;
			list_size--;
		}
	}
	void removeBack() {
		if (list_size > 0) {
			rear = rear->prev;
			if(list_size > 1) rear->next = NULL;
			list_size--;
		}
	}
	void printDeque() {
		Node* iter = head;
		for (int i = 0; i < list_size; i++) {
			cout << iter->item;
			if (iter != rear) {
				cout << " -> ";
				iter = iter->next;
			}
		}
	}
};

int main() {

	Deque test;
	test.insertFront(3);
	test.insertFront(2);
	test.insertFront(1);
	test.printDeque();
	cout << endl;
	test.removeFront();
	test.removeBack();
	test.printDeque();
	cout << endl;
	test.insertBack(5);
	test.insertFront(0);
	test.printDeque();
	cout << endl;
	test.removeFront();
	test.removeFront();
	test.removeFront();
	test.insertBack(7);
	test.insertBack(8);
	test.insertFront(6);
	test.printDeque();
	cout << endl;
	test.removeBack();
	test.removeBack();
	test.removeBack();
	test.insertFront(0);
	test.insertFront(1);
	test.insertFront(2);
	test.printDeque();
	return 0;
}