#ifndef ARCH_BUFFER_BUILDER_H
#define ARCH_BUFFER_BUILDER_H
#include <stddef.h>

#include "malloc_set.h"

struct builder_buffer {
	void *data;
	size_t size;
	size_t allocated;
	struct malloc_set malloc;
};

struct builder_buffer *resize_buffer(struct builder_buffer *old, size_t n, size_t size, bool shrink_allocation);

struct builder_buffer *grow_buffer(struct builder_buffer *buf, size_t n, size_t size);

struct builder_buffer *append_buffer(struct builder_buffer *buf, const void *data, size_t n, size_t size);

struct builder_buffer *append_string_buffer(struct builder_buffer *buf, const char *string);

#endif // ARCH_BUFFER_BUILDER_H
