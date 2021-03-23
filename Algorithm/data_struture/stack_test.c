#include <stdio.h>
#include "stack.h"

int main(void) {
  IntStack s;

  if (Initialize(&s, 64) == -1) {
    puts("failed to generate stack.");
    return 1;
  }

  while(1) {
    int menu, x;

    printf("volume of datas: %d / %d\n", Size(&s), Capacity(&s));
    printf("(1)push (2)pop (3)peek (4)view (0)exit: ");
    scanf("%d", &menu);

    if (menu == 0) break;

    switch (menu) {
      case 1:
        printf("data: ");
        scanf("%d", &x);
        if (Push(&s, x) == -1)
          puts("error: failed to push.");
        break;
      case 2:
        if (Pop(&s, &x) == -1)
          puts("error: failed to pop.");
        else
          printf("poped data is %d.\n", x);
        break;
      case 3:
        if (Peek(&s, &x) == -1)
          puts("error: failed to peek.");
        else
          printf("peeked data is %d.\n", x);
        break;
      case 4:
        Print(&s);
        break;
    }
  }
  Terminate(&s);
  return 0;
}
