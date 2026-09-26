#include "linked_list.h"

#define NEXT(value) (*(void **) (((void *) value) + list.offset_next_pointer))
#define PREV(value) (*(void **) (((void *) value) + list.offset_prev_pointer))
#define HEAD (*list.head)
#define TAIL (*list.tail)

void linked_list_add_after(struct linked_list_info list, void *new_item, void *existing_item) {
	if (!existing_item) existing_item = TAIL;
	if (!existing_item) {
		linked_list_set_one(list, new_item);
		return;
	}

	void *next_item = NEXT(existing_item);

	PREV(new_item) = existing_item;
	NEXT(new_item) = next_item;

	if (list.tail && TAIL == existing_item)
		TAIL = new_item;
	if (next_item)
		PREV(next_item) = new_item;
	NEXT(existing_item) = new_item;
}

void linked_list_add_before(struct linked_list_info list, void *new_item, void *existing_item) {
	if (!existing_item) existing_item = HEAD;
	if (!existing_item) {
		linked_list_set_one(list, new_item);
		return;
	}

	void *prev_item = PREV(existing_item);

	NEXT(new_item) = existing_item;
	PREV(new_item) = prev_item;

	if (list.head && HEAD == existing_item)
		HEAD = new_item;
	if (prev_item)
		NEXT(prev_item) = new_item;
	PREV(existing_item) = new_item;
}

bool linked_list_set_one(struct linked_list_info list, void *only_item) {
	if (list.head && HEAD) return false;
	if (list.tail && TAIL) return false;
	if (list.head)
		HEAD = only_item;
	if (list.tail)
		TAIL = only_item;
	return true;
}

void linked_list_remove(struct linked_list_info list, void *item_to_remove) {
	void *before = PREV(item_to_remove), *after = NEXT(item_to_remove);

	if (before)
		NEXT(before) = after;
	if (after)
		PREV(after) = before;

	if (list.head && HEAD == item_to_remove)
		HEAD = after;
	if (list.tail && TAIL == item_to_remove)
		TAIL = before;
}

void *linked_list_get_first(struct linked_list_info list, void *start, bool (*predicate)(void *item, void *ctx),
                            void *ctx) {
	if (!start) start = HEAD;
	for (void *next, *entry = start; entry; entry = next) {
		next = NEXT(entry);
		if (predicate(entry, ctx)) return entry;
	}
	return nullptr;
}

void *linked_list_get_last(struct linked_list_info list, void *end, bool (*predicate)(void *item, void *ctx),
                           void *ctx) {
	if (!end) end = TAIL;
	for (void *prev, *entry = end; entry; entry = prev) {
		prev = PREV(entry);
		if (predicate(entry, ctx)) return entry;
	}
	return nullptr;
}

int linked_list_loop_forward(struct linked_list_info list, void *start, int (*loop_function)(void *item, void *ctx),
                             void *ctx) {
	if (!start) start = HEAD;
	for (void *next, *entry = start; entry; entry = next) {
		next = NEXT(entry);
		int res = loop_function(entry, ctx);
		if (res) return res;
	}
	return 0;
}

int linked_list_loop_backward(struct linked_list_info list, void *end, int (*loop_function)(void *item, void *ctx),
                              void *ctx) {
	if (!end) end = TAIL;
	for (void *prev, *entry = end; entry; entry = prev) {
		prev = PREV(entry);
		int res = loop_function(entry, ctx);
		if (res) return res;
	}
	return 0;
}
