#include "fnv1_64.h"

#include <string.h>

static const uint64_t offset = 0xcbf29ce484222325, prime = 0x00000100000001b3;

uint64_t fnv1_64_hash(const void *data, size_t len) {
	uint64_t hash = offset;
	for (size_t i = 0; i < len; i++) {
		hash *= prime;
		hash ^= ((uint8_t *) data)[i];
	}
	return hash;
}

uint64_t fnv1a_64_hash(const void *data, size_t len) {
	uint64_t hash = offset;
	for (size_t i = 0; i < len; i++) {
		hash ^= ((uint8_t *) data)[i];
		hash *= prime;
	}
	return hash;
}

uint64_t fnv1_64_hash_str(const void *str) {
	return fnv1_64_hash(str, strlen(str));
}

uint64_t fnv1a_64_hash_str(const void *str) {
	return fnv1a_64_hash(str, strlen(str));
}

uint64_t fnv1_64_hash_strn(const void *str, size_t max_len) {
	return fnv1_64_hash(str, strnlen(str, max_len));
}

uint64_t fnv1a_64_hash_strn(const void *str, size_t max_len) {
	return fnv1a_64_hash(str, strnlen(str, max_len));
}
