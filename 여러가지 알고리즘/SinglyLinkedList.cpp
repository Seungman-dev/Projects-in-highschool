#include <iostream>

using namespace std;

int max(int a, int b) { return a < b ? b : a; }

struct Node {
	int item = 0;
	Node* next = NULL;
};

class Slist {
private:
	Node* head = NULL;
	int list_size = 0;

public:
	int size() { return list_size; }
	bool is_empty() { return list_size == 0; }
	Node** getHeadPointer() { return &head; }
	Node* getHead() { return head; }
	Node* getNext(Node* node) { return node->next; }
	void sizeUp() { list_size++; }
	void insertFront(int item) {
		Node* temp = head;
		head = new Node;
		head->item = item;
		head->next = temp;
		list_size++;
	}
	void deleteFront() {
		head = head->next;
		list_size--;
	}
	void printList() {
		if (list_size == 0) {
			cout << "리스트가 비어있습니다." << endl;
			return;
		}
		Node* iter = head;
		for (int i = 0; i < list_size; i++) {
			if (iter->next == NULL) {
				cout << iter->item;
			}
			else {
				cout << iter->item << " -> ";
				iter = iter->next;
			}
		}
		cout << endl;
	}
	void reverse() {
		Slist temp;
		Node* iter = head;
		for (int i = 0; i < list_size; i++) {
			temp.insertFront(iter->item);
			iter = iter->next;
		}
		head = temp.head;
	}
	//k를 기준으로 k보다 작은 값은 Slist1에, 큰 값은 Slist2에 저장하는 함수
	void separation(Slist* Slist1, Slist* Slist2, int k) {
		Node* iter = head;
		for (int i = 0; i < list_size; i++) {
			if (iter->item <= k) Slist1->insertFront(iter->item);
			else Slist2->insertFront(iter->item);
			iter = iter->next;
		}
	}
	//0 = 정상, 1 = 싸이클 에러 또는 SIZE에러
	int checkCycle() {
		Node* iter = head;
		for (int i = 0; i < list_size; i++) {
			iter = iter->next;
		}
		if (iter == NULL) return 0;
		else return 1;
	}
	//정수를 단일연결리스트에 저장
	void integerSave(int num){
		head = NULL;
		list_size = 0;
		while (1) {
			if (num > 0) {
				insertFront(num % 100);
				num /= 100;
			}
			else {
				return;
			}
		}
	}
	//단일연결리스트에 저장된 숫자를 integer형태로 리턴
	int integerReturn() {
		int result = 0;
		int temp = 1;
		for (int i = 1; i < list_size; i++) {
			temp *= 100;
		}
		Node* iter = head;
		for (int i = 0; i < list_size; i++) {
			result += iter->item * temp;
			temp /= 100;
			iter = iter->next;
		}
		return result;
	}
	int search(int num) {
		Node* iter = head;
		for (int i = 0; i < num; i++) {
			iter = iter->next;
		}
		return iter->item;
	}
	void sort() {
		Slist temp;

		//temp에 정렬해서 저장한 다음, head로 temp.head를 가리키기
		// or 기존 단순연결리스트에 바로 정렬하기
	}
};

int sameSum(Slist* Slist1, Slist* Slist2) {
	Node* iter1 = Slist1->getHead();
	Node* iter2 = Slist2->getHead();
	int result = 0;
	while (1) {
		if (iter1 == NULL or iter2 == NULL) break;
		if (iter1->item < iter2->item) iter1 = iter1->next;
		else if (iter1->item > iter2->item) iter2 = iter2->next;
		else {
			result += iter1->item;
			iter1 = iter1->next;
			iter2 = iter2->next;
		}
	}
	return result;
}

// Slist1이 앞, Slist2가 뒤에 오도록 합침
Slist combine(Slist* Slist1, Slist* Slist2) { 
	Slist result;
	Node* iter;
	Node** result_head = result.getHeadPointer();
	Node* result_iter = NULL;

	iter = Slist1->getHead();
	for (int i = 0; i < Slist1->size(); i++) {
		if (result.size() == 0) {
			*result_head = new Node;
			(*result_head)->item = iter->item;
			result_iter = (*result_head);
		}
		else {
			result_iter->next = new Node;
			result_iter->next->item = iter->item;
			result_iter = result_iter->next;
		}
		result.sizeUp();
		iter = iter->next;
	}
	iter = Slist2->getHead();
	for (int i = 0; i < Slist2->size(); i++) {
		if (result.size() == 0) {
			*result_head = new Node;
			(*result_head)->item = iter->item;
			result_iter = (*result_head);
		}
		else {
			result_iter->next = new Node;
			result_iter = result_iter->next;
			result_iter->item = iter->item;
			
		}
		result.sizeUp();
		iter = iter->next;
	}
	return result;
}

// 정렬된 Slist1, Slist2를 정렬된 하나의 단일연결리스트로 만듦
Slist SortedSlistCombine(Slist* Slist1, Slist* Slist2) { 
	Slist result;
	Node* iter1 = Slist1->getHead();
	Node* iter2 = Slist2->getHead();
	Node** result_head = result.getHeadPointer();
	Node* result_iter = NULL;
	int temp_size = Slist1->size() + Slist2->size();

	for (int i = 0; i < temp_size; i++) {
		if (result.size() == 0) {
			*result_head = new Node;
			result_iter = (*result_head);
		}
		else {
			result_iter->next = new Node;
			result_iter = result_iter->next;
		}

		if (iter1 == NULL) {
			result_iter->item = iter2->item;
			iter2 = iter2->next;
		}
		else if (iter2 == NULL) {
			result_iter->item = iter1->item;
			iter1 = iter1->next;
		}
		else if (iter1->item > iter2->item) {
			result_iter->item = iter2->item;
			iter2 = iter2->next;
		}
		else {
			result_iter->item = iter1->item;
			iter1 = iter1->next;
		}
		result.sizeUp();
	}
	return result;
}


int main() {
	Slist test;
	test.insertFront(10);
	test.insertFront(7);
	test.insertFront(5);
	test.insertFront(3);
	test.insertFront(1);
	test.printList();
	Slist test2;
	test2.insertFront(11);
	test2.insertFront(9);
	test2.insertFront(7);
	test2.insertFront(6);
	test2.insertFront(4);
	test2.insertFront(2);
	test2.printList();
	Slist test3 = SortedSlistCombine(&test, &test2);
	test3.printList();
	test3.reverse();
	test3.printList();
	Slist test4;
	Slist test5;
	test3.separation(&test4, &test5, 5);
	test3.printList();
	test4.printList();
	test5.printList();
	test3.reverse();
	int count = sameSum(&test3, &test4);
	cout << "count:" << count << endl;
	cout << test.checkCycle() << endl;
	test3.insertFront(0);
	test3.printList();
	cout << test3.search(test3.size() / 2 - 1) << endl;
	test.integerSave(12345);
	test.printList();
	test2.integerSave(43210);
	test2.printList();
	test3.integerSave(test.integerReturn() + test2.integerReturn());
	test2.printList();
	cout << test3.integerReturn() << endl;
	return 0;
}