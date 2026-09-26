#include "hashmap.h"
#include "linked_list.h"

#include <string.h>

struct hashmap *hashmap_create(struct malloc_set malloc, size_t bucket_count,
                               bool (*equals_key_function)(struct hashmap *hashmap, void *key1, void *key2),
                               size_t (*hash_key_function)(struct hashmap *hashmap, void *key)) {
	// allocate memory for hashmap + buckets + references
	size_t buckets_off = sizeof(struct hashmap),
	       references_off = bucket_count * sizeof(struct hashmap_bucket) + buckets_off,
	       hashmap_size = bucket_count * sizeof(struct bucket_bucket *) + references_off;

	struct hashmap *hashmap = malloc.malloc(hashmap_size);
	if (!hashmap) return nullptr;
	memset(hashmap, 0, hashmap_size);

	hashmap->malloc = malloc;

	hashmap->equals_key_function = equals_key_function;
	hashmap->hash_key_function = hash_key_function;

	hashmap->bucket_count = bucket_count;
	hashmap->buckets = ((void *) hashmap) + buckets_off;
	hashmap->referenced_bucket_count = 0;
	hashmap->referenced_buckets = ((void *) hashmap) + references_off;

	return hashmap;
}

void *hashmap_get_value(struct hashmap *hashmap, void *key) {
	struct hashmap_entry *entry = hashmap_get_entry(hashmap, key);
	if (entry) return entry->value;
	return nullptr;
}

static struct hashmap_bucket *get_bucket(struct hashmap *hashmap, void *key) {
	return &hashmap->buckets[hashmap->hash_key_function(hashmap, key) % hashmap->bucket_count];
}

struct hashmap_entry *hashmap_get_entry(struct hashmap *hashmap, void *key) {
	for (struct hashmap_entry *entry = get_bucket(hashmap, key)->head; entry; entry = entry->next) {
		if (hashmap->equals_key_function(hashmap, entry->key, key)) return entry;
	}
	return nullptr;
}

#define LL LINKED_LIST_INFO(&bucket->head, nullptr, struct hashmap_entry, next, prev)

struct hashmap_entry *hashmap_get_or_create_entry(struct hashmap *hashmap, void *key) {
	struct hashmap_bucket *bucket = get_bucket(hashmap, key);
	for (struct hashmap_entry *entry = bucket->head; entry; entry = entry->next) {
		if (hashmap->equals_key_function(hashmap, entry->key, key)) return entry;
	}

	struct hashmap_entry *entry = hashmap->malloc.malloc(sizeof(struct hashmap_entry));
	if (!entry) return nullptr;
	memset(entry, 0, sizeof(struct hashmap_entry));

	entry->bucket = bucket;
	entry->key = key;
	linked_list_add_before(LL, entry, nullptr);

	if (!bucket->referenced) {
		bucket->referenced = true;

		// this should always be true if !bucket->referenced
		if (hashmap->referenced_bucket_count < hashmap->bucket_count)
			hashmap->referenced_buckets[hashmap->referenced_bucket_count++] = bucket;
	}

	return entry;
}

void hashmap_remove_entry(struct hashmap *hashmap, struct hashmap_entry *entry) {
	struct hashmap_bucket *bucket = entry->bucket;

	linked_list_remove(LL, entry);

	hashmap->malloc.free(entry);
}

int hashmap_loop_entries(struct hashmap *hashmap, int (*loop_function)(struct hashmap_entry *entry, void *ctx), void *ctx) {
	for (size_t bucket_index = 0; bucket_index < hashmap->referenced_bucket_count; ++bucket_index) {
		struct hashmap_bucket *bucket = hashmap->referenced_buckets[bucket_index];
		for (struct hashmap_entry *next, *entry = bucket->head; entry; entry = next) {
			next = entry->next;
			int res = loop_function(entry, ctx);
			if (res != 0) return res;
		}
	}
	return 0;
}

void hashmap_clear_entries(struct hashmap *hashmap) {
	for (size_t bucket_index = 0; bucket_index < hashmap->referenced_bucket_count; ++bucket_index) {
		struct hashmap_bucket *bucket = hashmap->referenced_buckets[bucket_index];
		bucket->referenced = false;
		for (struct hashmap_entry *next, *entry = bucket->head; entry; entry = next) {
			next = entry->next;
			hashmap->malloc.free(entry);
		}
	}
	hashmap->referenced_bucket_count = 0;
}

void hashmap_free(struct hashmap *hashmap) {
	if (!hashmap) return;
	hashmap_clear_entries(hashmap);
	hashmap->malloc.free(hashmap);
}
