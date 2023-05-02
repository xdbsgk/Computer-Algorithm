#include <iostream>
#include <vector>
using namespace std;

int maxSum(vector<int>& v) {
    int max = v[0];         // 모두 음수인 경우를 고려해,
    int newMax = v[0];      // 배열 첫 값을 최대합으로 먼저 지정해 줌
    for (int i=1; i<v.size(); i++) {
        newMax = (v[i] > newMax+v[i]) ? v[i] : newMax+v[i]; // newmax와 v[i] 비교해 더 큰 값으로 초기화
        if (newMax > max) {
            max = newMax;
        }
    }
    return max;
}
int main() {
    int P, N, M;
    cin >> P >> N >> M;
    vector<int> research;
    for (int i=0; i<N; i++) {
        research.push_back(P);
    }
    for (int i=0; i<M; i++) {
        int n;
        cin >> n;
        for (int j=0; j<n; j++) {
            int start, end, noise;
            cin >> start >> end >> noise;
            while(start != end) {           // 각 시간대 noise 계산
                research[start] += noise;
                start++;
            }
        }
    }
    int maxResearch = maxSum(research);
    cout << maxResearch << endl;
    return 0;
}
