#include <iostream>
#include <vector>

using namespace std;

vector<int> ary = { 5, 2, 1, 7, 4, 9, 8, 6, 3, 10, 55, 100, 68, 24 };

void vectorPrint(vector<int> ary) {
	for (int i = 0; i < ary.size(); i++) {
		printf("[%d]", ary[i]);
	}
	cout << endl;
}

vector<int> quickSort(vector<int> ary) {
	if (ary.size() == 1) return ary;
	cout << endl << "�ʱⰪ " << endl;
	vectorPrint(ary);
	int pivot = ary[0];
	pair<int, int> find_small(ary.size() - 1, -1); //(index, value). -1 �� �ʱⰪ
	pair<int, int> find_big(1, -1); //(index, value). -1 �� �ʱⰪ
	while (1) {
		//�Ǻ����� ���� �� ã��
		if (find_small.second == -1 and find_small.first != 0){
			if(ary[find_small.first] < pivot) {
				find_small.second = ary[find_small.first];
			}
			else {
				find_small.first -= 1;
			}
		}

		//�Ǻ����� ū �� ã��
		if (find_big.second == -1 and find_big.first != ary.size()) {
			if (ary[find_big.first] > pivot) {
				find_big.second = ary[find_big.first];
			}
			else {
				find_big.first += 1;
			}
		}

		//�������� ū�� ã���� ��
		if ((find_small.second != -1 and find_big.second != -1) or (find_small.second != -1 and find_big.first == ary.size()) or (find_big.second != -1 and find_small.first == 0)) {
			//���� ���� ��ġ�� ū ���� ��ġ�� �����Ǹ� �Ǻ����� ���� �� �ٲٰ� ����Լ��� ��������, �� �� ��ġ�� ����
			if (find_small.first <= find_big.first) {
				//�ٲٱ�
				if (find_small.first != 0) {
					ary[find_small.first] = pivot;
					ary[0] = find_small.second;
				}
				
				cout << "�Ǻ� ���� ����" << endl;
				vectorPrint(ary);

;				//��������(���)
				vector<int> front_ary;
				vector<int> back_ary;
				vector<int> result_ary;
				if (find_small.first >= 1) {
					
					for (int i = 0; i < find_small.first; i++) {
						front_ary.push_back(ary[i]);
					}
					front_ary = quickSort(front_ary);
					for (int i = 0; i < front_ary.size(); i++) {
						result_ary.push_back(front_ary[i]);
					}
				}
				result_ary.push_back(pivot);
				if (ary.size()-1 > find_small.first) {
					for (int i = find_small.first + 1; i < ary.size(); i++) {
						back_ary.push_back(ary[i]);
					}
					back_ary = quickSort(back_ary);
					for (int i = 0; i < back_ary.size(); i++) {
						result_ary.push_back(back_ary[i]);
					}
				}
				cout << "�����";
				vectorPrint(result_ary);
				return result_ary;
			}

			//�ƴϸ� ���� ���� ��ġ�� ū �� �ٲٰ� �������� ū�� ã�� �����ʱ�ȭ
			else {
				//�� �ٲٱ�
				ary[find_small.first] = find_big.second;
				ary[find_big.first] = find_small.second;

				cout << "find!" << find_small.first << ' ' << find_small.second << ' ' << find_big.first << ' ' << find_big.second << endl;
				vectorPrint(ary);

				//������,ū�� ã�� ���� �ʱ�ȭ
				find_small.first = ary.size() - 1;
				find_small.second = -1;
				find_big.first = 1;
				find_big.second = -1;
			}
		}
		
	}

	return ary;
}

int main() {

	vectorPrint(quickSort(ary));

	return 0;
}