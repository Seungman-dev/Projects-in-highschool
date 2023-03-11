#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

vector<int> ary;

void binarySearch(int num, vector<int> ary, int left, int right, int count) {
	count++;
	int average = (left + right) / 2;
	if (left > right) cout << "탐색 결과 없음" << endl;
	else if (ary[average] == num) cout << "탐색 완료 횟수: " << count << " index: " << average << " value: " << ary[average] << endl;
	else if (ary[average] > num) binarySearch(num, ary, left, average - 1, count);
	else if (ary[average] < num) binarySearch(num, ary, average + 1, right, count);
	return;
}

int main() {
	srand(time(NULL));

	//탐색할 임의의 배열 만들기
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

	//입력값 받아서 이진탐색
	int input;
	while (1) {
		cout << "검색: ";
		cin >> input;
		binarySearch(input, ary, 0, ary.size() - 1, 0);
	}

	return 0;
}