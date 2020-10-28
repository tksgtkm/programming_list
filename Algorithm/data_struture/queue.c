/* ラウンドロビンスケジュールのシュミレートプログラム */

#include <stdio.h>
#include <string.h>
#define LEN 100005

/* プロセスを表す構造体 */
typedef struct pp {
  char name[100];
  int t;
} P;

P Q[LEN];
int head, tail, n;

void enqueue(P x) {
  Q[tail] = x;
  tail = (tail + 1) % LEN;
}

P dequeue() {
  P x = Q[head];
  head = (head + 1) % LEN;
  return x;
}

int min(int a, int b) {
  return a < b ? a : b; /* 最小値を返す */
}

int main() {
  int elpas = 0, c;
  int i, q;
  P u;
  scanf("%d %d", &n, &q);

  /* 全てのプロセスをキューに順番に追加する */
  for (i = 1; i <= n; i++) {
    scanf("%s", Q[i].name);
    scanf("%d", &Q[i].t);
  }

  head = 1;
  tail = n + 1;

  while (head != tail) {
    u = dequeue();
    c = min(q, u.t); /* qまたは必要な時間u.tだけ処理を行う */
    u.t -= c; /* 残りの必要時間を計算 */
    elpas += c;
    if (u.t > 0) enqueue(u); /* 処理が完了していなければキューに追加 */
    else {
      printf("%s %d\n", u.name, elpas);
    }
  }
  return 0;
}
