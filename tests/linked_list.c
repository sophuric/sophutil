#include "../src/linked_list.h"

#include <stdlib.h>

#include "assert.h"

struct entry {
	struct entry *next, *prev;
	size_t index;
};

struct context {
	const struct linked_list_info info;
	size_t looped_amount;
};

int loop_func(void *item, void *ctx);

int main(void) {
	struct entry *head = nullptr, *tail = nullptr;
	const struct linked_list_info info = LINKED_LIST_INFO(&head, &tail, struct entry, next, prev);

	const size_t entries_len = 64;
	struct entry *entries = calloc(entries_len, sizeof(struct entry));
	if (!entries) return 1;

	for (size_t i = 0; i < entries_len; ++i) {
		entries[i].index = i;
		linked_list_add_after(info, &entries[i], nullptr);
	}

	size_t i = 0;
	for (; i < entries_len; ++i) {
		void *expected_next = i == entries_len - 1 ? nullptr : &entries[i + 1];
		void *expected_prev = i == 0 ? nullptr : &entries[i - 1];

		ASSERT_P(entries[i].next, expected_next);
		ASSERT_P(entries[i].prev, expected_prev);
		ASSERT_2(size_t, "zu", entries[i].index, i);
	}

	ASSERT_P(entries[4].next, &entries[5]);
	ASSERT_P(entries[5].next, &entries[6]);
	ASSERT_P(entries[5].prev, &entries[4]);
	ASSERT_P(entries[6].prev, &entries[5]);
	ASSERT_P(head, &entries[0]);
	ASSERT_P(tail, &entries[entries_len - 1]);

	linked_list_remove(info, &entries[5]);
	ASSERT_P(entries[4].next, &entries[6]);
	ASSERT_P(entries[6].prev, &entries[4]);

	ASSERT_P(head, &entries[0]);
	ASSERT_P(entries[0].prev, nullptr);
	linked_list_remove(info, &entries[0]);
	ASSERT_P(head, &entries[1]);
	ASSERT_P(entries[1].prev, nullptr);

	ASSERT_P(tail, &entries[entries_len - 1]);
	ASSERT_P(entries[entries_len - 1].next, nullptr);
	linked_list_remove(info, &entries[entries_len - 1]);
	ASSERT_P(tail, &entries[entries_len - 2]);
	ASSERT_P(entries[entries_len - 2].next, nullptr);

	struct context ctx = {info, 0};

	linked_list_loop_forward(info, nullptr, loop_func, &ctx);

	ASSERT_2(size_t, "zu", ctx.looped_amount, entries_len - 3);
	ASSERT_P(head, nullptr);
	ASSERT_P(tail, nullptr);

	free(entries);
	return 0;
fail:
	free(entries);
	return 1;
}

int loop_func(void *item, void *ctx_) {
	struct context *ctx = ctx_;
	linked_list_remove(ctx->info, item);
	++ctx->looped_amount;
	return 0;
}
