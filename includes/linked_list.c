#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "linked_list.h"

#define HEAD_INDEX 0

/**
 * linked_list_is_empty verifies if an linked_list is empty by checking its head
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the linked list to be instanciated
 * 
 * @return if the list is empty
 * */
static bool linked_list_is_empty(ptr_linked_list this) { return !this->head; }

/**
 * linked_list_is_outside verifies if a given index is out of list bounds
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list being looked at
 * @param index is the index which is being verified
 * 
 * @return if the index is out of this borders
 * */
static bool linked_list_is_outside(ptr_linked_list this, size_t index) { return index > this->len || index < 0; }

/**
 * linked_list_is_ok verifies if the given lookup_result have an status of ok, so its value should be considered
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param result is the addres of the result which is being looked at
 * 
 * @return if the result is ok
 * */
bool linked_list_is_ok(lookup_result_t *result) { return result->status == OK; }

/**
 * linked_list_new returns a heap allocated linked list
 * 
 * @author Gustavo Reis Bauer
 * 
 * @return an instance of a linked_list(needs to be freed)\n
 *         NULL if the object could not be allocated
 * */
ptr_linked_list linked_list_new() {
    ptr_linked_list ll = ALLOC(1, linked_list_t);

    if(!ll) {
        perror("Could not allocate linked list");
        return NULL;
    }

    ll->head = NULL;
    ll->len = 0;

    return ll;
}

/**
 * linked_list_append inserts an element to the end of the list
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the list which an element should be appended to
 * @param data is the element itself
 * 
 * @return if the new node was correctly inserted
 * */
bool linked_list_append(ptr_linked_list this, int data) {
    if(!this) {
        perror("Cannot insert an element to a non allocated list");
        return false;
    }

    const ptr_node_t new_node = ALLOC(1, node_t);

    if(!new_node) {
        perror("Could not allocate enough memory to the node");
        return false;
    }

    new_node->data = data;
    new_node->next = NULL;

    if(linked_list_is_empty(this)) {
        this->head = new_node;
        this->len++;

        return true;
    }

    ptr_node_t trav = this->head;

    for(int i = 0; i < this->len - 1; i++)
        trav = trav->next;

    trav->next = new_node;
    this->len++;
    
    return true;
}

/**
 * linked_list_print iterates over a linked list and prints its elements to the standard output
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the allocated list which will be printed
 * */
void linked_list_print(ptr_linked_list this) {
    if(!this) {
        perror("Cannot iterate over a non allocated list");
        return;
    }

    if(linked_list_is_empty(this)) {
        printf("[ ]\n");
        return;
    }

    ptr_node_t trav = this->head;

    printf("[ ");

    for(int i = 0; i < this->len - 1; i++) {
        printf("%d, ", trav->data);

        trav = trav->next;
    }

    printf("%d ]\n", trav->data);
}

/**
 * linked_list_remove_at remove um elemento de uma linked list de acordo com o seu indice
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list which will have its element deleted
 * @param index is the index which will be removed
 * 
 * @return the removed value, if the list is invalid, the value of the status enum will say which error happened, the value should be considered only if the status value is ok
 * */
lookup_result_t linked_list_remove_at(ptr_linked_list this, size_t index) {
    lookup_result_t result;

    if(!this) {
        perror("Cannot remove element of non allocated list");
        result.status = INVALID_LIST;

        return result;
    }

    if(linked_list_is_outside(this, index)) {
        perror("Cannot remove element out of list bounds");
        result.status = INDEX_OUT_OF_BOUNDS;

        return result;
    }

    if(index == HEAD_INDEX) {
        const ptr_node_t aux = this->head;
        const int data = this->head->data;

        this->head = this->head->next;
        free(aux);

        this->len--;

        result.status = OK;
        result.value = data;

        return result;
    }

    ptr_node_t trav = this->head;

    for(int i = 0; i < index - 1; i++)
        trav = trav->next;

    const ptr_node_t aux = trav->next;
    const int data = trav->next->data;

    trav->next = trav->next->next;

    free(aux);

    this->len--;

    result.status = OK;
    result.value = data;

    return result;
}

/**
 * linked_list_get retrieves an element based on its index
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the instance of the list which is being searched
 * @param index is the index of the element which will be retrieved
 * 
 * @return the value stored in the list index, if the status of the result is not OK then its value should not be considered
 * */
lookup_result_t linked_list_get(ptr_linked_list this, size_t index) {
    lookup_result_t result;

    if(!this) {
        perror("Cannot search through a non allocated list");

        result.status = INVALID_LIST;

        return result;
    }

    if(linked_list_is_empty(this)) {
        perror("Cannot search through an empty list");

        result.status = EMPTY_LIST;

        return result;
    }

    if(linked_list_is_outside(this, index)) {
        perror("Cannot get element out of list bounds");
         
        result.status = INDEX_OUT_OF_BOUNDS;

        return result;
    }

    ptr_node_t trav = this->head;

    for(int i = 0; i < index; i++)
        trav = trav->next;
    
    result.status = OK;
    result.value = trav->data;

    return result;
}

