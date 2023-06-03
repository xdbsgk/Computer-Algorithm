#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <climits>
using namespace std;

int n; // 주문 수
vector<vector<int>> table; // 칠판 표
vector<pair<pair<int, int>, pair<int, int>>> Point;
vector<int> optimalPath; // 최종 경로
int minDistance = INT_MAX; // 최종 경로의 길이

int calculateDistance(int x1, int y1, int x2, int y2) { // 맨하튼 거리 구하기
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<int> get_order(const vector<int>& v1, const vector<int>& v2) { // 사전식 순서 구하는 함수
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] < v2[i]) {
            return v1;
        } else if (v1[i] > v2[i]) {
            return v2;
        }
    }
    return v1;
}

// 백트래킹 함수
void backtracking(int total, vector<bool>& visitedOrders, int cur, int distance, vector<int>& cur_box, vector<int>& path) {
    // 전부 방문했을 경우 ..
    if (visitedOrders[cur]==true && total==2*n) {
        if (distance < minDistance) {
            minDistance = distance;
            optimalPath = path;
        } else if (distance == minDistance) { // 길이 같을 시 사전순 함수로 재정렬해주기
            vector<int> newOrder = get_order(optimalPath, path);
            if (newOrder != optimalPath) {
                optimalPath = newOrder;
            }
        }
        return;
    }

   if (cur_box.size() < 2) { // 배달박스에 물건 두개 없을 때 탐색
        for (int i=1; i<=n; i++) {
            if (!visitedOrders[i] && i != cur) {
                visitedOrders[i] = true;
                cur_box.push_back(i);
                path.push_back(i);

                backtracking(total+1, visitedOrders, i, distance+table[cur][i], cur_box, path);
                
                cur_box.pop_back();
                path.pop_back();
                visitedOrders[i] = false;
            }
        }
   }

   for (int i=0; i<cur_box.size(); i++) { // 배달박스 안에 집으로 배달할 물건 탐색
       int order = cur_box[i]; // 박스에서 지우기전에 저장해놓기
       int order_home = cur_box[i]+n; // 집 인덱스 저장해놓기
       path.push_back((-1)*cur_box[i]);
       visitedOrders[order_home] = true;
       cur_box.erase(cur_box.begin()+i);

       backtracking(total+1, visitedOrders, order_home, distance+table[cur][order_home], cur_box, path);

       path.pop_back();
       visitedOrders[order_home] = false;
       cur_box.insert(cur_box.begin()+i, order);
   }
}


int main() {
    // 입력
    cin >> n;
    Point.resize(n);
    for (int i=0; i<n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        Point[i].first = make_pair(a, b);
        Point[i].second = make_pair(c, d);
    }
    table.resize(2*n+1, vector<int>(2*n+1));

    // 테이블 생성하기 (칠판 표 그대로)
    for (int i=0; i<2*n+1; i++) {
        for (int j=0; j<2*n+1; j++) {
            if (i == j) {
                table[i][j] = 0;
            } else {
                int x1, y1, x2, y2;
                if (i == 0) {
                    x1 = 500; y1 = 500;
                } else {
                    if (i <= n) {
                        x1 = Point[i-1].first.first; y1 = Point[i-1].first.second;
                    } else {
                        x1 = Point[i-n-1].second.first; y1 = Point[i-n-1].second.second;
                    }
                }
                if (j == 0) {
                    x2 = 500; y2 = 500;
                } else {
                    if (j <= n) {
                        x2 = Point[j-1].first.first; y2 = Point[j-1].first.second;
                    } else {
                        x2 = Point[j-n-1].second.first; y2 = Point[j-n-1].second.second;
                    }
                }
                table[i][j] = calculateDistance(x1, y1, x2, y2);
            }
        }
    }

    vector<bool> visitedOrders;
    visitedOrders.resize(2*n+1);
    vector<int> cur_box;
    vector<int> path;
    backtracking(0, visitedOrders, 0, 0, cur_box, path);
    
    // 출력
    for (int i=0; i<optimalPath.size(); i++) {
        cout << optimalPath[i] << " ";
    } cout << endl;
    cout << minDistance << endl;
    return 0;
}