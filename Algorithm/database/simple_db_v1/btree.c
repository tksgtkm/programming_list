#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "btree.h"

#define INTERNAL 1
#define LEAF 2

#define nchilds _u._internal._nchilds
#define child _u._internal._child
#define low _u._internal._low

#define leaf_key _u._leaf._leaf_key
#define your_data _u._leaf._your_data

struct node {
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
};

node * root;


error(char *s) {
  fprintf(stderr, s);
  exit(1);
}

NODE *alloc_node(void) {
  NODE *p;

  if ((p = malloc(sizeof(NODE))) == NULL)
    error("Memory Error\n");
  return p;
}

int keyequal(KEY a, KEY b) {
  return a == b;
}

int keylt(KEY a, KEY b) {
  return a < b;
}

int locate_subtree(NODE *p, KEY key) {
  int i;
  for (i = p->nchilds - 1; i > 0; i--) {
    if (key >= p->low[i])
      return i;
  }
  return 0;
}

NODE *search(KEY key) {
  NODE *p;
  int i;

  if (root == NULL) {
    return NULL;
  } else {
    p = root;
    while (p->nodekind == INTERNAL) {
      i = locate_subtree(p, key);
      p = p->child[i];
    }
    if (key == p->leaf_key)
      return p;
    else
      return NULL;
  }
}

NODE *insert_aux(NODE **pnode, KEY key, NODE **newnode, KEY *lowest) {
  NODE *node;
  *newnode = NULL;
  node = *pnode;
  if (node->nodekind == LEAF) {
    if (keyequal(node->leaf_key, key)) {
      return NULL;
    } else {
      NODE *new;
      new = alloc_node();
      new->nodekind = LEAF;
      new->leaf_key = key;
      if (key < node->leaf_key) {
        *pnode = new;
        *lowest = node->leaf_key;
        *newnode = node;
      } else {
        *lowest = key;
        *newnode = new;
      }
      return new;
    }
  } else {
    int pos;
    NODE *xnode;
    KEY xlow;
    NODE *retv;
    int i, j;
    pos = locate_subtree(node, key);
    retv = insert_aux(&(node->child[pos]), key, &xnode, &xlow);
    if (xnode == NULL)
      return retv;
    if (node->nchilds < MAX_CHILD) {
      for (i = node->nchilds - 1; i > pos; i--) {
        node->child[i+1] = node->child[i];
        node->low[i+1] = node->low[i];
      }
      node->child[pos+1] = xnode;
      node->low[pos+1] = xlow;
      node->nchilds++;
      return retv;
    } else {
      NODE *new;
      new = alloc_node();
      new->nodekind = INTERNAL;
      if (pos < HALF_CHILD - 1) {
        for (i = HALF_CHILD - 1, j = 0; i < MAX_CHILD; i++, j++) {
          new->child[j] = node->child[i];
          new->low[j] = node->low[i];
        }
        for (i = HALF_CHILD - 2; i > pos; i--) {
          node->child[i+1] = node->child[i];
          new->low[i+1] = node->low[i];
        }
        node->child[pos+1] = xnode;
        node->low[pos+1] = xlow;
      } else {
        j = MAX_CHILD - HALF_CHILD;
        for (i = MAX_CHILD-1; i >= HALF_CHILD; i--) {
          if (i == pos) {
            new->child[j] = xnode;
            new->low[j--] = xlow;
          }
          new->child[j] = node->child[i];
          new->low[j--] = node->low[i];
        }
        if (pos < HALF_CHILD) {
          new->child[0] = xnode;
          new->low[0] = xlow;
        }
      }
      node->nchilds = HALF_CHILD;
      new->nchilds = (MAX_CHILD + 1) - HALF_CHILD;
      *newnode = new;
      *lowest = new->low[0];
      return retv;
    }
  }
}

