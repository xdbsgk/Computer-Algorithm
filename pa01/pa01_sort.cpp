#include <iostream>
#include <vector>
using namespace std;

// 1. 힙 정렬 함수
void heapify(vector<int>& arr, int n, int i) {
    int st = i;
    int lc = 2*i + 1;
    int rc = 2*i + 2;
    if (lc < n && arr[lc] <= arr[st]) {
        st = lc;
    }
    if (rc < n && arr[rc] <= arr[st]) {
        st = rc;
    }
    if (st != i) {
        swap(arr[i], arr[st]);
        heapify(arr, n, st);
    }
}
void heap_sort(vector<int>& arr, int k) {
    int n = arr.size();
    for (int i = n/2-1; i>=0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n-1; i>n-k-1; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 2. 퀵 정렬 함수
int coun = 0;
bool flag = false;
void quickSort(vector<int>& arr, int start, int end, int k) {
	int pivot = start;
	int left = pivot + 1;
    int right = end;
	if (start >= end)
		return;
    coun = coun+ 1;
	while (left <= right) {
		while (left <= end && arr[left] <= arr[pivot]) {
            left++;
		}
        while (right > start && arr[right] > arr[pivot]) {
            right--;
        }
		if (left < right) {
            swap(arr[left], arr[right]);
		}
		else {
            swap(arr[pivot], arr[right]);
		}
	}
    if (coun == k) {
        for (int i = 0; i < arr.size(); i++) {
		    cout << arr[i] << endl;
            flag = true;
	    }
    }
	quickSort(arr, start, right - 1, k);
	quickSort(arr, right + 1, end, k);
}

int main() {
    int mode, k;
    cin >> mode >> k;
    int N;
    cin >> N;
    vector<int> v;
    for (int i=0; i<N; i++) {
        int e;
        cin >> e;
        v.push_back(e);
    }
    switch (mode)
    {
    // 1. 삽입 정렬
    case 1:
        {
            int i, key, j, cnt=0;
            for (i = 1; i < N; i++) {
                key = v[i];
                j = i - 1;
                while (j>=0 && v[j]>key) {
                    cnt++;
                    v[j + 1] = v[j];
                    j = j-1;
                }
                if (j+1 != 0) {
                    cnt++;
                }
                v[j + 1] = key;
                if (i == k) {
                    cout << cnt << endl;
                }
            }
        }
        break;
    // 2. 선택 정렬
    case 2:
        {
            for (int i=0; i<N-1; i++) {
                int minElement = i;
                for (int j=i+1; j<N; j++) {
                    if (v[j]< v[minElement]) {
                        minElement = j;
                    }
                }
                swap(v[i], v[minElement]);
                if (i == k-1) {
                    for (int x : v) {
                        cout << x << endl;
                    }
                }
            }
        }
        break;
    // 3. 힙 정렬
    case 3:
        {
            heap_sort(v, k);
            for (int i=0; i<N-k; i++) {
                cout << v[i] << endl;
            }
        }
        break;
    // 4. 퀵 정렬
    case 4:
        {
            quickSort(v, 0, N-1, k);
            if (!flag) {
                for (int i=0; i<N; i++) {
                    cout << v[i] << endl;
                }
            }
        }
        break;
    default:
        cout << endl;
        break;
    }
    return 0;
}