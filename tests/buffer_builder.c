#include "../src/buffer_builder.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "assert.h"

size_t gen_rand_buf(size_t size_min, size_t size_max, void *out_buf) {
	size_t size = (rand() % (size_max - size_min + 1)) + size_min;
	for (size_t i = 0; i < size; ++i, ++out_buf) {
		*(char *) out_buf = rand();
	}
}

int main(void) {
	srand(time(nullptr));

	struct buffer_builder buf = {0};
	buf.malloc = MALLOC_SET_DEFAULT;

	size_t offset = 0;
	for (size_t cycle = 0; cycle < 16; ++cycle) {
		char rand_data[256];
		size_t rand_data_len = gen_rand_buf(16, sizeof(rand_data), &rand_data);
		ASSERT_P(buffer_builder_append(&buf, rand_data, rand_data_len, 1), &buf);
		ASSERT_I0(memcmp(buf.data + offset, rand_data, rand_data_len));
		offset += rand_data_len;
	}

	buffer_builder_free(&buf);

	ASSERT_P(buffer_builder_append_str(&buf, "Hello"), &buf);
	ASSERT_I0(strcmp(buf.data, "Hello"))

	ASSERT_P(buffer_builder_append_str(&buf, " World"), &buf);
	ASSERT_I0(strcmp(buf.data, "Hello World"))

	ASSERT_P(buffer_builder_append_str(&buf, " to"), &buf);
	ASSERT_I0(strcmp(buf.data, "Hello World to"))

	ASSERT_P(buffer_builder_append_str(&buf, " everyone!"), &buf);
	ASSERT_I0(strcmp(buf.data, "Hello World to everyone!"))

	ASSERT_P(buffer_builder_append_str(&buf, ""), &buf);
	ASSERT_I0(strcmp(buf.data, "Hello World to everyone!"))

	buffer_builder_free(&buf);
	return 0;
fail:
	buffer_builder_free(&buf);
	return 1;
}
