#ifndef SOPHUTIL_FNV1_64_H
#define SOPHUTIL_FNV1_64_H
#include <stdint.h>
#include <stddef.h>

uint64_t fnv1_64_hash(const void *data, size_t len);
uint64_t fnv1a_64_hash(const void *data, size_t len);
uint64_t fnv1_64_hash_str(const void *str);
uint64_t fnv1a_64_hash_str(const void *str);
uint64_t fnv1_64_hash_strn(const void *str, size_t max_len);
uint64_t fnv1a_64_hash_strn(const void *str, size_t max_len);

#endif // SOPHUTIL_FNV1_64_H
