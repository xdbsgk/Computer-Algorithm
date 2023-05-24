#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <unordered_map>
using namespace std;

int RK(string P, string T) {            // RK 함수
    int compare = 0;
    const int p = 30011;
    int Plength = P.length();
    int Tlength = T.length();
    int hashP = 0, hashT = 0;

    for (int i=0; i<Plength; i++) {      // 패턴 문자열 P의 해시값과 텍스트 문자열 T의 처음 부분의 해시값 계산
        hashP = (hashP * p + P[i]) % p;
        hashT = (hashT * p + T[i]) % p;
    }

    for (int i=0; i<=Tlength-Plength; i++) {
        if (hashP == hashT) {
            bool match = true;
            for (int j = 0; j < Plength; j++) {     compare++;      // 해시값이 일치하는 경우 문자열을
                if (P[j] != T[i + j]) {                             // 비교하여 정확한 매칭 여부 확인
                    match = false;
                    break;
                }
            }
            if (match) {
                compare ++;
            }
        }
        if (i<Tlength-Plength) {                                // 다음 위치로 이동하기 위해 해시값 업데이트
            hashT = ((p * (hashT - T[i] * int(pow(p, Plength - 1)))) + T[i + Plength]) % p;
            if (hashT < 0) {
                hashT += p;
            }
        }
    }
    return compare;
}


vector<int> LPS(string P) {         // KMP - LPS 함수
    int Plength = P.length();       // LPS 테이블 생성 함수
    vector<int> lps(Plength);
    int len = 0, i = 1;
    while(i < Plength) {
        if (P[i] == P[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len-1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int KMP(string P, string T) {       // KMP 함수
    int compare = 0;
    int Plength = P.length();
    int Tlength = T.length();

    vector<int> lps = LPS(P);       // LPS 테이블 생성
    int i=0, j=0;
    while(i < Tlength) {
        compare++;
        if (P[j] == T[i]) {
            i++;    j++;
            compare++;
            if (j == Plength) {
                j = lps[j-1];
            }
        } else {
            if (j != 0) {
                j = lps[j-1];
            } else {
                i++;
            }
        }
    }
    return compare;
}

unordered_map<char, int> build_bad_char_table(const string& pattern) {  // Bad Character 테이블 생성 함수
    unordered_map<char, int> bad_char;
    int pattern_length = pattern.length();

    for (int i = 0; i < pattern_length - 1; i++) {
        bad_char[pattern[i]] = pattern_length - i - 1;
    }

    return bad_char;
}

int BM(const string& pattern, const string& text) {     // BM 함수
    int pl = pattern.length();
    int text_length = text.length();
    unordered_map<char, int> bad_char = build_bad_char_table(pattern);
    int compare = 0;

    int i = pl - 1;
    int j = pl - 1;

    while (i < text_length) {
        compare++;
        if (pattern[j] == text[i]) {
            if (j == 0) {
                i += pl;
            } else {
                i--;
                j--;
            }
        } else {
            char c = text[i];
            if (bad_char.find(c) != bad_char.end()) {
                i += max(bad_char[c], pl - j);
            } else {
                i += pl;
            }

            j = pl - 1;
        }
    }

    return compare;
}

vector<int> build_lps_table(const string& pattern) {       // BM - LPS 테이블 생성 함수
    int pl = pattern.length();
    vector<int> lps(pl);
    int length = 0;
    int i = 1;

    while (i < pl) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

int main() {
    int CompRK=0, CompKMP=0, CompBM=0;
    int nP, nT;
    cin >> nP;
    string P;
    for (int i=0; i<nP; i++) {
        string input;
        cin >> input;
        P += input;
    }
    cin >> nT;
    string T;
    for (int i=0; i<nT; i++) {
        string input;
        cin >> input;
        T += input;
    }

    CompRK = RK(P, T);      // RK 알고리즘 수행
    CompKMP = KMP(P, T);    // KMP 알고리즘 수행
    CompBM = BM(P, T);      // BM 알고리즘 수행

    if (CompRK == CompKMP) {
        if (CompKMP == CompBM)      cout << "0 0 0";
        else if (CompKMP < CompBM)  cout << "0 0 3";
        else if (CompRK > CompBM)   cout << "3 0 0";
    } else if (CompRK == CompBM) {
        if (CompKMP < CompRK)       cout << "2 0 0";
        else if (CompKMP > CompRK)  cout << "0 0 2";
    } else if (CompKMP == CompBM) {
        if (CompRK < CompKMP)       cout << "1 0 0";
        else if (CompRK > CompKMP)  cout << "0 0 1";
    } else if (CompRK < CompKMP) {
        if (CompKMP < CompBM)       cout << "1 2 3";
        else if (CompBM < CompKMP && CompRK < CompBM) cout << "1 3 2";
        else if (CompBM < CompKMP && CompRK > CompBM) cout << "3 1 2";
    } else if (CompKMP < CompRK) {
        if (CompRK < CompBM)        cout << "2 1 3";
        else if (CompRK > CompBM && CompKMP < CompBM) cout << "2 3 1";
        else if (CompRK > CompBM && CompKMP > CompBM) cout << "3 2 1";
    } cout << endl;

    return 0;
}