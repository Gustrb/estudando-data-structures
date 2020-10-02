#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "includes/linked_list.h"
#include "includes/queue.h"
#include "includes/stack.h"

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

    puts("Teste queues:");

    ptr_queue queue = queue_new();

    for(int i = 0; i < 10; i++) {
        queue_enqueue(queue, i);
    }

    for(int i = 0; i < 10; i++) {
        lookup_result_t result = queue_dequeue(queue);

        if(is_ok(&result)) {
            printf("%d valor: %d\n", i, result.value);
        }
    }

    linked_list_print(queue->list);
    queue_free(queue);

    puts("Teste stacks:");

    ptr_stack stack = stack_new();

    for(int i = 0; i < 10; i++) {
        stack_push(stack, i);
    }

    const int len = stack_get_len(stack);

    for(int i = 0; i < len; i++) {
        lookup_result_t result = stack_pop(stack);

        if(!is_ok(&result))
            continue;

        printf("%d valor: %d\n", i, result.value);
    }

    linked_list_print(stack->list);
    
    stack_free(stack);
    return EXIT_SUCCESS;
}
