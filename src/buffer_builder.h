#ifndef SOPHUTIL_BUFFER_BUILDER_H
#define SOPHUTIL_BUFFER_BUILDER_H
#include <stddef.h>

#include "malloc_set.h"

struct buffer_builder {
	void *data;
	size_t size;
	size_t allocated;
	struct malloc_set malloc;
};

#define NEW_BUFFER_BUILDER(malloc_set) ((struct buffer_builder) {.data = nullptr, .size = 0, .allocated = 0, .malloc = (malloc_set)})

// Resize the buffer
struct buffer_builder *buffer_builder_resize(struct buffer_builder *buf, size_t n, size_t size, bool shrink_allocation);

// Grow the buffer by an amount
struct buffer_builder *buffer_builder_grow(struct buffer_builder *buf, size_t n, size_t size);

// Append data to the end of the buffer
struct buffer_builder *buffer_builder_append(struct buffer_builder *buf, const void *data, size_t n, size_t size);

// Append a null-terminated string to the end of the buffer
struct buffer_builder *buffer_builder_append_str(struct buffer_builder *buf, const char *string);

// Append a string to the end of the buffer, a string which is terminated with null or at a maximum length
struct buffer_builder *buffer_builder_append_strn(struct buffer_builder *buf, const char *string, size_t len);

// Free the buffer
void buffer_builder_free(struct buffer_builder *buf);

#endif // SOPHUTIL_BUFFER_BUILDER_H
