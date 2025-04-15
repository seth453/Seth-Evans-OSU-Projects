/*
 * In this file, you will write the structures and functions needed to
 * implement a hash table.  Feel free to implement any helper functions
 * you need in this file to implement a hash table.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>

#include "dynarray.h"
#include "list.h"
#include "hash_table.h"


struct ht_entry { 
    void* key; 
    void* value;
}; 

/*
 * This is the structure that represents a hash table.  You must define
 * this struct to contain the data needed to implement a hash table.
 */
struct ht { 
    struct dynarray** buckets;
    int capacity; 
    int size; 
}; 


/*
 * This function should allocate and initialize an empty hash table and
 * return a pointer to it.
 */
struct ht* ht_create(){
    struct ht* ht = malloc(sizeof(struct ht)); 
    if (ht == NULL) { 
    fprintf(stderr, "Memory allocation failed ht.\n");  
    exit(EXIT_FAILURE);
}

ht->capacity = DYNARRAY_INIT_CAPACITY; 
ht->size = 0; 

ht->buckets = malloc(ht->capacity * sizeof(struct dynarray*));
if (ht->buckets == NULL) {  
    fprintf(stderr, "Memory allocation failed ht buckets.\n");  
    free(ht); 
    exit(EXIT_FAILURE);
}

for (int i = 0; i < ht->capacity; ++i)
{
    ht->buckets[i] = dynarray_create();
} 

return ht;
}

/*
 * This function should free the memory allocated to a given hash table.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the hash table.  That is the responsibility of the caller.
 *
 * Params:
 *   ht - the hash table to be destroyed.  May not be NULL.
 */
void ht_free(struct ht* ht){
    if (ht == NULL) { 
    return;
}

for (int i = 0; i < ht->capacity; ++i)
{
    dynarray_free(ht->buckets[i]);
} 

free(ht->buckets); 
free(ht); 

}

/*
 * This function should return 1 if the specified hash table is empty and
 * 0 otherwise.
 *
 * Params:
 *   ht - the hash table whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if ht is empty and 0 otherwise.
 */
int ht_isempty(struct ht* ht){
    return (ht->size == 0);
}


/*
 * This function returns the size of a given hash table (i.e. the number of
 * elements stored in it, not the capacity).
 */
int ht_size(struct ht* ht){  
    return ht->size;
}


/*
 * This function takes a key, maps it to an integer index value in the hash table,
 * and returns it. The hash algorithm is totally up to you. Make sure to consider
 * Determinism, Uniformity, and Speed when design the hash algorithm
 *
 * Params:
 *   ht - the hash table into which to store the element.  May not be NULL.
 *   key - the key of the element to be stored
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
int ht_hash_func(struct ht* ht, void* key, int (*convert)(void*)){
    int hash = convert(key) % ht->capacity; 
    return (hash < 0) ? hash + ht->capacity : hash;
} 

/*
 * This function should insert a given element into a hash table with a
 * specified key.  Note that you cannot have two same keys in one hash table.
 * If the key already exists, update the value associated with the key.  
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * Resolution of collisions is requried, use either chaining or open addressing.
 * If using chaining, double the number of buckets when the load factor is >= 4
 * If using open addressing, double the array capacity when the load factor is >= 0.75
 * load factor = (number of elements) / (hash table capacity)
 *
 * Params:
 *   ht - the hash table into which to insert an element.  May not be NULL.
 *   key - the key of the element
 *   value - the value to be inserted into ht.
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */


void ht_insert(struct ht* ht, void* key, void* value, int (*convert)(void*)){
    int index = ht_hash_func(ht, key, convert); 
    struct dynarray* bucket = ht->buckets[index]; 

    //loop through bucket to check if key already exists 
    for (int i = 0; i < dynarray_size(bucket); ++i)
    {
        struct ht_entry* entry = dynarray_get(bucket, i); 
        if (entry != NULL && entry->key != NULL && convert(entry->key) == convert(key))
        {
            entry->value = value; 
            return;
        }
    }
}


/*
 * This function should search for a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, return the corresponding value (void*) of the element,
 * otherwise, return NULL
 *
 * Params:
 *   ht - the hash table into which to loop up for an element.  May not be NULL.
 *   key - the key of the element to search for
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void* ht_lookup(struct ht* ht, void* key, int (*convert)(void*)) {
      int index = ht_hash_func(ht, key, convert); 
      struct dynarray* bucket = ht->buckets[index];


       //loop through bucket to find key 
       for (int i = 0; i < dynarray_size(bucket); ++i)
        {
            struct ht_entry* entry = dynarray_get(bucket, i); 
            if (entry != NULL && entry->key != NULL && convert(entry->key) == convert(key))
            {
                return entry->value;
            }
        } 
      return NULL;
} 



/*
 * This function should remove a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, remove the element and return, otherwise, do nothing and return 
 *
 * Params:
 *   ht - the hash table into which to remove an element.  May not be NULL.
 *   key - the key of the element to remove
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void ht_remove(struct ht* ht, void* key, int (*convert)(void*)){
     int index = ht_hash_func(ht, key, convert); 
     struct dynarray* bucket = ht->buckets[index]; 

     //loop to find bucket and remove 
     for (int i = 0; i < dynarray_size(bucket); ++i)
     {
         struct ht_entry* entry = dynarray_get(bucket, i); 
         if (entry != NULL && entry->key != NULL && convert(entry->key) == convert(key)) 
         {
             dynarray_remove(bucket, i); 
             free(entry); 
             ht->size--; 
             return;
         }
     }
}
