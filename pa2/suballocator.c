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

void suballocator_init(){
    //not empty return
    if(memory != null){
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
