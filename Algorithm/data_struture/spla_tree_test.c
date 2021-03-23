#include <stdio.h>
#include <stdlib.h>

#include "spla_tree.h"

int main() {
  tree_node_t *searchtree;
  char nextop;
  searchtree = create_tree();
  printf("Made Tree\n");
  printf("In the following, the key n is associated with the object 10n+2\n");
  while((nextop = getchar()) != 'q') {
    if (nextop == 'i') {
      int inskey, *insobj, success;
      insobj = (int *)malloc(sizeof(int));
      scanf(" %d", &inskey);
      *insobj = 10*inskey + 2;
      success = insert(searchtree, inskey, insobj);
      if (success == 0)
        printf("insert successful, key = %d, object value = %d.\n", inskey, *insobj);
      else
        printf("insert failed, success = %d\n", success);
    }
    if (nextop == 'f') {
      int findkey, *findobj;
      scanf("%d", &findkey);
      findobj = find(searchtree, findkey);
      if (findobj == NULL)
        printf("find failed, for key %d\n", findkey);
      else
        printf("find successful, found object %d\n", *findobj);
    }
    if (nextop == 'd') {
      int delkey, *delobj;
      scanf("%d", &delkey);
      delobj = delete(searchtree, delkey);
      if (delobj == NULL)
        printf("delete failed for key %d\n", delkey);
      else
        printf("delete successful, deleted object %d for key %d\n", *delobj, delkey);
    }
    if (nextop == '?') {
      printf("Checking tree.\n");
      check_tree(searchtree, 0, -1000, 1000);
      printf("\n");
      if (searchtree->object != NULL)
        printf("key in root is %d\n", searchtree->key);
      printf("Finished Checking tree.\n");
    }
  }

  remove_tree(searchtree);
  printf("Removed tree.\n");
  // printf("Total number of needs taken %d, total number of nodes returned %d\n", nodes_taken, nodes_returned);
  return 0;
}
