#include "linked_lists.h"

struct linked_list *new_linked_list() {
  struct linked_list *sentinel = (struct linked_list *)malloc(sizeof(struct linked_list));
  sentinel->key = 0;
  sentinel->next = 0;
  return sentinel;
}

void delete_linked_list(struct linked_list *list) {
  while (list) {
    struct linked_list *next = list->next;
    free(list);
    list = next;
  }
}

static struct linked_list *get_previous_link(struct linked_list *list, uint32_t key) {
  while (list->next) {
    if (list->next->key == key)
      return list;
    list = list->next;
  }
  return 0;
}

void add_element(struct linked_list *list, uint32_t key) {
  struct linked_list *link = (struct linked_list*)malloc(sizeof(struct linked_list));
  link->key = key;
  link->next = list->next;
  list->next = link;
}

void delete_element(struct linked_list *list, uint32_t key) {
  struct linked_list *link = get_previous_link(list, key);
  if (!link) return;
  struct linked_list *to_delete = link->next;
  link->next = to_delete->next;
  free(to_delete);
}

bool contains_element(struct linked_list *list, uint32_t key) {
  return get_previous_link(list, key) != 0;
}

uint32_t search_length(struct linked_list *list, uint32_t key) {
  uint32_t probed = 1;
  while (list->next) {
    probed++;
    if (list->next->key == key)
      break;
    list = list->next;
  }
  return probed;
}
