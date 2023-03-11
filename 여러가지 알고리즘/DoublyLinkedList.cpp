#include <iostream>

using namespace std;

struct Node {
	Node* next = NULL;
	Node* prev = NULL;
	int item = 0;
};

class DoublyLinkedList {
private:
	Node* head = new Node;
	Node* tail = new Node;
	int size = 0;

public:
	DoublyLinkedList() {
		head->next = tail;
		tail->prev = head;
	}

	int getSize() { return size; }
	int is_empty() { return size == 0; }
	Node* getHead() { return head; }
	Node* getTail() { return tail; }

	void insertAfter(Node* p, int item) {
		if (p == tail) return; //抗寇贸府
		Node* temp = p->next;
		p->next = new Node;
		p->next->item = item;
		p->next->prev = p;
		p->next->next = temp;
		temp->prev = p->next;
		size++;
	}

	void insertBefore(Node* p, int item) {
		if (p == head) return; //抗寇贸府
		Node* temp = p->prev;
		p->prev = new Node;
		p->prev->item = item;
		p->prev->next = p;
		p->prev->prev = temp;
		temp->next = p->prev;
		size++;
	}

	void deleteNode(Node* p) {
		if (p == head or p == tail) return; //抗寇贸府
		p->prev->next = p->next;
		p->next->prev = p->prev;
		size--;
	}

	void printList() {
		Node* iter = head;
		for (int i = 0; i < size; i++) {
			iter = iter->next;
			if (iter->next == tail) cout << iter->item;
			else cout << iter->item << " <=> ";
		}
		cout << endl;
	}
	void printReverseList() {
		Node* iter = tail;
		for (int i = 0; i < size; i++) {
			iter = iter->prev;
			if (iter->prev == head) cout << iter->item;
			else cout << iter->item << " <=> ";
		}
		cout << endl;
	}
};


int main() {

	DoublyLinkedList test;
	test.insertAfter(test.getHead(), 1);
	test.insertAfter(test.getHead(), 0);
	test.insertAfter(test.getHead()->next->next, 2);
	test.insertBefore(test.getHead()->next, -1);
	test.insertBefore(test.getTail(), 3);
	test.deleteNode(test.getHead()->next);
	test.printList();
	test.printReverseList();


	return 0;
}