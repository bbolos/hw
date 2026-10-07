#include "suballocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>

typedef unsigned char byte;
static byte * memory = NULL;

//defenitie region headers
typedef struct Header{
    uint32_t magic;
    uint32_t size;
    struct Header *next;
    struct Header *prev;
} Header;

#define HEADER_SIZE sizeof(Header)
static Header *free_list_ptr = NULL;

//magic constants
#define FREE_MAGIC 0xDEADBEEF
#define ALLOC_MAGIC 0xDEAFBEAD

//Suballocator functies
void suballocator_init(){
    //not empty return
    if(memory != NULL){
        return;
    }

    //init memory and reset if fail
    memory = mmap(NULL, 1048576, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(memory == MAP_FAILED){
        memory = NULL;
        fprintf(stderr, "mmap failed\n");
        abort();
    }

    //init header and set free_list_ptr
    Header h = (Header *) memory;
    h -> magic = 0xDEADBEEF;
    h -> size = 1048576;
    h -> next = h;
    h -> prev = h;

    free_list_ptr = h;
}

void *suballocator_malloc(u_int32_t n){
    if (free_list_ptr == NULL){
        return NULL;
    }

    u_int32_t size = n + HEADER_SIZE;
    Header *curr = free_list_ptr;
    Header *found = NULL;

    //zoek naar plek met genoeg ruimte
    do{
        if(curr -> magic != FREE_MAGIC){
            fprintf(stderr, "Memory corruption\n");
            abort();
        }

        if(curr -> size >= size){
            found = curr;
            break;
        }

        curr = curr -> next;
    } while(curr != free_list_ptr);

    if(found == NULL){
        return NULL;
    }

    //blok halveren tot het nietmeer kleiner kan
    while((found -> size) / 2 >= size){
        u_int32_t half_size = (chosen -> size) / 2;
        chosen -> size = half_size;

        //maak nieuwe helft
        Header *next = (Header *)((byte *)found + half_size);
        next -> magic = FREE_MAGIC;
        next -> size = half_size;

        //voeg nieuwe helft toe
        next -> next = found -> next;
        next -> prev = found;
        found -> next -> prev = next;
        found -> next = next;
    }

    //invariant controleren
    if((found -> next) == found){
        return NULL;
    }

    //verwijder uit free list
    found -> prev -> next = found -> next;
    found -> next -> prev = found -> prev;

    if(free_list_ptr == found){
        free_list_ptr = found -> next
    }

    found -> magic = ALLOC_MAGIC;

    return (void *)((byte *)found + HEADER_SIZE);
}

void suballocator_free(void *p){
    return;
}

void suballocator_exit(void){
    //reset when not empty
    if(memory != NULL){
        munmap(memory, 1048576);
        memory = NULL;
        free_list_ptr = NULL;
    }
}
