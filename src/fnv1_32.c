#include "fnv1_32.h"

#include <string.h>

static const uint32_t offset = 0x811c9dc5, prime = 0x01000193;

uint32_t fnv1_32_hash(const void *data, size_t len) {
	uint32_t hash = offset;
	for (size_t i = 0; i < len; i++) {
		hash *= prime;
		hash ^= ((uint8_t *) data)[i];
	}
	return hash;
}

uint32_t fnv1a_32_hash(const void *data, size_t len) {
	uint32_t hash = offset;
	for (size_t i = 0; i < len; i++) {
		hash ^= ((uint8_t *) data)[i];
		hash *= prime;
	}
	return hash;
}

uint32_t fnv1_32_hash_str(const void *str) {
	return fnv1_32_hash(str, strlen(str));
}

uint32_t fnv1a_32_hash_str(const void *str) {
	return fnv1a_32_hash(str, strlen(str));
}

uint32_t fnv1_32_hash_strn(const void *str, size_t max_len) {
	return fnv1_32_hash(str, strnlen(str, max_len));
}

uint32_t fnv1a_32_hash_strn(const void *str, size_t max_len) {
	return fnv1a_32_hash(str, strnlen(str, max_len));
}
