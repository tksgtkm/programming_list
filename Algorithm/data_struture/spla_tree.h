#ifndef __spla_tree
#define __spla_tree

typedef int key_t;
typedef int object_t;
typedef struct tr_n_t {
  key_t key;
  struct tr_n_t *left;
  struct tr_n_t *right;
  object_t *object;
} tree_node_t;

#define BLOCKSIZE 256

tree_node_t *get_node();

void return_node(tree_node_t *node);

tree_node_t *create_tree(void);

void left_rotation(tree_node_t *n);

void right_rotation(tree_node_t *n);

object_t *find(tree_node_t *tree, key_t query_key);

int insert(tree_node_t *tree, key_t new_key, object_t *new_object);

object_t *delete(tree_node_t *tree, key_t delete_key);

void remove_tree(tree_node_t *tree);

void check_tree(tree_node_t *tr, int depth, int lower, int upper);

#endif
