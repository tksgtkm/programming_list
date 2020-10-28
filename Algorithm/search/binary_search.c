
#include <stdio.h>

int A[1000000], n;

/* 二文探索 */

int binary_search(int key) {
  int left = 0;
  int right = n;
  int mid;
  while (left < right) {
    mid = (left + right) / 2;
    if (key == A[mid]) { // key を発見
      return 1;
    }

    if (key > A[mid]) { // 後半を探索
      left = mid + 1;
    } else if (key < A[mid]){ // 前半を探索
      right = mid;
    }
  }
  return 0;
}

int main() {
  int i, q, k, sum = 0;

  scanf("%d", &n);
  for (i=0; i < n; i++) {
    scanf("%d", &A[i]);
  }

  scanf("%d", &q);
  for (i=0; i < q; i++) {
    scanf("%d", &k);
    if (binary_search(k)) {
      sum++;
    }
  }

  printf("%d\n", sum);

  return 0;
}
