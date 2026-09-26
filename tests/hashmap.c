#include "../src/hashmap.h"

#include <stdlib.h>
#include <time.h>

#include "assert.h"

bool equals_key(struct hashmap *hm, void *a, void *b) {
    return a == b;
}

size_t hash_key(struct hashmap *hm, void *key) {
    return (uintptr_t) key / 0x100;
}

int main(void) {
    struct hashmap *hm = hashmap_create(MALLOC_SET_DEFAULT, 32, equals_key, hash_key);
    if (!hm) return 1;

    srand(time(NULL));

    int test_keys[1024];

    for (size_t i = 0; i < sizeof(test_keys) / sizeof(*test_keys); ++i) {
        while (true) {
        new_guess:
            int val = rand();
            for (size_t j = 0; j < i; ++j) {
                if (test_keys[j] == val) goto new_guess;
            }
            test_keys[i] = val;
            break;
        }
    }

    for (size_t i = 0; i < sizeof(test_keys) / sizeof(*test_keys); ++i) {
        void *key = (void *) (uintptr_t) test_keys[i], *value = key;
        ASSERT_P(hashmap_get_entry(hm, key), nullptr);

		struct hashmap_entry *entry = hashmap_get_or_create_entry(hm, key);
        ASSERT_NOT_EQUAL_P(entry, nullptr);
        ASSERT_P(hashmap_get_entry(hm, key), entry);
    }

    // TODO write more tests for this

    hashmap_free(hm);
    return 0;
fail:
    hashmap_free(hm);
    return 1;
}
