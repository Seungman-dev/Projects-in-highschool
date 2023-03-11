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
	cout << endl << "초기값 " << endl;
	vectorPrint(ary);
	int pivot = ary[0];
	pair<int, int> find_small(ary.size() - 1, -1); //(index, value). -1 는 초기값
	pair<int, int> find_big(1, -1); //(index, value). -1 는 초기값
	while (1) {
		//피봇보다 작은 값 찾기
		if (find_small.second == -1 and find_small.first != 0){
			if(ary[find_small.first] < pivot) {
				find_small.second = ary[find_small.first];
			}
			else {
				find_small.first -= 1;
			}
		}

		//피봇보다 큰 값 찾기
		if (find_big.second == -1 and find_big.first != ary.size()) {
			if (ary[find_big.first] > pivot) {
				find_big.second = ary[find_big.first];
			}
			else {
				find_big.first += 1;
			}
		}

		//작은값과 큰값 찾았을 때
		if ((find_small.second != -1 and find_big.second != -1) or (find_small.second != -1 and find_big.first == ary.size()) or (find_big.second != -1 and find_small.first == 0)) {
			//작은 값의 위치와 큰 값의 위치가 교차되면 피봇값과 작은 값 바꾸고 재귀함수로 분할정렬, 그 후 합치고 리턴
			if (find_small.first <= find_big.first) {
				//바꾸기
				if (find_small.first != 0) {
					ary[find_small.first] = pivot;
					ary[0] = find_small.second;
				}
				
				cout << "피봇 기준 정렬" << endl;
				vectorPrint(ary);

;				//분할정렬(재귀)
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
				cout << "결과값";
				vectorPrint(result_ary);
				return result_ary;
			}

			//아니면 작은 값의 위치와 큰 값 바꾸고 작은값과 큰값 찾는 변수초기화
			else {
				//값 바꾸기
				ary[find_small.first] = find_big.second;
				ary[find_big.first] = find_small.second;

				cout << "find!" << find_small.first << ' ' << find_small.second << ' ' << find_big.first << ' ' << find_big.second << endl;
				vectorPrint(ary);

				//작은값,큰값 찾는 변수 초기화
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