/**
 * linked_list_free deallocates all lists nodes and itself, the list cannot be used after
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list to be deallocated
 * */
void linked_list_free(ptr_linked_list this) {
    ptr_node_t trav = this->head;

    for(int i = 0; i < this->len; i++) {
        const ptr_node_t aux = trav;

        trav = trav->next;

        free(aux);
    }

    free(trav);
    free(this);
}

/**
 * linked_list_insert_at_head inserts a new node at the first position of the list
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list which will have a new element inserted
 * @param data is the value of the element which will be inserted
 *  
 * @return if the element was correctly inserted
 * */
bool linked_list_insert_at_head(ptr_linked_list this, int data) {
    if(!this) {
        perror("Cannot search through a non allocated list");
        return false;
    }

    ptr_node_t new_node = ALLOC(1, node_t);

    if(!new_node) {
        perror("Could not allocate node object");
        return false;
    }

    new_node->data = data;
    new_node->next = NULL;

    if(linked_list_is_empty(this)) {
        this->head = new_node;

        this->len++;

        return true;
    }

    new_node->next = this->head;
    this->head = new_node;

    this->len++;

    return true;
}

/**
 * linked_list_insert_at inserts a new node at a given index
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list which will have a new element inserted at
 * @param data is the value of the new node 
 * @param index is the index of the list that the new node will be inserted
 * 
 * @return if the element was properly inserted
 * */
bool linked_list_insert_at(ptr_linked_list this, int data, size_t index) {
    if(index == HEAD_INDEX)
        return linked_list_insert_at_head(this, data);

    if(!this) {
        perror("Cannot search through a non allocated list");
        return false;
    }

    if(linked_list_is_outside(this, index)) {
        perror("Cannot insert an element outside of the list");
        return false;
    }

    ptr_node_t new_node = ALLOC(1, node_t);

    if(!new_node) {
        perror("Could not allocat node object");
        return false;
    }

    new_node->data = data;
    new_node->next = NULL;

    ptr_node_t trav = this->head;

    for(int i = 0; i < index - 1; i++)
        trav = trav->next;
    
    new_node->next = trav->next;
    trav->next = new_node;

    this->len++;

    return true;
}

/**
 * linked_list_remove_last remove o último elemento de uma linked list
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list which will have it last element removed
 * 
 * @return the lookup result of the operation, if the status is not ok then the value should not be considered 
 * */
lookup_result_t linked_list_remove_last(ptr_linked_list this) {
    return linked_list_remove_at(this, this->len - 1);
}

/**
 * linked_list_reversed returns a new linked list which all elements are the first list but reversed
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list which will be reversed
 * 
 * @return a new heap allocated list which needs to freed later
 * */
ptr_linked_list linked_list_reverse(ptr_linked_list this) {
    if(!this) {
        perror("Cannot reverse a non allocated list");
        return false;
    }
    
    ptr_linked_list reversed = linked_list_new();

    for(int i = this->len - 1; i >= 0; i--) {
        lookup_result_t result = linked_list_get(this, i);

        if(linked_list_is_ok(&result)) 
            linked_list_append(reversed, result.value);
    }

    return reversed;
}

/**
 * linked_list_map iterates over a list and applies a callback to each element, generating a new list which needs to be freed
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list which will be mapped
 * @param fn is the function which all the elements of this will be applied
 * 
 * @return a new heap allocated list with all the values of this which passed by fn
 * */
ptr_linked_list linked_list_map(ptr_linked_list this, callback fn) {
    if(!this) {
        perror("Cannot iterate over a non allocated list");
        return NULL;
    }

    if(!fn) {
        perror("Cannot call a null function");
        return NULL;
    }

    ptr_linked_list mapped_list = linked_list_new();

    for(int i = 0; i < this->len; i++) {
        lookup_result_t result = linked_list_get(this, i);

        if(linked_list_is_ok(&result))
            linked_list_append(mapped_list, fn(result.value));
    }

    return mapped_list;
}

/**
 * linked_list_filter iterates over a list and returns a new list with all the elements that pass through a filter_callback
 * 
 * @author Gustavo Reis Bauer
 * 
 * @param this is the list which will be filtered
 * @param fn is the filter function
 * 
 * @return a new heap allocated list which have all the elements of this which returns true when passed on fn
 * */
ptr_linked_list linked_list_filter(ptr_linked_list this, filter_callback fn) {
    if(!this) {
        perror("Cannot iterate over a non allocated list");
        return NULL;
    }

    if(!fn) {
        perror("Cannot call a null function");
        return NULL;
    }

    ptr_linked_list filtered = linked_list_new();

    for(int i = 0; i < this->len; i++) {
        lookup_result_t result = linked_list_get(this, i);

        if(linked_list_is_ok(&result)) {
            if(!fn(result.value)) continue;
            
            linked_list_append(filtered, result.value);
        }
    }

    return filtered;
}
