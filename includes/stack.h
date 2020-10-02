#pragma once
    #include "linked_list.h"
    
    //Stack representation, made on top of a linked list
    typedef struct stack_t {
        ptr_linked_list list;
    } stack_t;

    typedef stack_t * ptr_stack;

    ptr_stack stack_new();

    bool stack_push(ptr_stack this, int data);
    bool stack_is_empty(ptr_stack this);

    lookup_result_t stack_pop(ptr_stack this);
    lookup_result_t stack_peek(ptr_stack this);

    int stack_get_len(ptr_stack this);

    void stack_free(ptr_stack this);