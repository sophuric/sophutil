#include "buffer_builder.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct opt_size_t {
	size_t value;
	bool set;
};

static struct opt_size_t safe_multiply(const size_t a, const size_t b) {
	if (a > SIZE_MAX / b || b > SIZE_MAX / a) return (struct opt_size_t) {.set = false};
	return (struct opt_size_t) {.set = true, .value = a * b};
}

static struct opt_size_t safe_add(const size_t a, const size_t b) {
	if (a > SIZE_MAX - b || b > SIZE_MAX - a) return (struct opt_size_t) {.set = false};
	return (struct opt_size_t) {.set = true, .value = a + b};
}

#define IF_SET(opt, opt_type, var, if_not_set) \
	{                                          \
		opt_type temp_opt = (opt);             \
		if (!temp_opt.set) { if_not_set };     \
		var = temp_opt.value;                  \
	}

struct builder_buffer *resize_buffer(struct builder_buffer *old, const size_t n, const size_t size,
                                     const bool shrink_allocation) {
	struct builder_buffer buf = *old;

	if (buf.allocated < 1 || shrink_allocation) buf.allocated = 1;
	IF_SET(safe_multiply(n, size), struct opt_size_t, buf.size, return nullptr;)
	if (buf.size > SIZE_MAX / 2) buf.allocated = SIZE_MAX;
	else
		while (buf.allocated < buf.size) buf.allocated *= 2;

	buf.data = buf.data ? old->malloc.realloc(buf.data, buf.allocated) : old->malloc.malloc(buf.allocated);
	if (!buf.data) return nullptr;

	*old = buf;
	return old;
}

struct builder_buffer *grow_buffer(struct builder_buffer *buf, size_t n, size_t size) {
	size_t add_size, new_size;
	IF_SET(safe_multiply(n, size), struct opt_size_t, add_size, return nullptr;)
	const size_t old_size = buf->size;
	IF_SET(safe_add(add_size, old_size), struct opt_size_t, new_size, return nullptr;)

	buf = resize_buffer(buf, new_size, 1, false);
	if (!buf) return nullptr;

	return buf;
}

struct builder_buffer *append_buffer(struct builder_buffer *buf, const void *data, size_t n, size_t size) {
	size_t add_size, new_size;
	IF_SET(safe_multiply(n, size), struct opt_size_t, add_size, return nullptr;)
	const size_t old_size = buf->size;
	IF_SET(safe_add(add_size, old_size), struct opt_size_t, new_size, return nullptr;)

	buf = resize_buffer(buf, new_size, 1, false);
	if (!buf) return nullptr;

	memcpy(buf->data + old_size, data, add_size);

	return buf;
}

struct builder_buffer *append_string_buffer(struct builder_buffer *buf, const char *string) {
	const size_t string_len = strlen(string);
	size_t add_len = string_len;
	if (buf->size == 0) IF_SET(safe_add(add_len, 1), struct opt_size_t, add_len, return nullptr;)

	size_t new_offset = buf->size;
	if (new_offset > 0) new_offset -= 1;

	buf = grow_buffer(buf, sizeof(*string), add_len);
	if (!buf) return nullptr;

	memcpy(buf->data + new_offset, string, string_len + 1);

	return buf;
}
