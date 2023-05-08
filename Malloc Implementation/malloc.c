#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "malloc.h"

metadata_t *address_list;

enum my_malloc_err my_malloc_errno;

metadata_t *find_right(metadata_t *freed_block) {
    metadata_t *temp;
    for (temp = address_list; temp != NULL; temp = temp->next) {
    if ((uintptr_t) temp == (uintptr_t) freed_block + TOTAL_METADATA_SIZE + freed_block->size) {
        return temp;
    }
}
    return NULL;
}

metadata_t *find_left(metadata_t *freed_block) {
    metadata_t *temp;
    for (temp = address_list; temp != NULL && temp < freed_block; temp = temp->next) {
        if (((uintptr_t) temp + TOTAL_METADATA_SIZE + temp->size) == (uintptr_t) freed_block) {
            return temp;
        }
    }
    return NULL;
}

 void merge(metadata_t *left, metadata_t *right) {
    left->size += right->size + TOTAL_METADATA_SIZE;
    left->next = right->next;
 }

 metadata_t *split_block(metadata_t *block, size_t size) {
    size_t total = size + TOTAL_METADATA_SIZE;
    metadata_t *new = (metadata_t*) ((uintptr_t) block + TOTAL_METADATA_SIZE + block->size - total);
    new->size = size;
    block->size -= total;
    return new;
 }

 void add_to_addr_list(metadata_t *block) {
    if (address_list == NULL) {
        address_list = block;
        address_list->size = block->size;
        address_list->next = NULL;
        return;
    }
    metadata_t **ptr = &address_list;
    while (*ptr != NULL && *ptr < block) {
        ptr = &(*ptr)->next;
    }
    block->next = *ptr;
    *ptr = block;
    
}

 void remove_from_addr_list(metadata_t *block) {
    metadata_t *curr = address_list;
    if (!curr) {
        return;
    } else if (curr == block) {
        address_list = curr->next;
    }

    metadata_t *next;
    while ((next = curr->next) && (uintptr_t) block > (uintptr_t) next) {
        curr = next;
    }
    if (next == block) {
        curr->next = next->next;
    }
}

 metadata_t *find_best_fit(size_t size) {
    metadata_t *temp;
    metadata_t *second = NULL;

    for (temp = address_list; temp != NULL; temp = temp->next) {
        if (temp->size == size) {
            return temp;
        }
        if (temp->size > size) {
            if (second == NULL || temp->size < second->size) {
                second = temp;
            }
        }
    }
    return second;
 }

void *my_malloc(size_t size) {
    my_malloc_errno = NO_ERROR;
    
    if (size <= 0) {
    return NULL;
    }
    if (size + TOTAL_METADATA_SIZE > SBRK_SIZE) {
        my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
        return NULL;
    }

    metadata_t *block = find_best_fit(size);
    if (block == NULL) {
        metadata_t *ptr = my_sbrk(SBRK_SIZE);
        if (ptr == (void*) -1) {
            my_malloc_errno = OUT_OF_MEMORY;
            return NULL;
        }
        ptr->size = SBRK_SIZE - TOTAL_METADATA_SIZE;
        ptr->next = NULL;
        my_free((void*) ((uintptr_t) ptr + TOTAL_METADATA_SIZE));
        return my_malloc(size);
    }
    if (block->size < size + MIN_BLOCK_SIZE) {
        remove_from_addr_list(block);
        return (void*) ((uintptr_t) block + TOTAL_METADATA_SIZE);
    }
    return (void*) ((uintptr_t) split_block(block, size) + TOTAL_METADATA_SIZE);
}

void my_free(void *ptr) {
    my_malloc_errno = NO_ERROR;

    if (ptr == NULL) {
    return;
    }

    metadata_t *start = (metadata_t*) ((uintptr_t) ptr - TOTAL_METADATA_SIZE);

    metadata_t *right = find_right(start);
    while (right != NULL) {
        remove_from_addr_list(right);
        merge(start, right);
        right = find_right(start);
    }

    metadata_t *left;
    do {
        left = find_left(start);
        if (left != NULL) {
            remove_from_addr_list(left);
            merge(left, start);
            start = left;
        }
    } while (left != NULL);

    add_to_addr_list(start);
}

void *my_realloc(void *ptr, size_t size) {
    my_malloc_errno = NO_ERROR;

    if (size == 0) {
        my_free(ptr);
        return NULL;
    } else if (ptr == NULL) {
        return my_malloc(size);
    } else {
        size_t prev = ((metadata_t*)((uintptr_t) ptr - TOTAL_METADATA_SIZE))->size;
        metadata_t *ptr2 = my_malloc(size);
        if (ptr2 == NULL) {
            return NULL;
        }
        if (size < prev) {
            size = prev;
        }
        memcpy(ptr2, ptr, size);
        my_free(ptr);
        return ptr2;
    }
}

void *my_calloc(size_t nmemb, size_t size) {
    my_malloc_errno = NO_ERROR;

    metadata_t *start = my_malloc(nmemb * size);

    if (start == NULL) {
        return NULL;
    }
    memset(start, '\0', nmemb * size);
    return start;
}
