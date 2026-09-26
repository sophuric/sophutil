#ifndef SOPHUTIL_HASHMAP_H
#define SOPHUTIL_HASHMAP_H
#include <stdbool.h>
#include <stddef.h>

#include "malloc_set.h"

struct hashmap_entry {
	struct hashmap_entry *prev, *next;
	struct hashmap_bucket *bucket;

	// If key is changed to a different pointer, the result of hash_key_function(key) MUST remain the same
	void *key, *value; // RW
};

struct hashmap_bucket {
	bool referenced;
	struct hashmap_entry *head;
};

struct hashmap {
	struct malloc_set malloc; // RW

	bool (*equals_key_function)(struct hashmap *hashmap, void *key1, void *key2);
	size_t (*hash_key_function)(struct hashmap *hashmap, void *key);

	void *ctx;

	size_t bucket_count;
	struct hashmap_bucket *buckets;

	size_t referenced_bucket_count;
	struct hashmap_bucket **referenced_buckets;
};

struct hashmap *hashmap_create(struct malloc_set malloc, size_t bucket_count,
                               bool (*equals_key_function)(struct hashmap *hashmap, void *key1, void *key2),
                               size_t (*hash_key_function)(struct hashmap *hashmap, void *key));

// Same as hashmap_get_entry()->value
void *hashmap_get_value(struct hashmap *hashmap, void *key);

// Return the entry struct, use this to determine whether an entry exists in the map, because the value is allowed to be zero/nullptr
struct hashmap_entry *hashmap_get_entry(struct hashmap *hashmap, void *key);

// Returns nullptr if memory allocation fails
struct hashmap_entry *hashmap_get_or_create_entry(struct hashmap *hashmap, void *key);

void hashmap_remove_entry(struct hashmap *hashmap, struct hashmap_entry *entry);

void hashmap_clear_entries(struct hashmap *hashmap);

// Calls hashmap_clear_entries before
void hashmap_free(struct hashmap *hashmap);

// Breaks if loop_function returns non-zero value, returns last return value of loop_function
int hashmap_loop_entries(struct hashmap *hashmap, int (*loop_function)(struct hashmap_entry *entry, void *ctx),
                         void *ctx);
#endif // SOPHUTIL_HASHMAP_H
