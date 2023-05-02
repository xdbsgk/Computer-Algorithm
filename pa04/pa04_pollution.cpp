#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Func. 다익스트라 알고리즘을 이용하여 최단 경로 구하기
void dijkstra(int start, vector<pair<int, int>> adj[], int* dist) {
    const int INF = 1e9;
    // priority queue 사용 (현재 노드에서 갈 수 있는 노드 저장)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    fill(dist, dist + 20, INF);     // 최단 경로를 담는 배열 초기화 : INF로
    dist[start] = 0;                // 시작 - 자기 자신이므로 0
    pq.push({0, start});            // 시작 노드 및 최단 경로를 pq에 넣기
    while (!pq.empty()) {           // pq가 빌 때까지
        int curr = pq.top().second;
        int curr_dist = pq.top().first;     // 현재 노드까지의 최단경로
        pq.pop();                           // 현재 노드 제거 
        if (dist[curr] < curr_dist) continue;       // 현재 노드보다 큰 값 -> 무시
        for (int i=0; i<adj[curr].size(); i++) {    // 현재 노드와 연결된 모든 노드들에 대해
            int next = adj[curr][i].first;          
            int next_dist = curr_dist + adj[curr][i].second;    // 다음 노드까지의 최단경로
            if (dist[next] > next_dist) {                       // 최단 경로 갱신
                dist[next] = next_dist;
                pq.push({next_dist, next});
            }
        }
    }
}

int main() {
    int N, c1, c2;                                              // 입력
    cin >> N >> c1 >> c2;
    vector<pair<int, int>> adj[20];                             // 인접 리스트
    
    for (int i=0; i<N-1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a-1].push_back({b-1, w});                           // 삽입
        adj[b-1].push_back({a-1, w});
    }

    int dist_c1[20], dist_c2[20], dist[20];
    dijkstra(c1-1, adj, dist_c1);                               // c1으로부터 최단경로 구하기
    dijkstra(c2-1, adj, dist_c2);                               // c2로부터 최단경로 구하기	

    for (int i=0; i<N; i++) {
        dist[i] = min(dist_c1[i], dist_c2[i]);                  // 둘 중 빠른 값으로 저장
    }
    vector<pair<int, int>> sequence;
    for (int i=0; i<N; i++) {
        if (i==c1-1 || i==c2-1) continue;                       // c1, c2 제외한 N-2개의 노드들만
        sequence.push_back({dist[i], i});                       // sequence에 추가
    }
    sort(sequence.begin(), sequence.end());                     // 오름차순 정렬
    for (int i=0; i<sequence.size(); i++) {
        cout << sequence[i].second+1 << endl;                   // 출력
    }
    
    return 0;
}
