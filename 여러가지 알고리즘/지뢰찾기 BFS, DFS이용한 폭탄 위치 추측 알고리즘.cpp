#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector< vector<int> > map = {  // -3 폭탄이 있을 수 없는 벽, -2 폭탄, -1 벽, 0 빈공간 이외 숫자: 주변 폭탄 갯수
	{ -1, -2, -2, -2, -1 },
	{ -1, 3, 3, 4, -1 },
	{ -1, 1, 0, 2, -1 },
	{ -1, 1, 1, 2, -1 },
	{ -1, -1, -1, -1, -1} };

vector< vector<int> > result(5, vector<int>(5, 0)); // 결과값 저장할 배열
int result_count = 0; // 총 몇개의 경우의 수가 생기는지



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

bool mapCheck(vector< vector<int> > temp_map) { // 지뢰찾기게임 정답이 맞는지 확인
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (map[y][x] > 0) {
				int num = map[y][x];

				//검사범위설정
				int min_x = x;
				int min_y = y;
				int max_x = x;
				int max_y = y;
				if (min_x > 0) min_x--;
				if (min_y > 0) min_y--;
				if (max_x < 4) max_x++;
				if (max_y < 4) max_y++;

				//주변 폭탄 갯수 카운트
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

//가능한 모든 조합 구하기(재귀)
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

//한 노드에 인접한 모든 노드를 구하는 함수
vector< vector< vector<int> > > check(vector< vector<int> > temp_map) {
	vector< vector< vector<int> > > check_list;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (temp_map[y][x] > 0) { // 벽이나 빈공간이 아닌 주변 폭탄 갯수가 적힌 칸을 만나면
				int boom_num = temp_map[y][x]; // 주변 폭탄 갯수 저장
				int already_boom = 0; // 이미 주변에 있는 폭탄 갯수 카운트할 변수

				//검사범위설정
				int min_x = x;
				int min_y = y;
				int max_x = x;
				int max_y = y;
				if (min_x > 0) min_x--;
				if (min_y > 0) min_y--;
				if (max_x < 4) max_x++;
				if (max_y < 4) max_y++;
				
				//주변 폭탄 갯수 카운트
				for (int temp_y = min_y; temp_y <= max_y; temp_y++) {
					for (int temp_x = min_x; temp_x <= max_x; temp_x++) {
						if (temp_map[temp_y][temp_x] == -2) already_boom++;
					}
				}
				temp_map[y][x] = 0; //검사한 폭탄 갯수가 적혀있는 칸은 0으로 만듦(나중에 검사안한자리와 구별하기위해)

				//주변에 이미 있는 폭탄의 갯수가 있어야하는 폭탄의 갯수보다 적을때
				if (already_boom < boom_num) {
					boom_num -= already_boom;
					//폭탄이 있을 수 있는 블럭들 위치 찾기
					vector< pair<int, int> > block_list;
					for (int temp_y = min_y; temp_y <= max_y; temp_y++) {
						for (int temp_x = min_x; temp_x <= max_x; temp_x++) {
							if (temp_map[temp_y][temp_x] == -1) {
								block_list.push_back(pair<int, int>(temp_y, temp_x));
							}
						}
					}

					

					//찾은 블럭들에 폭탄이 있을 수 있는 모든 경우의 수 구하기
					//== block_list.siye() 개의 블럭들 중에서 boom_num개의 폭탄이 있을 모든 경우 구하기
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
				//모든 경우의 수 리턴
				return check_list;
			}
		}
	}
	//더이상 검사할 칸이 없으면 출력
	if (mapCheck(temp_map) == true) { //정답 조건을 통과하면
		printMap(temp_map);
		result_count++;
		//결과 변수에 폭탄 갯수 더하기
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
		//큐에서 가장 앞에있는 노드 뽑기
		vector< vector<int> > temp_map = q.front(); 
		q.pop();

		//뽑은 노드와 연결되어있는 모든 자식 노드를 큐에 넣기
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
		//스택에서 가장 위에있는 노드 뽑기
		vector< vector<int> > temp_map = s.top();
		s.pop();

		//뽑은 노드와 연결되어있는 모든 노드를 스택에 넣기
		vector< vector< vector<int> > > check_list = check(temp_map);
		for (int i = 0; i < check_list.size(); i++) {
			s.push(check_list[i]);
		}

	}
}

void main()
{
	bfs();
	cout << "총 " << result_count << "개의 경우의 수" << "\n\n";

	cout << "결과:" << '\n';
	printMap(result);
}