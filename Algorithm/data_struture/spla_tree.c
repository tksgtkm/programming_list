#include <stdio.h>
#include <stdlib.h>

#include "spla_tree.h"

tree_node_t *currentblock = NULL;
int size_left;
tree_node_t *free_list = NULL;
int nodes_taken = 0;
int nodes_returned = 0;

tree_node_t *get_node() {
  tree_node_t *tmp;
  nodes_taken += 1;
  if (free_list != NULL) {
    tmp = free_list;
    free_list = free_list -> right;
  } else {
    if (currentblock == NULL || size_left == 0) {
      currentblock = (tree_node_t *)malloc(BLOCKSIZE * sizeof(tree_node_t));
      size_left = BLOCKSIZE;
    }
    tmp = currentblock++;
    size_left -= 1;
  }
  return tmp;
}

void return_node(tree_node_t *node){
  node->right = free_list;
  free_list = node;
  nodes_returned += 1;
}

tree_node_t *create_tree(void) {
  tree_node_t *tmp_node;
  tmp_node = get_node();
  tmp_node->left = NULL;
  tmp_node->right = NULL;
  tmp_node->object = NULL;
  return tmp_node;
}

void left_rotation(tree_node_t *n) {
  tree_node_t *tmp_node;
  key_t tmp_key;
  object_t *tmp_object;
  tmp_node = n->left;
  tmp_key = n->key;
  tmp_object = n->object;
  n->left = n->right;
  n->key = n->right->key;
  n->object = n->right->object;
  n->right = n->left->right;
  n->left->right = n->left->right;
  n->left->left = tmp_node;
  n->left->key = tmp_key;
  n->left->object = tmp_object;
}

void right_rotation(tree_node_t *n) {
  tree_node_t *tmp_node;
  key_t tmp_key;
  object_t *tmp_object;
  tmp_node = n->right;
  tmp_key = n->key;
  tmp_object = n->object;
  n->right = n->left;
  n->key = n->left->key;
  n->object = n->left->object;
  n->right = n->right->left;
  n->right->right = n->right->right;
  n->right->right = tmp_node;
  n->right->key = tmp_key;
  n->right->object = tmp_object;
}

object_t *find(tree_node_t *tree, key_t query_key) {
  int finished = 0;
  if (tree->object == NULL) {
    return NULL;
  } else {
    tree_node_t *current_node, *stack_top, *tmp_stack;
    stack_top = NULL;
    current_node = tree;
    while (!finished) {
      tmp_stack = get_node();
      tmp_stack->right = stack_top;
      tmp_stack->left = current_node;
      stack_top = tmp_stack;
      if (query_key < current_node->key && current_node->left != NULL)
        current_node = current_node->left;
      else if (query_key > current_node->key && current_node->right != NULL)
        current_node = current_node->right;
      else
        finished = 1;
    }
    if (current_node->key != query_key) {
      return NULL;
    } else {
      tree_node_t *upper, *upper2;
      tmp_stack = stack_top;
      stack_top = stack_top->right;
      return_node(tmp_stack);
      while(current_node != tree) {
        upper = stack_top->left;
        tmp_stack = stack_top;
        stack_top = stack_top->right;
        return_node(tmp_stack);
        if (upper == tree) {
          if (upper->left == current_node)
            right_rotation(upper);
          else
            left_rotation(upper);
          current_node = upper;
        } else {
          upper2 = stack_top->left;
          tmp_stack = stack_top;
          stack_top = stack_top->right;
          return_node(tmp_stack);
          if (upper == upper2->left) {
            if (current_node == upper->left)
              right_rotation(upper2);
            else
              left_rotation(upper);
            right_rotation(upper2);
          } else {
            if (current_node == upper->right)
              left_rotation(upper2);
            else
              right_rotation(upper);
            left_rotation(upper2);
          }
          current_node = upper2;
        }
      }
      return current_node->object;
    }
  }
}

