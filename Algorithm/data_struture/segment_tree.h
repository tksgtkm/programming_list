#ifndef __SegmentTree_H
#define __SegmentTree_H

#define BLOCKSIZE 256

struct intv {int low; int up;};

typedef struct intv object_t;
typedef int key_t;
typedef struct ls_n_t {
  key_t key_a, key_b;
  struct ls_n_t *next;
  object_t *object;
} list_node_t;
typedef struct tr_n_t {
  key_t key;
  struct tr_n_t *left;
  struct tr_n_t *right;
  list_node_t *interval_list;
} tree_node_t;

tree_node_t *get_node();

void return_node(tree_node_t *node);

list_node_t *get_list_node();

tree_node_t *make_tree(tree_node_t *list);

void empty_tree(tree_node_t *stree);

void check_tree(tree_node_t *tr, int depth, int lower, int upper);

list_node_t *find_intervals(tree_node_t *tree, key_t query_key);

void attach_intv_node(tree_node_t *tree_node, key_t a, key_t b, object_t *object);

void insert_interval(tree_node_t *tree, key_t a, key_t b, object_t *object);

int compint(int *a, int *b);

#endif
