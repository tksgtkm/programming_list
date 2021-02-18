#include <stdio.h>

#define MAX 10000
#define NIL -1

struct Node {int p, l, r;};
struct Node T[MAX];
int n;

void pre_parse(int u) {
  if (u == NIL) return;
  printf("%d", u);
  pre_parse(T[u].l);
  pre_parse(T[u].r);
}

void in_parse(int u) {
  if (u == NIL) return;
  in_parse(T[u].l);
  printf("%d", u);
  in_parse(T[u].r);
}

void post_parse(int u) {
  if (u == NIL) return;
  post_parse(T[u].l);
  post_parse(T[u].r);
  printf("%d", u);
}

int main() {
  int i, v, l, r, root;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    T[i].p = NIL;
  }

  for (i = 0; i < n; i++) {
    scanf("%d %d %d", &v, &l, &r);
    T[v].l = l;
    T[v].r = r;
    if (l != NIL) T[l].p = v;
    if (r != NIL) T[r].p = v;
  }

  for (i = 0; i < n; i++) if (T[i].p == NIL) root = i;

  printf("Preorder\n");
  pre_parse(root);
  printf("\n");
  printf("Inorder\n");
  in_parse(root);
  printf("\n");
  printf("Postorder\n");
  post_parse(root);
  printf("\n");

  return 0;
}
