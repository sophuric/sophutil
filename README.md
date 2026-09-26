# General purpose C utility library

### Files:

#### Buffer builder:
A buffer capable of dynamically resizing to fit more data
- [Header](src/buffer_builder.h)
- [Source](src/buffer_builder.c)

#### [Fowler-Noll-Vo hash function](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function):
A non-cryptograhic hash function
- [Header (32-bit)](src/fnv1_32.h)
- [Header (64-bit)](src/fnv1_64.h)
- [Source (32-bit)](src/fnv1_32.c)
- [Source (64-bit)](src/fnv1_64.c)

#### Hash map
A data structure that maps keys to value
- [Header](src/hash_map.h)
- [Source](src/hash_map.c)

#### Linked list
Functions to modify a linked list with next/previous pointers, works for any item struct
- [Header](src/linked_list.h)
- [Source](src/linked_list.c)
