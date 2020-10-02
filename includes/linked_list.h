#pragma once

    //The atomic part of an linked list
    typedef struct node {
        //data is the value which all the nodes must have
        int data;

        //next is the subsequent node, it has value NULL if the given node is the last of the list
        struct node *next;

    } node_t;

    //A pointer to a node type
    typedef node_t * ptr_node_t;

    //Definition of the linked list
    typedef struct linked_list {
        //head is the first element of the list, so if a head is NULL than the list is emptySD
        ptr_node_t head;

        //len is the list current lenght
        int len;

    } linked_list_t;

    //Status of a lookup operation, so it can know how it went
    typedef enum lookup_status {
        INDEX_OUT_OF_BOUNDS,
        INVALID_LIST,
        EMPTY_LIST,
        OK
    } lookup_status_t;

    //Result of a operation which returns a result
    typedef struct lookup_result {
        //status is the lookup operation current status, so if the operation went corectly than the status should be OK
        lookup_status_t status;

        //value is the operation result, its value should not be considered if the status is not OK
        int value;
        
    } lookup_result_t;

    typedef int (*callback)(int);
    typedef bool (*filter_callback)(int);

    //A pointer to a linked list
    typedef linked_list_t * ptr_linked_list;

    //Functions to manage linked lists:

    ptr_linked_list linked_list_new();
    ptr_linked_list linked_list_reverse(ptr_linked_list this);
    ptr_linked_list linked_list_map(ptr_linked_list this, callback fn);
    ptr_linked_list linked_list_filter(ptr_linked_list this, filter_callback fn);

    bool is_ok(lookup_result_t *result);
    bool linked_list_is_empty(ptr_linked_list this);
    
    bool linked_list_append(ptr_linked_list this, int data);
    bool linked_list_insert_at_head(ptr_linked_list this, int data);
    bool linked_list_insert_at(ptr_linked_list this, int data, int index);

    lookup_result_t linked_list_remove_at(ptr_linked_list this, int index);
    lookup_result_t linked_list_remove_last(ptr_linked_list this);
    lookup_result_t linked_list_get(ptr_linked_list this, int index);

    void linked_list_print(ptr_linked_list this);
    void linked_list_free(ptr_linked_list this);
