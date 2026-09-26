#ifndef SOPHUTIL_MALLOC_SET_H
#define SOPHUTIL_MALLOC_SET_H

struct malloc_set {
	void *(*malloc)(size_t size);

	void *(*realloc)(void *ptr, size_t size);

	void (*free)(void *ptr);
};

#define MALLOC_SET(malloc_, realloc_, free_) ((struct malloc_set) {.malloc = malloc_, .realloc = realloc_, .free = free_})
#define MALLOC_SET_DEFAULT MALLOC_SET(malloc, realloc, free)

#endif // SOPHUTIL_MALLOC_SET_H
