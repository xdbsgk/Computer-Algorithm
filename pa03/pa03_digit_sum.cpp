#include <iostream>
#include <cstring>
using namespace std;

// 각 자리 수의 합을 계산하는 함수
int digitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n%10;
        n /= 10;
    }
    return sum;
}

int main() {
    int num;
    cin >> num;

    int maxSum = 0;
    pair<int, int> max_pair;

    // 두 수는 각각 i와 j. 012 ~ 987의 바깥 값들은 중복되니 제외하고 본다. 
    for (int i=12; i<min(num, 988); i++) {
        for (int j=i+1; j<min(num, 988); j++) {
            if (i<100 && j<100) continue;                               // 1. 두 수 모두 2자리인 경우 제외
            if ((i<100 && i%10==0) || (j<100 && j%10==0)) continue;     // 2. 두 수 중, 2자리수인데 일의자리수가 0인 수 제외 (0 중복)
            if (i+j == num && to_string(i).find_first_of(to_string(j)) == string::npos) {   // 합이 주어진 수와 일치하며, i에 j의 수가 포함되는지 확인
                // ** 6명 중 중복된 숫자 있는지 체크 **
                int isDuplicate = false;
                int digits[10] = {0};
                if (i<100) {            // 우선 100보다 작은 경우, 백의 자리 수가 0 이므로 배열의 0번째 원소에 숫자가 있음을 표시함
                    digits[0] = 1;
                }
                int temp = 1000*i + j;  // 두 수를 합산하여 계산해야 하므로 i*1000
                while(temp>0) {         // 각 자리 수를 배열에 체크
                    int digit = temp % 10;
                    digits[digit]++;
                    if (digits[digit]>1) {  // 중복되면 2 이상이므로 걸러짐
                        isDuplicate = true;
                        break;
                    }
                    temp /= 10;
                }
                if (isDuplicate) continue;
                int sumDigit = digitSum(i) + digitSum(j);
                if (sumDigit == maxSum) continue;   // 현재 sum과 maxsum 같을시 업데이트 안 함. But 생략 가능한 코드임
                if (sumDigit > maxSum) {            // 두 수의 자리수 합이 더 크다면 업데이트
                    maxSum = sumDigit;
                    max_pair = make_pair(i, j);
                }
            }
        }
    }

    if (maxSum == 0) {                              // 두 수의 합으로 나타낼 수 없을 시 -1 출력
        cout << -1 << endl;
    } else {
        string new_i;
        if (max_pair.first < 100) {                 // 100보다 작으면 두자리수 숫자. 0 추가
            new_i = to_string(max_pair.first);
            new_i = "0" + new_i;
            cout << new_i << " " << max_pair.second << " " << maxSum << endl;
        } else {
            cout << max_pair.first << " " << max_pair.second << " " << maxSum << endl;
        }
    }

    return 0;
}
