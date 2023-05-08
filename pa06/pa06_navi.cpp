#include <iostream>
#include <utility>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x7f7f7f7f; // 처음 초기화 할 min 값

int Manhattan(pair<int, int> a, pair<int, int> b) { return abs(b.first - a.first) + abs(b.second - a.second); } // 맨하탄 거리 계산
int Euclidean(pair<int, int> a, pair<int, int> b) { return static_cast<int>(sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2))); } // 유클리드 거리 계산
int f(pair<int, int> now, pair<int, int> s, pair<int, int> t) { // f = g + h 계산
    int g = Manhattan(s, now);
    int h = Euclidean(now, t);
    return g + h;
}
bool in_bounds(pair<int, int> point, int m, int n) {            // 주어진 좌표계 안 값인지 확인
    return point.first >= 0 && point.first < m && point.second >= 0 && point.second < n;
}
bool is_blocked(pair<int, int> point, const vector<pair<pair<int, int>, pair<int, int>>>& ob) {     // 장애물 영역으로 가려진 곳인지 반환
    for (const auto& o : ob) {
        int x1 = min(o.first.first, o.second.first);
        int x2 = max(o.first.first, o.second.first);
        int y1 = min(o.first.second, o.second.second);
        int y2 = max(o.first.second, o.second.second);
        if (point.first >= x1 && point.first <= x2 &&
            point.second >= y1 && point.second <= y2) {
            return true;
        }
    }
    return false;
}

bool is_zero(pair<int, int> point, const vector<pair<int, int>>& zero) { return find(zero.begin(), zero.end(), point) != zero.end(); } // 0인 셀인지 반환

int main() {
    // Input
    int m, n, zero_num, ob_num;
    cin >> m >> n >> zero_num;                  
    vector<pair<int, int>> zero(zero_num);
    for (int i = 0; i < zero_num; i++) {          
        int z;
        cin >> z >> zero[i].first >> zero[i].second;
    }
    char c;
    pair<int, int> s, t;
    cin >> c >> s.first >> s.second;                 
    cin >> c >> t.first >> t.second;                
    string obb;
    cin >> obb >> ob_num;         
    vector<pair<pair<int, int>, pair<int, int>>> ob(ob_num);
    for (int i = 0; i < ob_num; i++) {
        cin >> ob[i].first.first >> ob[i].first.second >> ob[i].second.first >> ob[i].second.second;
    } // End of Input

    vector<vector<int>> g_s(m, vector<int>(n, INF));        // 각 점의 g 값 저장용 벡터
    vector<vector<int>> f_s(m, vector<int>(n, INF));        // 각 점의 f 값 저장용 벡터
    vector<vector<pair<int, int>>> x(m, vector<pair<int, int>>(n, {-1, -1}));   // 이전 점 저장용 벡터

    vector<vector<bool>> in_cl(m, vector<bool>(n, false));  // closed list에 포함되어 있는지
    vector<vector<bool>> in_ol(m, vector<bool>(n, false));  // open list에 포함되어 있는지
    
    in_ol[s.first][s.second] = true;                        // 초기화 작업
    g_s[s.first][s.second] = 0;
    f_s[s.first][s.second] = f(s, s, t);                    // start에서 시작

    vector<pair<int, int>> open_list = {s};                 // open list 만들기
    while (!open_list.empty()) {                            // open list가 빌 때까지 반복

        int minF = INF;
        pair<int, int> curr;
        for (auto& p : open_list) {
            if (f_s[p.first][p.second] < minF) {
                minF = f_s[p.first][p.second];
                curr = p;
            }
        }

        if (curr == t) {                                    // 목표점에 도달할 경우 출력 및 종료
            vector<pair<int, int>> path;
            pair<int, int> p = curr;
            path.push_back(p);
            while (p != s) {
                p = x[p.first][p.second];
                path.push_back(p);
            }
            reverse(path.begin(), path.end());
            cout << g_s[curr.first][curr.second]*3 << "\n";
            return 0;
        }

        open_list.erase(find(open_list.begin(), open_list.end(), curr));    // 도착점 아닐시, (검사완료)오픈리스트에서 삭제

        in_ol[curr.first][curr.second] = false;                             // openlist 제거
        in_cl[curr.first][curr.second] = true;                              // closedlist 추가

        vector<pair<int, int>> adjacent_point = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};     // curr의 상, 하, 좌, 우 값 검사
        for (const auto& p : adjacent_point) {
            pair<int, int> neigh = {curr.first + p.first, curr.second + p.second};      // 각 상하좌우에 대해
            if (!in_bounds(neigh, m, n)) continue;                          // 좌표계 밖 값이면 패스
            if (is_blocked(neigh, ob)) continue;                            // 장애물 내부면 패스
            if (is_zero(neigh, zero)) continue;                             // 0인 셀이면 패스
            int temp_g = g_s[curr.first][curr.second] + 1;                  // 현재 위치(curr)까지의 이동거리 + 이웃까지 거리(1)
            if (in_cl[neigh.first][neigh.second] && temp_g >= g_s[neigh.first][neigh.second]) continue; // 이웃이 closed list 값인 경우 && 이전 계산값이 최단임 => 패스
            if (!in_ol[neigh.first][neigh.second] || temp_g < g_s[neigh.first][neigh.second]) {         // 이웃이 open list 내부에 없음 && 현재 계산값이 최단임 => 갱신
                x[neigh.first][neigh.second] = curr;
                g_s[neigh.first][neigh.second] = temp_g;
                f_s[neigh.first][neigh.second] = temp_g + f(neigh, s, t);
                if (!in_ol[neigh.first][neigh.second]) {        // open list에 인접 좌표도 추가해주기
                    open_list.push_back(neigh);
                    in_ol[neigh.first][neigh.second] = true;
                }
            }
        }
    }
    return 0;
}
