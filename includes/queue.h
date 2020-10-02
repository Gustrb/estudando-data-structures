#pragma once
    #include "linked_list.h"

    //Queue is just a list where you can only insert at the end and remove at the front
    typedef struct queue {
        //This queue implementations uses an linked list as its main data structure
        ptr_linked_list list;

    } queue_t;

    //Pointer to a queue
    typedef queue_t * ptr_queue;
    
    ptr_queue queue_new();

    bool queue_enqueue(ptr_queue this, int data);
    lookup_result_t queue_dequeue(ptr_queue this);

    int queue_get_len(ptr_queue this);

    void queue_free(ptr_queue this);
