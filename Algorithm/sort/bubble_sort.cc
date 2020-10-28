
#include <iostream>
using namespace std;

int bubble_sort(int A[], int N) {
  int sw = 0;
  bool flag = 1;
  for (int i = 0; flag; i++) {
    flag = 0;
    for (int j = N - 1; j >= i + 1; j--) {
      if (A[j] < A[j - 1]) {
        swap(A[j], A[j - 1]);
        flag = 1;
        sw++;
      }
    }
  }
  return sw;
}

int main() {
  int A[100], N, sw;
  cin >> N;

  for (int i = 0; i < N; i++) cin >> A[i];

  sw = bubble_sort(A, N);

  cout << "整理した配列" << '\n';

  for (int i = 0; i < N; i++) {
    if (i) cout << " ";
    cout << A[i];
  }

  cout << endl;
  cout << "交換した回数" << sw << endl;

  return 0;
}