NODE *insert(KEY key) {
  if (root == NULL) {
    root = alloc_node();
    root->nodekind = LEAF;
    root->leaf_key = key;
    return root;
  } else {
    NODE *retv, *new, *newnode;
    KEY lowest;
    retv = insert_aux(&root, key, &newnode, &lowest);
    if (newnode != NULL) {
      new = alloc_node();
      new->nodekind = INTERNAL;
      new->nchilds = 2;
      new->child[0] = root;
      new->child[1] = newnode;
      new->low[1] = lowest;
      root = new;
    }
    return retv;
  }
}

int merge_nodes(NODE *p, int x) {
  NODE *a, *b;
  int an, bn;
  int i;

  a = p->child[x];
  b = p->child[x+1];
  b->low[0] = p->low[x+1];
  an = a->nchilds;
  bn = b->nchilds;
  if (an + bn <= MAX_CHILD) {
    for (i = 0; i < bn; i++) {
      a->child[i+an] = b->child[i];
      a->low[i+an] = b->low[i];
    }
    a->nchilds += bn;
    free(b);
    return 1;
  } else {
    int n, move;
    n = (an + bn) / 2;
    if (an > n) {
      move = an - n;
      for (i = bn - 1; i >= 0; i--) {
        b->child[i+move] = b->child[i];
        b->low[i+move] = b->low[i];
      }
      for (i = 0; i < move; i++) {
        b->child[i] = a->child[i+n];
        b->low[i] = a->low[i+n];
      }
    } else {
      move = n - an;
      for (i = 0; i < move; i++) {
        a->child[i+an] = b->child[i];
        a->low[i+an] = b->low[i];
      }
      for (i = 0; i < bn - move; i++) {
        b->child[i] = b->child[i+move];
        b->low[i] = b->low[i+move];
      }
    }
    a->nchilds = n;
    b->nchilds = an + bn - n;
    p->low[x+1] = b->low[0];
    return 0;
  }
}

#define OK 1
#define REMOVED 2
#define NEED_REORG 3

int delete_aux(NODE *node, KEY key, int *result) {
  *result = OK;
  if (node->nodekind == LEAF) {
    if (keyequal(node->leaf_key, key)) {
      *result = REMOVED;
      free(node);
      return 1;
    } else {
      return 0;
    }
  } else {
    int pos;
    int condition;
    int retv;
    int sub;
    int joined;
    int i;

    pos = locate_subtree(node, key);
    retv = delete_aux(node->child[pos], key, &condition);
    if (condition == OK)
      return retv;

    if (condition == NEED_REORG) {
      sub = (pos == 0) ? 0 : pos - 1;
      joined = merge_nodes(node, sub);
      if (joined)
        pos = sub + 1;
    }

    if (condition == REMOVED || joined) {
      for (i = pos; i < node->nchilds - 1; i++) {
        node->child[i] = node->child[i+1];
        node->low[i] = node->low[i+1];
      }
      if (--node->nchilds < HALF_CHILD)
        *result = NEED_REORG;
    }
    return retv;
  }
}

int delete(KEY key) {
  int retv, result;
  NODE *p;

  if (root == NULL) {
    return 0;
  } else {
    retv = delete_aux(root, key, &result);
    if (result == REMOVED) {
      root = NULL;
    } else if (result == NEED_REORG && root->nchilds == 1) {
      p = root;
      root = root->child[0];
      free(p);
    }
    return retv;
  }
}

void print_tree(NODE *p) {
  int i;

  if (p->nodekind == LEAF) {
    printf("%04x leaf = val = %d\n", p, p->leaf_key);
  } else {
    printf("%04x %02d [%04x] %d[%04x] %d[%04x] %d[%04x] %d[%04x]\n",
           p, p->nchilds, p->child[0],
           p->low[1], p->child[1],
           p->low[2], p->child[2],
           p->low[3], p->child[3],
           p->low[4], p->child[4]);
    for (i  = 0; i < p->nchilds; i++)
      print_tree(p->child[i]);
  }
}
