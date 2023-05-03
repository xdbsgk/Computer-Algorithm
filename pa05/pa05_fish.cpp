#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
bool correct(vector<int>&);
vector<int> flip(int, vector<int>);

int main() {
    int N, order;
    cin >> N;                                       // 입력
    for (int i=0; i<5; i++) {
        vector<int> fish;
        for (int j=0; j<N; j++) {
            cin >> order;
            fish.push_back(order);
        }
        bool is_over = true;
        if (correct(fish)) {
            cout << "zero" << endl;
        } else {
            vector<int> new_fish;
            for (int a=0; a<fish.size(); a++) {     // a = 처음부터 순서대로 뒤집기
                new_fish = flip(a, fish);
                if (correct(new_fish)) {
                    cout << "one" << endl;
                    is_over = false; break;
                } else {
                    new_fish = flip(0, new_fish);   // 일치하지 않으면 한번 더 뒤집기
                    if (correct(new_fish)) {
                        cout << "two" << endl;
                        is_over = false; break;
                    }
                }
            }
        }   if (is_over) cout << "over" << endl;        // 2번 했는데 안되면 over 출력
    }
    return 0;
}

// 순서가 일치하는지 확인하는 함수
bool correct(vector<int>& fish) {
    for (int i=1; i<=fish.size(); i++) {
        if (i != fish[i-1]) return false;
    } return true;
}

// 붕어빵 뒤집기 함수
vector<int> flip(int i, vector<int> v) {
    for (int j=i; j<v.size(); j++) {                        // 받아온 시작 지점부터 뒤집기 시도
        if (v[j] != j+1) {                                  // 해당 지접의 값이 원래 값이 아니라면
            int k=0;
            for (k=0; k<v.size(); k++) {                    // 그 값과 절대값이 같은 다른 곳 찾기
                if (j+1 == v[k] || j+1 == (-1)*v[k]) break;
            }
            if (k < j) {                                    // 찾은 곳이 해당 지점보다 앞쪽이라면
                for (int l=k; l<j+1; l++) {                 // 찾은 곳 부터 해당 지점까지 뒤집기
                    v[l] *= -1;
                }
                reverse(v.begin()+k, v.begin()+j+1);
                return v;                
            } else if (k > j) {                             // 찾은 곳이 해당 지점보다 뒤쪽이라면
                for (int l=j; l<k+1; l++) {                 // 헤딩 지점부터 찾은 곳까지 뒤집기
                    v[l] *= -1;
                }
                reverse(v.begin()+j, v.begin()+k+1);
                return v;
            } else {                                        // 찾은 곳 == 헤당 지점일 경우 부호만 반대
                v[k] *= -1;
                return v;
            }
        }
    }
    return v;
}

