#include <iostream>
#include <utility>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x7f7f7f7f;

int Manhattan(pair<int, int> a, pair<int, int> b) { return abs(b.first - a.first) + abs(b.second - a.second); }
int Euclidean(pair<int, int> a, pair<int, int> b) { return static_cast<int>(sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2))); }
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

bool is_zero(pair<int, int> point, const vector<pair<int, int>>& zero) { return find(zero.begin(), zero.end(), point) != zero.end(); }

int main() {
    // input
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
    } // end of input

    vector<vector<int>> g_s(m, vector<int>(n, INF));
    vector<vector<int>> f_s(m, vector<int>(n, INF));
    vector<vector<pair<int, int>>> x(m, vector<pair<int, int>>(n, {-1, -1}));

    vector<vector<bool>> in_cl(m, vector<bool>(n, false));
    vector<vector<bool>> in_ol(m, vector<bool>(n, false));
    in_ol[s.first][s.second] = true;
    g_s[s.first][s.second] = 0;
    f_s[s.first][s.second] = f(s, s, t);

    vector<pair<int, int>> open_list = {s};
    while (!open_list.empty()) {

        int minF = INF;
        pair<int, int> curr;
        for (auto& p : open_list) {
            if (f_s[p.first][p.second] < minF) {
                minF = f_s[p.first][p.second];
                curr = p;
            }
        }

        if (curr == t) {
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

        open_list.erase(find(open_list.begin(), open_list.end(), curr));

        in_ol[curr.first][curr.second] = false;
        in_cl[curr.first][curr.second] = true;

        vector<pair<int, int>> adjacent_point = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        for (const auto& p : adjacent_point) {
            pair<int, int> neigh = {curr.first + p.first, curr.second + p.second};
            if (!in_bounds(neigh, m, n)) continue;
            if (is_blocked(neigh, ob)) continue;
            if (is_zero(neigh, zero)) continue;
            int temp_g = g_s[curr.first][curr.second] + 1;
            if (in_cl[neigh.first][neigh.second] && temp_g >= g_s[neigh.first][neigh.second]) continue;
            if (!in_ol[neigh.first][neigh.second] || temp_g < g_s[neigh.first][neigh.second]) {
                x[neigh.first][neigh.second] = curr;
                g_s[neigh.first][neigh.second] = temp_g;
                f_s[neigh.first][neigh.second] = temp_g + f(neigh, s, t);
                if (!in_ol[neigh.first][neigh.second]) {
                    open_list.push_back(neigh);
                    in_ol[neigh.first][neigh.second] = true;
                }
            }
        }
    }
    return 0;
}
