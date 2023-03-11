#include <iostream>
#include <vector>

using namespace std;

//���� ��� �迭
vector<int> ary = { 5, 2, 1, 7, 4, 9, 8, 6, 3, 10, 55, 2, 100, 68, 24 };

//vector<int> ��� �Լ�
void print(vector<int> ary) {
	for (int i = 0; i < ary.size(); i++) {
		printf("[%d]", ary[i]);
	}
}

//���� ����
vector<int> mergeSort(vector<int> ary) {
	int size = ary.size();
	
	//������ ������ 1���� ��쿡�� �̹� ���ĵ� ������ �����Ѵ�.
	if (size <= 1) return ary;

	//����
	vector<int> temp1;
	vector<int> temp2;
	for (int i = 0; i < size; i++) {
		if (i < size / 2) {
			temp1.push_back(ary[i]);
		}
		else {
			temp2.push_back(ary[i]);

		}
	}

	//������ �迭 ���� ��ͷ� ����
	temp1 = mergeSort(temp1);
	temp2 = mergeSort(temp2);

	print(temp1);
	printf(" + ");
	print(temp2);
	printf(" = ");

	//����
	vector<int> temp3; // ��ĥ �迭
	int temp1_x = 0;
	int temp2_x = 0;
	for (int i = 0; i < temp1.size() + temp2.size(); i++) {
		if (temp1_x == temp1.size()) {
			temp3.push_back(temp2[temp2_x]);
			temp2_x++;
		}
		else if (temp2_x == temp2.size()) {
			temp3.push_back(temp1[temp1_x]);
			temp1_x++;
		}
		else if (temp1[temp1_x] < temp2[temp2_x]) {
			temp3.push_back(temp1[temp1_x]);
			temp1_x++;
		}
		else {
			temp3.push_back(temp2[temp2_x]);
			temp2_x++;
		}
	}


	print(temp3);
	cout << endl;

	return temp3;
}

int main() {
	ary = mergeSort(ary);

	cout << endl;
	print(ary);

	return 0;
}
