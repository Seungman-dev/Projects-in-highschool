#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

vector<int> ary;

void binarySearch(int num, vector<int> ary, int left, int right, int count) {
	count++;
	int average = (left + right) / 2;
	if (left > right) cout << "Ž�� ��� ����" << endl;
	else if (ary[average] == num) cout << "Ž�� �Ϸ� Ƚ��: " << count << " index: " << average << " value: " << ary[average] << endl;
	else if (ary[average] > num) binarySearch(num, ary, left, average - 1, count);
	else if (ary[average] < num) binarySearch(num, ary, average + 1, right, count);
	return;
}

int main() {
	srand(time(NULL));

	//Ž���� ������ �迭 �����
	ary.reserve(10000);
	int count = 0;
	for (int i = 1; i <= 10000; i++) {
		count += rand() % 10 + 1;
		ary.push_back(count);
	}

	for (int i = 0; i < ary.size(); i++) {
		printf("[%d]", ary[i]);
	}
	cout << endl;

	//�Է°� �޾Ƽ� ����Ž��
	int input;
	while (1) {
		cout << "�˻�: ";
		cin >> input;
		binarySearch(input, ary, 0, ary.size() - 1, 0);
	}

	return 0;
}