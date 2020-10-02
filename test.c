#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "includes/linked_list.h"

int square(int n)   { return n * n;      }
bool is_even(int n) { return n % 2 == 0; }

int main(int argc, char **argv) {
    ptr_linked_list list = linked_list_new();

    for(int i = 0; i < 10; i++) {
        linked_list_append(list, i);
    }

    ptr_linked_list squared = linked_list_map(list, &square);
    ptr_linked_list evens = linked_list_filter(list, &is_even);

    linked_list_print(squared);
    linked_list_print(evens);

    linked_list_free(evens);
    linked_list_free(squared);
    linked_list_free(list);

    return EXIT_SUCCESS;
}
