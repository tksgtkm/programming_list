#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHILD 5
#define HALF_CHILD ((MAX_CHILD + 1)/2)

typedef int KEY;
typedef int DATA;

typedef struct node NODE;

extern NODE *search(KEY key);

extern NODE *insert(KEY key);

extern int delete(KEY key);

extern void print_tree(NODE *p);
