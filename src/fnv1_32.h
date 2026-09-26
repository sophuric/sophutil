#ifndef SOPHUTIL_FNV1_32_H
#define SOPHUTIL_FNV1_32_H
#include <stdint.h>
#include <stddef.h>

uint32_t fnv1_32_hash(const void *data, size_t len);
uint32_t fnv1a_32_hash(const void *data, size_t len);
uint32_t fnv1_32_hash_str(const void *str);
uint32_t fnv1a_32_hash_str(const void *str);
uint32_t fnv1_32_hash_strn(const void *str, size_t max_len);
uint32_t fnv1a_32_hash_strn(const void *str, size_t max_len);

#endif // SOPHUTIL_FNV1_32_H