int insert(tree_node_t *tree, key_t new_key, object_t *new_object) {
  tree_node_t *tmp_node, *next_node;
  if (tree->object == NULL) {
    tree->object = new_object;
    tree->key = new_key;
    tree->left = NULL;
    tree->right = NULL;
  } else {
    next_node = tree;
    while (next_node != NULL) {
      tmp_node = next_node;
      if (new_key < tmp_node->key)
        next_node = tmp_node->left;
      else if (new_key > tmp_node->key)
        next_node = tmp_node->right;
      else
      return -1;
    }
    while (next_node == NULL) {
      tree_node_t *new_leaf;
      new_leaf = get_node();
      new_leaf->object = new_object;
      new_leaf->key = new_key;
      new_leaf->left = NULL;
      new_leaf->right = NULL;
      if (new_key < tmp_node->key)
        tmp_node->left = new_leaf;
      else
        tmp_node->right = new_leaf;
    }
  }
  return 0;
}

object_t *delete(tree_node_t *tree, key_t delete_key) {
  tree_node_t *tmp_node, *upper_node, *next_node, *del_node;
  object_t *deleted_object;
  if (tree->object == NULL) {
    return NULL;
  } else {
    next_node = tree;
    tmp_node = NULL;
    while (next_node != NULL) {
      upper_node = tmp_node;
      tmp_node = next_node;
      if (delete_key < tmp_node->key)
        next_node = tmp_node->left;
      else if (delete_key > tmp_node->key)
        next_node = tmp_node->right;
      else
    break;
    }
    if (next_node == NULL) {
      return NULL;
    } else {
      deleted_object = tmp_node->object;
      if (tmp_node->left == NULL && tmp_node->right == NULL) {
        if (upper_node != NULL) {
          if (tmp_node == upper_node->left)
            upper_node->left = NULL;
          else
            upper_node->right = NULL;
          return_node(tmp_node);
        } else {
          tmp_node->object = NULL;
        }
      } else if (tmp_node->left == NULL) {
        tmp_node->left = tmp_node->right->left;
        tmp_node->key = tmp_node->right->key;
        tmp_node->object = tmp_node->right->object;
        del_node = tmp_node->right;
        tmp_node->right = tmp_node->right->right;
        return_node(del_node);
      } else if (tmp_node->right == NULL) {
        tmp_node->right = tmp_node->left->right;
        tmp_node->key = tmp_node->left->key;
        tmp_node->object = tmp_node->left->key;
        del_node = tmp_node->left;
        tmp_node->left = tmp_node->left->left;
        return_node(del_node);
      } else {
        upper_node = tmp_node;
        del_node = tmp_node->right;
        while (del_node->left != NULL) {
          upper_node = del_node;
          del_node = del_node->left;
        }
        tmp_node->key = del_node->key;
        tmp_node->object = del_node->object;
        if (del_node == tmp_node->right)
          tmp_node->right = del_node->right;
        else
          upper_node->left = del_node->right;
        return_node(del_node);
      }
      return deleted_object;
    }
  }
}

void remove_tree(tree_node_t *tree) {
  if (tree->left != NULL)
    remove_tree(tree->left);
  if (tree->right != NULL)
    remove_tree(tree->right);
  return_node(tree);
}

void check_tree(tree_node_t *tr, int depth, int lower, int upper) {
  if (tr->object == NULL) {
    printf("Tree Empty\n");
    return;
  }
  if (tr->key < lower || tr->key > upper)
    printf("Wrong Key Order.\n");
  if (*((int *)tr->object) == 10*tr->key + 2)
    printf("%d(%d) ", tr->key, depth);
  else
    printf("Wrong Object.\n");
  if (tr->left != NULL)
    check_tree(tr->left, depth+1, lower, tr->key);
  if (tr->right != NULL)
    check_tree(tr->right, depth+1, tr->key, upper);
}
