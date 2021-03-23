#include <stdio.h>

#include "segment_tree.h"

int main(void) {
  tree_node_t *seg_tree, *tmp, *list;
  char nextop;
  struct intv intervals[100];
  int keys[200];
  int prev_key;
  int i = 0, j;
  int *tmpob;
  printf("Please enter the intervals\n");
  while ((nextop = getchar()) != 'q') {
    if(nextop == 'i') {
      int lower, upper;
      scanf("%d %d", &lower, &upper);
      intervals[i].low = lower;
      intervals[i].up = upper;
      keys[2*i] = lower;
      keys[2*i+1] = upper;
      i+=1;
    }
  }
  printf("stored %d intervals\n", i);
  printf("the %d intervals, are\n", i);
  for (j = 0; j < i; j++)
    printf("[%d,%d[ ", intervals[j].low, intervals[j].up);
  printf("\n");
  qsort(keys, 2*i, sizeof(int), compint);
  printf(" the keys, sorted in increasing order, are \n");
  for (j = 0; j<2*i; j++)
    printf("%d, ", keys[j]);
  printf("\n");
  list = get_node();
  list->right = NULL;
  prev_key = list->key = keys[2*i-1];
  tmpob = (int *)malloc(sizeof(int));
  *tmpob = 42;
  list->left = (tree_node_t *)tmpob;
  for (j = 2*i-2; j >= 0; j--) {
    if (keys[j] != prev_key) {
      tmp = get_node();
      prev_key = tmp->key = keys[j];
      tmp->right = list;
      tmpob = (int *)malloc(sizeof(int));
      *tmpob = 42;
      tmp->left = (tree_node_t *)tmpob;
      list = tmp;
    }
  }
  tmp = get_node();
  tmp->key = -1000;
  tmp->right = list;
  tmpob = (int *)malloc(sizeof(int));
  *tmpob = 42;
  tmp->left = (tree_node_t *)tmpob;
  list = tmp;
  printf("Built sorted list from keys\n");
  tmp = list;
  while (tmp != NULL) {
    printf("%d ", tmp->key);
    tmp = tmp->right;
  }
  printf("\n");
  seg_tree = make_tree(list);
  printf("Made Tree\n");
  empty_tree(seg_tree);
  check_tree(seg_tree, 0, -2000, 1000);
  printf("Tree tested.\n");
  for (j = i-1; j >= 0; j--) {
    struct intv *tmp_ob;
    tmp_ob = (struct intv *)malloc(sizeof(struct intv));
    tmp_ob->low = intervals[j].low;
    tmp_ob->up = intervals[j].up;
    insert_interval(seg_tree, intervals[j].low, intervals[j].up, tmp_ob);
  }
  printf("inserted the intervals into the tree. Now entering query phase.\n");
  while ((nextop = getchar()) != 'q') {
    list_node_t *answer_list;
    if (nextop == 'f') {
      int findkey;
      scanf(" %d", &findkey);
      answer_list = find_intervals(seg_tree, findkey);
      if (answer_list == NULL)
        printf("no intervals found for key %d\n", findkey);
      else
        printf(" the following intervals contain key %d\n", findkey);
      while (answer_list != NULL) {
        printf("[%d, %d[ ", answer_list->object->low, answer_list->object->up);
        answer_list = answer_list->next;
      }
      printf("end.\n");
    }
  }
  return 0;
}
