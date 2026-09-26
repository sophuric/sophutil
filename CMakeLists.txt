cmake_minimum_required(VERSION 4.1.6)
project(sophutil C)

include(CTest)

set(CMAKE_C_STANDARD 23)

set(sources
        fnv1_32.c
        fnv1_32.h
        fnv1_64.c
        fnv1_64.h
        hashmap.c
        hashmap.h
        linked_list.c
        linked_list.h
        buffer_builder.c
        buffer_builder.h
        malloc_set.h
)
list(TRANSFORM sources PREPEND src/)

add_library(sophutil SHARED ${sources})

set(tests
        hashmap
        linked_list
        buffer_builder
)
foreach (test ${tests})
    add_executable(test_${test} tests/assert.h tests/${test}.c)
    target_link_libraries(test_${test} sophutil)
    add_test(NAME ${test} COMMAND test_${test})
endforeach ()
