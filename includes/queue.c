#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "linked_list.h"
#include "queue.h"

/**
 * queue_new allocates a new queue object
 * 
 * @author Gustavo Reis Bauer
 * 
 * @return a heap allocated queue(needs to freed later)
 * */
ptr_queue queue_new() {
    ptr_queue queue = ALLOC(1, queue_t);

    if(!queue) {
        perror("Couldnt allocate queue object");
        return NULL;
    }

    queue->list = linked_list_new();

    return queue;
}

/**
 * queue_enqueue inserts an element at the end of the queue
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the queue which will have the element inserted
 * @param data is the value of the node which will be added
 * 
 * @return if the node was successfully added
 * */
bool queue_enqueue(ptr_queue this, int data) {
    return linked_list_append(this->list, data);
}

/**
 * queue_dequeue removes the head of the list(dequeues it)
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the queue where the head will be dequeued
 * 
 * @return an lookup result, the data value should be considered only if the staus is OK
 * */
lookup_result_t queue_dequeue(ptr_queue this) {
    return linked_list_remove_at(this->list, 0);
}

/**
 * queue_free deallocates an queue object
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the queue which will be deallocated
 * */
void queue_free(ptr_queue this) {
    if(!this) {
        perror("Cannot free null pointer");
        return;
    }

    linked_list_free(this->list);

    free(this);
}

/**
 * queue_get_len returns the number of elements contained in the queue
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the queue being checked
 * 
 * @return is the length of the list
 * */
int queue_get_len(ptr_queue this) { 
    return this->list->len;
}
