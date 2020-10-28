#include <cstdio>
#include <cstdlib>
#include <cstring>

/* 双方向連結リスト(redisみたいな感じ)
　　insert x: 連結リストの先頭にキーxを持つ要素を継ぎ足す
　　delete x: キーxを持つ最初の要素を連結リストｋから削除する
   deleteFirst: 連結リストの先頭の要素を削除する
   deleteLast:  連結リストの末尾の要素を削除する
*/

// 双方向連結リストのノード
struct Node {
  int key;
  Node *next, *prev;
};

Node *nil;

// 双方向リストの要素の探索
Node* list_search(int key) {
  Node *cur = nil->next; // 番兵の次の要素から辿る
  while (cur != nil && cur->key != key) {
    cur = cur->next;
  }
  return cur;
}

// 双方向リストの初期化
void init() {
  nil = (Node *)malloc(sizeof(Node));
  nil->next = nil;
  nil->prev = nil;
}

void print_list() {
  Node *cur = nil->next;
  int isf = 0;
  while (1) {
    if (cur == nil) break;
    if (isf++ > 0) printf(" ");
    printf("%d", cur->key);
    cur = cur->next;
  }
  printf("\n");
}

// 双方向リストの要素の削除
void delete_node(Node *t) {
  if (t == nil) return; // tが蛮兵の場合は処理しない
  t->prev->next = t->next;
  t->next->prev = t->prev;
  free(t);
}

void delete_first() {
  delete_node(nil->next);
}

void delete_last() {
  delete_node(nil->prev);
}

void delete_key(int key) {
  // 探索したノードを削除
  delete_node(list_search(key));
}

// 双方向リストへの要素の挿入
/* 与えられたキーを持つノードを生成し、それをリストの先頭に追加しする*/
void insert(int key) {
  Node *x = (Node *)malloc(sizeof(Node));
  x->key = key;
  // 番兵の直後に要素を追加
  x->next = nil->next;
  nil->next->prev = x;
  nil->next = x;
  x->prev = nil;
}

int main() {
  int key, n, i;
  int size = 0;
  char com[20];
  int np = 0, nd = 0;
  scanf("%d", &n);
  init();
  for (i = 0; i < n; i++) {
    scanf("%s%d", com, &key);
    if (com[0] == 'i') {
      insert(key); np++; size++;
    } else if (com[0] == 'd') {
      if (strlen(com) > 6) {
        if (com[6] == 'F') delete_first();
        else if (com[6] == 'L') delete_last();
      } else {
        delete_key(key); nd++;
      }
      size--;
    }
  }

  print_list();

  return 0;
}
