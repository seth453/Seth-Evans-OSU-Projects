/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include "pq.h"
#include "dynarray.h"

struct pq {
    struct dynarray* heap;
};


struct pq_node {
    void* value;
    int priority;
};

struct pq* pq_create() {
    struct pq* pq = malloc(sizeof(struct pq));
    if (pq == NULL) {
        return NULL;
    }
    
    pq->heap = dynarray_create();
    if (pq->heap == NULL) {
        free(pq);
        return NULL;
    }
    
    return pq;
}

void pq_free(struct pq* pq) {
    if (pq) {
        dynarray_free(pq->heap);
        free(pq);
    }
}

int pq_isempty(struct pq* pq) {
    return dynarray_size(pq->heap) == 0;
}

void pq_insert(struct pq* pq, void* value, int priority) {
    // Create a new node to insert into the heap
    struct pq_node* new_node = malloc(sizeof(struct pq_node));
    if (new_node == NULL) {
        return;
    }
    new_node->value = value;
    new_node->priority = priority;
    
    // Insert the new node into the heap and perform heapify-up
    dynarray_insert(pq->heap, new_node);
int index = dynarray_size(pq->heap) - 1;
int parent = (index - 1) / 2;
while (index > 0 && ((struct pq_node*)dynarray_get(pq->heap, parent))->priority > priority) {
    // Perform swapping logic here...

        dynarray_set(pq->heap, index, dynarray_get(pq->heap, parent));
        index = parent;
        parent = (index - 1) / 2;
    }
    dynarray_set(pq->heap, index, new_node);
}

void* pq_first(struct pq* pq) {
    return ((struct pq_node*)dynarray_get(pq->heap, 0))->value;
}

int pq_first_priority(struct pq* pq) {
    return ((struct pq_node*)dynarray_get(pq->heap, 0))->priority;
}

void* pq_remove_first(struct pq* pq) {
    if (pq_isempty(pq)) {
        return NULL;
    }
    
    // Remove the root node and perform heapify-down
    void* result = pq_first(pq);
    struct pq_node* last_node = dynarray_get(pq->heap, dynarray_size(pq->heap) - 1);
    dynarray_set(pq->heap, 0, last_node);
    
    int index = 0;
    while (1) {
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int smallest = index;
        
        if (left_child < dynarray_size(pq->heap) && ((struct pq_node*)dynarray_get(pq->heap, left_child))->priority < ((struct pq_node*)dynarray_get(pq->heap, smallest))->priority) {
            smallest = left_child;
        }
        
        if (right_child < dynarray_size(pq->heap) && ((struct pq_node*)dynarray_get(pq->heap, right_child))->priority < ((struct pq_node*)dynarray_get(pq->heap, smallest))->priority) {
            smallest = right_child;
        }
        
        if (smallest != index) {
            dynarray_set(pq->heap, index, dynarray_get(pq->heap, smallest));
            index = smallest;
        } else {
            break; // Fixed: Exit the loop if heap property is satisfied
        }
    }
    
    dynarray_set(pq->heap, index, last_node);
    
    return result;
}
