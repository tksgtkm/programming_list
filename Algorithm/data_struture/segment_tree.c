#include <stdio.h>
#include <stdlib.h>

#include "segment_tree.h"

tree_node_t *currentblock = NULL;
int size_left;
tree_node_t *free_list = NULL;

tree_node_t *get_node() {
  tree_node_t *tmp;
  if (free_list != NULL) {
    tmp = free_list;
    free_list = free_list->left;
  } else {
    if (currentblock == NULL || size_left == 0) {
      currentblock = (tree_node_t *)malloc(BLOCKSIZE * sizeof(tree_node_t));
    }
    tmp = currentblock++;
    size_left -= 1;
  }
  return tmp;
}

void return_node(tree_node_t *node) {
  node->left = free_list;
  free_list = node;
}

list_node_t *get_list_node() {
  return (list_node_t *)get_node();
}

tree_node_t *make_tree(tree_node_t *list) {
  typedef struct {
    tree_node_t *node1;
    tree_node_t *node2;
    int number;
  } st_item;
  st_item current, left, right;
  st_item stack[100];
  int st_p = 0;
  tree_node_t *tmp, *root;
  int length = 0;
  for (tmp = list; tmp != NULL; tmp = tmp->right)
    length += 1;

  root = get_node();
  current.node1 = root;
  current.node2 = NULL;
  current.number = length;
  stack[st_p++] = current;
  while (st_p > 0) {
    current = stack[--st_p];
    if (current.number > 1) {
      left.node1 = get_node();
      left.node2 = current.node2;
      left.number = current.number/2;
      right.node1 = get_node();
      right.node2 = current.node1;
      right.number = current.number - left.number;
      (current.node1)->left = left.node1;
      (current.node1)->right = right.node1;
      stack[st_p++] = right;
      stack[st_p++] = left;
    } else {
      (current.node1)->left = list->left;
      (current.node1)->key = list->key;
      (current.node1)->right = NULL;
      if (current.node2 != NULL)
        (current.node2)->key = list->key;
      tmp = list;
      list = list->right;
      return_node(tmp);
    }
  }
  return root;
}

void empty_tree(tree_node_t *stree) {
  stree->interval_list = NULL;
  if (stree->right != NULL) {
    empty_tree(stree->left);
    empty_tree(stree->right);
  }
}

void check_tree(tree_node_t *tr, int depth, int lower, int upper) {
  if (tr->left == NULL) {
    printf("Tree Empty\n");
    return;
  }
  if (tr->key < lower || tr->key >= upper)
    printf("Wrong Key Order.\n");
  if (tr->right == NULL) {
    if (*((int *)tr->left) == 42)
      printf("%d(%d) ", tr->key, depth);
    else
      printf("Wrong Object.\n");
  } else {
    check_tree(tr->left, depth+1, lower, tr->key);
    check_tree(tr->right, depth+1, tr->key, upper);
  }
}

list_node_t *find_intervals(tree_node_t *tree, key_t query_key) {
  tree_node_t *current_tree_node;
  list_node_t *current_list, *result_list, *new_result;
  if (tree->left == NULL) {
    return NULL;
  } else {
    current_tree_node = tree;
    result_list = NULL;
    while (current_tree_node->right != NULL) {
      if (query_key < current_tree_node->key)
        current_tree_node = current_tree_node->left;
      else
        current_tree_node = current_tree_node->right;
      current_list = current_tree_node->interval_list;
      while (current_list != NULL) {
        new_result = get_list_node();
        new_result->next = result_list;
        new_result->key_a = current_list->key_a;
        new_result->key_b = current_list->key_b;
        new_result->object = current_list->object;
        result_list = new_result;
        current_list = current_list->next;
      }
    }
    return result_list;
  }
}

void attach_intv_node(tree_node_t *tree_node, key_t a, key_t b, object_t *object) {
  list_node_t *new_node;
  new_node = get_list_node();
  new_node->next = tree_node->interval_list;
  new_node->key_a = a;
  new_node->key_b = b;
  new_node->object = object;
  tree_node->interval_list = new_node;
}

void insert_interval(tree_node_t *tree, key_t a, key_t b, object_t *object) {
  tree_node_t *current_node, *right_path, *left_path;
  list_node_t *current_list, *new_node;
  if (tree->left == NULL) {
    exit(-1);
  } else {
    current_node = tree;
    right_path = left_path = NULL;
    while (current_node->right != NULL) {
      if (b < current_node->key) {
        current_node = current_node->left;
      } else if (current_node->key < a) {
        current_node = current_node->right;
      } else if (a < current_node->key && current_node->key < b) {
        right_path = current_node->right;
        left_path = current_node->left;
        break;
      } else if (a == current_node->key) {
        right_path = current_node->right;
        break;
      } else {
        left_path = current_node->left;
        break;
      }
    }
    if (left_path != NULL) {
      while (left_path->right != NULL) {
        if (a < left_path->key) {
          attach_intv_node(left_path->right, a, b, object);
          left_path = left_path->left;
        } else if (a == left_path->key) {
          attach_intv_node(left_path->right, a, b, object);
          break;
        } else {
          left_path = left_path->right;
        }
      }
      if (left_path->right == NULL && left_path->key == a)
        attach_intv_node(left_path, a, b, object);
    }
    if (right_path != NULL) {
      while (right_path->right != NULL) {
        if (right_path->key < b) {
          attach_intv_node(right_path->left, a, b, object);
          right_path = right_path->right;
        } else if (right_path->key == b) {
          attach_intv_node(right_path->left, a, b, object);
          break;
        } else {
          right_path = right_path->left;
        }
      }
    }
  }
}

int compint(int *a, int *b) {
  return *a>*b;
}
