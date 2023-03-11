#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector< vector<int> > map = {  // -3 ��ź�� ���� �� ���� ��, -2 ��ź, -1 ��, 0 ����� �̿� ����: �ֺ� ��ź ����
	{ -1, -2, -2, -2, -1 },
	{ -1, 3, 3, 4, -1 },
	{ -1, 1, 0, 2, -1 },
	{ -1, 1, 1, 2, -1 },
	{ -1, -1, -1, -1, -1} };

vector< vector<int> > result(5, vector<int>(5, 0)); // ����� ������ �迭
int result_count = 0; // �� ��� ����� ���� �������



void printMap(vector< vector<int> > temp_map) {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (temp_map[y][x] >= 0) cout << ' ';
			if (temp_map[y][x] == 0) cout << map[y][x] << ' ';
			else cout << temp_map[y][x] << ' ';
			
		}
		cout << '\n';
	}
	cout << '\n';
}

bool mapCheck(vector< vector<int> > temp_map) { // ����ã����� ������ �´��� Ȯ��
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (map[y][x] > 0) {
				int num = map[y][x];

				//�˻��������
				int min_x = x;
				int min_y = y;
				int max_x = x;
				int max_y = y;
				if (min_x > 0) min_x--;
				if (min_y > 0) min_y--;
				if (max_x < 4) max_x++;
				if (max_y < 4) max_y++;

				//�ֺ� ��ź ���� ī��Ʈ
				int boom_count = 0;
				for (int temp_y = min_y; temp_y <= max_y; temp_y++) {
					for (int temp_x = min_x; temp_x <= max_x; temp_x++) {
						if (temp_map[temp_y][temp_x] == -2) boom_count++;
					}
				}
				if (boom_count != num) return false;
			}

		}
	}
	return true;
}

//������ ��� ���� ���ϱ�(���)
void combinationCheck(vector< pair<int, int> > block_list, vector< pair<int, int> > com, int boom_num, int count, vector< vector< pair<int, int> > > *all_combination) {
	if (com.size() == boom_num) {
		all_combination->push_back(com);
		return;
	}
	for (int i = count; i < block_list.size(); i++) {
		vector< pair<int, int> > temp = com;
		temp.push_back(block_list[i]);
		count++;
		combinationCheck(block_list, temp, boom_num, count, all_combination);
	}
	return;
}

//�� ��忡 ������ ��� ��带 ���ϴ� �Լ�
vector< vector< vector<int> > > check(vector< vector<int> > temp_map) {
	vector< vector< vector<int> > > check_list;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (temp_map[y][x] > 0) { // ���̳� ������� �ƴ� �ֺ� ��ź ������ ���� ĭ�� ������
				int boom_num = temp_map[y][x]; // �ֺ� ��ź ���� ����
				int already_boom = 0; // �̹� �ֺ��� �ִ� ��ź ���� ī��Ʈ�� ����

				//�˻��������
				int min_x = x;
				int min_y = y;
				int max_x = x;
				int max_y = y;
				if (min_x > 0) min_x--;
				if (min_y > 0) min_y--;
				if (max_x < 4) max_x++;
				if (max_y < 4) max_y++;
				
				//�ֺ� ��ź ���� ī��Ʈ
				for (int temp_y = min_y; temp_y <= max_y; temp_y++) {
					for (int temp_x = min_x; temp_x <= max_x; temp_x++) {
						if (temp_map[temp_y][temp_x] == -2) already_boom++;
					}
				}
				temp_map[y][x] = 0; //�˻��� ��ź ������ �����ִ� ĭ�� 0���� ����(���߿� �˻�����ڸ��� �����ϱ�����)

				//�ֺ��� �̹� �ִ� ��ź�� ������ �־���ϴ� ��ź�� �������� ������
				if (already_boom < boom_num) {
					boom_num -= already_boom;
					//��ź�� ���� �� �ִ� ���� ��ġ ã��
					vector< pair<int, int> > block_list;
					for (int temp_y = min_y; temp_y <= max_y; temp_y++) {
						for (int temp_x = min_x; temp_x <= max_x; temp_x++) {
							if (temp_map[temp_y][temp_x] == -1) {
								block_list.push_back(pair<int, int>(temp_y, temp_x));
							}
						}
					}

					

					//ã�� ���鿡 ��ź�� ���� �� �ִ� ��� ����� �� ���ϱ�
					//== block_list.siye() ���� ���� �߿��� boom_num���� ��ź�� ���� ��� ��� ���ϱ�
					vector< pair<int, int> > com;
					vector< vector< pair<int, int> > > all_combination;
					combinationCheck(block_list, com, boom_num, 0, &all_combination);
					for (int i = 0; i < all_combination.size(); i++) {
						vector< vector<int> > temptemp_map = temp_map;
						for (int j = 0; j < all_combination[i].size(); j++) {
							if (temptemp_map[all_combination[i][j].first][all_combination[i][j].second] != -3)
							{
								temptemp_map[all_combination[i][j].first][all_combination[i][j].second] = -2;
							}
						}
						for (int temp_y = min_y; temp_y <= max_y; temp_y++) {
							for (int temp_x = min_x; temp_x <= max_x; temp_x++) {
								if (temptemp_map[temp_y][temp_x] == -1) {
									temptemp_map[temp_y][temp_x] = -3;
								}
							}
						}
						check_list.push_back(temptemp_map);
						//printMap(temptemp_map);
					}
					

				}
				else {
					vector< vector<int> > temptemp_map = temp_map;
					for (int temp_y = min_y; temp_y <= max_y; temp_y++) {
						for (int temp_x = min_x; temp_x <= max_x; temp_x++) {
							if (temptemp_map[temp_y][temp_x] == -1) {
								temptemp_map[temp_y][temp_x] = -3;
							}
						}
					}
					check_list.push_back(temptemp_map);
					//printMap(temp_map);
				}
				//��� ����� �� ����
				return check_list;
			}
		}
	}
	//���̻� �˻��� ĭ�� ������ ���
	if (mapCheck(temp_map) == true) { //���� ������ ����ϸ�
		printMap(temp_map);
		result_count++;
		//��� ������ ��ź ���� ���ϱ�
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (temp_map[y][x] == -2) {
					result[y][x]++;
				}
			}
		}
	}
	return check_list;
}

void bfs() { 
	queue< vector< vector<int> > > q;
	q.push(map);
	while (!q.empty()) {
		//ť���� ���� �տ��ִ� ��� �̱�
		vector< vector<int> > temp_map = q.front(); 
		q.pop();

		//���� ���� ����Ǿ��ִ� ��� �ڽ� ��带 ť�� �ֱ�
		vector< vector< vector<int> > > check_list = check(temp_map);
		for (int i = 0; i < check_list.size(); i++) {
			q.push(check_list[i]);
		}

	}
}

void dfs() {
	stack< vector< vector<int> > > s;
	s.push(map);
	while (!s.empty()) {
		//���ÿ��� ���� �����ִ� ��� �̱�
		vector< vector<int> > temp_map = s.top();
		s.pop();

		//���� ���� ����Ǿ��ִ� ��� ��带 ���ÿ� �ֱ�
		vector< vector< vector<int> > > check_list = check(temp_map);
		for (int i = 0; i < check_list.size(); i++) {
			s.push(check_list[i]);
		}

	}
}

void main()
{
	bfs();
	cout << "�� " << result_count << "���� ����� ��" << "\n\n";

	cout << "���:" << '\n';
	printMap(result);
}