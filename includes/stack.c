#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "linked_list.h"
#include "stack.h"

/**
 * stack_new instantiates an heap allocated stack
 * 
 * @author Gustavo Reis Bauer
 * 
 * @return an heap allocated stack(needs to be freed later)
 * */
ptr_stack stack_new() {
    ptr_stack stack = ALLOC(1, stack_t);

    if(!stack) {
        perror("Could not allocate stack object");
        return NULL;
    }

    stack->list = linked_list_new();

    return stack;
}

/**
 * stack_push inserts an element to the end of the stack
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the stack which will have a new element added to
 * @param data is the value of the new element
 * 
 * @return if the element was properly added
 * */
bool stack_push(ptr_stack this, int data) {
    return linked_list_append(this->list, data);
}

/**
 * stack_pop removes the last element of the stack
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the stack
 * 
 * @return an lookup result, if status is not OK then its data should not be considered
 * */
lookup_result_t stack_pop(ptr_stack this) {
    return linked_list_remove_last(this->list);
}

/**
 * stack_is_empty checks if a stack is empty
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the istance of the stack
 * 
 * @return if the stack is empty
 * */
inline bool stack_is_empty(ptr_stack this) {
    return linked_list_is_empty(this->list);
}

/**
 * stack_peek returns the top element of the stack
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the stack
 * 
 * @return the result of the peek, if the result status is not OK then its data should not be considered
 * */
lookup_result_t stack_peek(ptr_stack this) {
    return linked_list_get(this->list, this->list->len - 1);
}

/**
 * stack_get_len returns the size of the stack
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the stack
 * 
 * @return the stack size
 * */
int stack_get_len(ptr_stack this) {
    return this->list->len;
}

/**
 * stack_free deallocates an stack from the memory(it cannot be used after)
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the stack
 * */
void stack_free(ptr_stack this) {
    if(!this) {
        perror("Cannot free a non allocated stack");
        return;
    }

    linked_list_free(this->list);

    free(this);
}
