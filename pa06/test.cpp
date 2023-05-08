#include <iostream>
#include <utility>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x7f7f7f7f;

int Manhattan(pair<int, int> a, pair<int, int> b) {
    return abs(b.first - a.first) + abs(b.second - a.second);
}

int Euclidean(pair<int, int> a, pair<int, int> b) {
    return sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second));
}

int f(pair<int, int> now, pair<int, int> s, pair<int, int> t) {
    int g = Manhattan(s, now);
    int h = Euclidean(now, t);
    return g + h;
}

bool in_bounds(pair<int, int> point, int m, int n) {
    return point.first >= 0 && point.first < m && point.second >= 0 && point.second < n;
}

bool is_blocked(pair<int, int> point, const vector<pair<pair<int, int>, pair<int, int>>>& ob) {
    for (const auto& o : ob) {
        if (point.first >= o.first.first && point.first <= o.second.first 
            && point.second >= o.first.second && point.second <= o.second.second) {
            return true;
        }
    }
    return false;
}

bool is_zero(pair<int, int> point, const vector<pair<int, int>>& zero) {
    return find(zero.begin(), zero.end(), point) != zero.end();
}

int main() {
    
    // input
    int m, n, zero_num, ob_num;
    cin >> m >> n >> zero_num;                          // m, n,zero 개수 입력받기
    vector<pair<int, int>> zero(zero_num);
    for (int i = 0; i < zero_num; i++) {                // zero인 좌표 입력받기
        int z;
        cin >> z >> zero[i].first >> zero[i].second;
    }
    char c;
    pair<int, int> s, t;
    cin >> c >> s.first >> s.second;                    // 시작점 s 입력
    cin >> c >> t.first >> t.second;                    // 목표점 t 입력
    string obb;
    cin >> obb >> ob_num;                               // 장애물 개수 입력
    vector<pair<pair<int, int>, pair<int, int>>> ob(ob_num);
    for (int i = 0; i < ob_num; i++) {                  // 장애물 입력
        cin >> ob[i].first.first >> ob[i].first.second >> ob[i].second.first >> ob[i].second.second;
    }

    vector<pair<int, int>> open_list;       // 조사하지 않은 노드
    vector<pair<int, int>> closed_list;     // 조사한 노드
    open_list.push_back(s);                 // 초기화 : open_list에 시작점 넣기

   while(!open_list.empty()) {
    // 1. open_list 에서 f 값이 가장 작은 점 선택하기 (current node)
        pair<int, int> curr;
        int minF = INF;
        for (auto p : open_list) {
            int f_val = f(p, s, t);
            if (f_val < minF) {
                curr = p;
                minF = f_val;
            }   
        }
        // 2. 현재 노드와 목표점을 비교, 같다면 구한 minF 출력
        if (curr == t) {
            cout << minF << endl;
            return 0;
        }

        // 3. curr와 인접한 점들 중에서 open_list에 없는 점은 open_list에 추가하고 f값 계산
        vector<pair<int, int>> neighbors = {
                {curr.first-1, curr.second},   // 상
                {curr.first+1, curr.second},   // 하
                {curr.first, curr.second-1},   // 좌
                {curr.first, curr.second+1}    // 우
        };
        for (auto nb : neighbors) {
            if (in_bounds(nb, m, n) && !is_blocked(nb, ob) && !is_zero(nb, zero) && find(closed_list.begin(), closed_list.end(), nb) == closed_list.end()) {
                int f_val = f(nb, s, t);
                open_list.push_back(nb);
                f_values[nb] = f_val;
                g_values[nb] = g_values[curr] + 1;
                parent[nb] = curr;
            }
        }

        // 4. 현재 노드를 closed_list에 추가
        closed_list.push_back(curr);
    }

    return 0;
}