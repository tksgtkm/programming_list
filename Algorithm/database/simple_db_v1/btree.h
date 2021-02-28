#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHILD 5
#define HALF_CHILD ((MAX_CHILD + 1)/2)

typedef int KEY;
typedef int DATA;

typedef struct node {
  int nodekind;
  union {
    struct {
      int _nchilds;
      struct node *_child[MAX_CHILD];
      KEY _low[MAX_CHILD];
    } _internal;
    struct {
      KEY _leaf_key;
      DATA _your_data;
    } _leaf;
  } _u;
} NODE;

extern NODE *search(KEY key, NODE *root);

extern NODE *insert(KEY key, NODE *root);

extern int delete(KEY key, NODE *root);

extern void print_tree(NODE *p);
