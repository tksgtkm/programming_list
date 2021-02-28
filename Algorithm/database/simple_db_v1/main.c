#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "btree.h"

int main() {
  static int data[] = {13, 5, 2, 7, 6, 21, 15};
  int i, x;
  char str[100];
  NODE *root = NULL;

  for (i = 0; i < sizeof(data)/sizeof(data[0]); i++)
    insert(data[i], root);

  printf("+n : nを挿入する\n-n : nを削除する\nn  : nを探索する\n");
  // print_tree(root);
  printf("\n>");

  while(gets(str) != NULL) {
    x = abs(atoi(str));
    printf("%d input.\n", x);
    switch (str[0]) {
      case '+':
        if (insert(x, root) != NULL)
          printf("%d inserted.\n", x);
        else
          printf("%d not inserted.\n", x);
        break;
      case '-':
        if (delete(x, root))
          printf("%d deleted.\n", x);
        else
          printf("%d not deleted.\n", x);
        break;
      default:
        if (search(x, root) != NULL)
          printf("%d found.\n", x);
        else
          printf("%d not found.\n", x);
        break;
    }
    // print_tree(root);
    printf("\n>");
  }
}
