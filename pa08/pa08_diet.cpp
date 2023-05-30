#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

struct Diet{    // Diet 구조체
    int index;
    int p, f, s, v;
    int price;
};

Diet diet_min;                      // 최소 권장량
vector<Diet> diet_list;             // 주어진 재료 list
vector<Diet> sum;                   // 재료들의 각 요소 합 저장
vector<Diet> select_list;           // 현재 선택한 재료리스트 저장
vector<vector<Diet>> select_lists;  // 가능한 현재 리스트 저장 (2차원 리스트)

int MIN_PRICE = INT_MAX;            // 최소 가격 저장

void calculate(Diet diet) {
    if (diet_min.p <= diet.p && diet_min.f <= diet.f && diet_min.s <= diet.s && diet_min.v <= diet.v) { // 주어진 권장량 충족 확인
        vector<Diet> tmp = select_list;
        sort(tmp.begin(), tmp.end(), [](const Diet& a, const Diet& b) { return a.index < b.index; });
        if (MIN_PRICE > diet.price) {           // 현재 가격이 최소 가격보다 작으면 결과 갱신
            MIN_PRICE = diet.price;
            select_lists.clear();
            select_lists.push_back(tmp);
            return ;
        } else if (MIN_PRICE == diet.price) {   // 현재 가격이 최소 가격과 같으면 결과 추가
            select_lists.push_back(tmp);
            return ;
        } else 
            return ;
    }
    int n = diet.index;
    if (n >= diet_list.size())      // 재료 리스트를 모두 탐색한 경우 종료
        return ;
    if (diet.price > MIN_PRICE)     // 현재 가격이 최소 가격보다 큰 경우 종료
        return;
    if (diet.p+sum[n].p < diet_min.p ||     // 현재 권장량에 현재 재료를 추가했을 때,
        diet.f+sum[n].f < diet_min.f ||     // 최소 권장량을 충족하지 못하는 경우 종료
        diet.s+sum[n].s < diet_min.s ||
        diet.v+sum[n].v < diet_min.v)
        return ;
    // 현재 재료를 선택한 경우
    diet.p += diet_list[n].p;    diet.f += diet_list[n].f;    diet.s += diet_list[n].s;    diet.v += diet_list[n].v;    diet.price += diet_list[n].price;
    select_list.push_back(diet_list[n]);
    diet.index = n+1;
    calculate(diet);
    // 현재 재료를 선택하지 않은 경우
    diet.p -= diet_list[n].p;    diet.f -= diet_list[n].f;    diet.s -= diet_list[n].s;    diet.v -= diet_list[n].v;    diet.price -= diet_list[n].price;
    select_list.pop_back();
    diet.index = n+1;
    calculate(diet);
}   

int main() {
    int k;
    cin >> k;
    Diet diet;
    cin >> diet_min.p >> diet_min.f >> diet_min.s >> diet_min.v;

    for (int i=0; i<k; i++) {
        diet.index=i+1;
        cin >> diet.p >> diet.f >> diet.s >> diet.v >> diet.price;
        diet_list.push_back(diet);
    }
    // 가격 기준 정렬
    sort(diet_list.begin(), diet_list.end(), [](const Diet& a, const Diet& b) { return a.price < b.price; });

    Diet tmp_sum;   // 재료 합 미리 계산
    tmp_sum.p=0; tmp_sum.f=0; tmp_sum.s=0; tmp_sum.v=0;
    for (int i=0; i<k; i++) {
        tmp_sum.p += diet_list[i].p;  tmp_sum.f += diet_list[i].f;  tmp_sum.s += diet_list[i].s;  tmp_sum.v += diet_list[i].v;
    }
    sum.push_back(tmp_sum);
    for (int i=0; i<k-1; i++) {
        tmp_sum.p -= diet_list[i].p;  tmp_sum.f -= diet_list[i].f;  tmp_sum.s -= diet_list[i].s;  tmp_sum.v -= diet_list[i].v;
        sum.push_back(tmp_sum);
    }

    diet.index=0; diet.p=0; diet.f=0; diet.s=0; diet.v=0; diet.price=0;
    calculate(diet);

    vector<Diet> best_choice;       // 최적의 선택 결과 추출
    if (select_lists.empty()) cout << 0 << endl;
    int sel_size = select_lists.size();
    int E = 0;
    for (int i=0; i<sel_size; i++) {
        int Etmp = 0;
        for (int j=0; j<sel_size; j++) {
            Etmp += select_lists[i][j].p + select_lists[i][j].f + select_lists[i][j].s + select_lists[i][j].v;
        }
        if (E < Etmp) {
            E = Etmp;
            best_choice.resize(select_lists[i].size());
            copy(select_lists[i].begin(), select_lists[i].end(), best_choice.begin());
        }
    }
    for (auto food : best_choice) {     // 결과 출력
        cout << food.index << " ";
    } cout << endl;

    return 0;
}