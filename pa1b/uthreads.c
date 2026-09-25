#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "uthreads.h"

void uthread_init(){
    return;
}

uthread_t *uthread_create(void (*func)(int), int arg){
    return NULL;
}

void uthread_yield(){
    return;
}

void uthread_join(uthread_t *uthread){
    return;
}

void uthread_exit(){
    return;
}

void uthread_cleanup(bool force){
    return;
}
