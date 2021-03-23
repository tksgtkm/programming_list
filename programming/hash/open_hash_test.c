#include <stdio.h>
#include "member.h"
#include "open_hash.h"

typedef enum {
  TERMINATE, ADD, DELETE, SEARCH, CLEAR, DUMP
} Menu;

Menu select_menu(void) {
  int ch;

  do {
    printf("1.add 2.delete, 3.search 4.clear 5.dump 0.exit : ");
    scanf("%d", &ch);
  } while (ch < TERMINATE || ch > DUMP);
  return (Menu)ch;
}

int main(void) {
  Menu menu;
  OpenedHash hash;

  Initialize(&hash, 13);

  do {
    int result;
    Member x;
    Bucket *temp;

    switch (menu = select_menu()) {
      case ADD:
        x = scan_member("add", MEMBER_NO | MEMBER_NAME);
        result = Add(&hash, &x);
        if (result)
          printf("error: faild to add (%s).\n", (result == 1) ? "already regist" : "memory error");
        break;
      case DELETE:
        x = scan_member("delete", MEMBER_NO);
        result = Remove(&hash, &x);
        if (result == 1)
          printf("error: not exist data in such as number.\n");
        break;
      case SEARCH:
        x = scan_member("search", MEMBER_NO);
        temp = Search(&hash, &x);
        if (temp == NULL) {
          printf("failed to search.\n");
        } else {
          printf("success to search: ");
          print_member(&temp->data);
        }
        break;
      case CLEAR:
        Clear(&hash);
        break;
      case DUMP:
        Dump(&hash);
        break;
    }
  } while (menu != TERMINATE);
  Terminate(&hash);
  return 0;
}
