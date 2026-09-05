#ifndef MALLOC_SET_H
#define MALLOC_SET_H
struct malloc_set {
	void *(*malloc)(size_t size);
	void *(*realloc)(void *ptr, size_t size);
	void (*free)(void *ptr);
};

#define MALLOC(malloc_, realloc_, free_) ((struct malloc_set) {.malloc = malloc_, .realloc = realloc_, .free = free_})
#define MALLOC_DEFAULT MALLOC(malloc, realloc, free)
#endif // MALLOC_SET_H
