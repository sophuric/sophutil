#ifndef SOPHUTIL_LINKED_LIST_H
#define SOPHUTIL_LINKED_LIST_H
#include <stdbool.h>
#include <stddef.h>

struct linked_list_info {
	void **head;
	void **tail;
	size_t offset_next_pointer, offset_prev_pointer;
};

#define LINKED_LIST_INFO(head, tail, struct_type, next_pointer_field, prev_pointer_field) ((struct linked_list_info) {(void **) head, (void **) tail, offsetof(struct_type, next_pointer_field), offsetof(struct_type, prev_pointer_field)})

// Add a new item after a given item
void linked_list_add_after(struct linked_list_info list, void *new_item, void *after);

// Add a new item before a given item
void linked_list_add_before(struct linked_list_info list, void *new_item, void *before);

// Adds an item to the linked list only if the list is empty
bool linked_list_set_one(struct linked_list_info list, void *only_item);

// Removes an item from the linked list
void linked_list_remove(struct linked_list_info list, void *item_to_remove);

// Iterates forward and find the first item for which the predicate function returns true
// Returns nullptr if no match was found
// It is safe to free the item in loop_function, as long as linked_list_remove is called before
void *linked_list_get_first(struct linked_list_info list, void *start, bool (*predicate)(void *item, void *ctx),
                            void *ctx);

// Iterates backward and find the first item for which the predicate function returns true
// Returns nullptr if no match was found
// It is safe to free the item in loop_function, as long as linked_list_remove is called before
void *linked_list_get_last(struct linked_list_info list, void *end, bool (*predicate)(void *item, void *ctx),
                           void *ctx);

// Iterates forward
// It is safe to free the item in loop_function, as long as linked_list_remove is called before
int linked_list_loop_forward(struct linked_list_info list, void *start, int (*loop_function)(void *item, void *ctx),
                             void *ctx);

// Iterates backward
// It is safe to free the item in loop_function, as long as linked_list_remove is called before
int linked_list_loop_backward(struct linked_list_info list, void *end, int (*loop_function)(void *item, void *ctx),
                              void *ctx);

#endif // SOPHUTIL_LINKED_LIST_H
