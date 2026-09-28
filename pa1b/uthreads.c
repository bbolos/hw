#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "uthreads.h"

#define PAGE_SIZE 4096
#define STACK_SIZE (1024 * 1024)

//state var
static bool initialized = false;
static uthread_t *current_thread = NULL;
static uthread_t main_thread;

//queue var
static uthread_t *queue_head = NULL;
static uthread_t *queue_tail = NULL;

//helper func
static void enqueue(uthread_t *thread) {
    thread->next = NULL;
    if (queue_tail == NULL) {
        queue_head = thread;
        queue_tail = thread;
    } else {
        queue_tail->next = thread;
        queue_tail = thread;
    }
}

static uthread_t *dequeue(void) {
    if (queue_head == NULL) {
        return NULL;
    }
    uthread_t *thread = queue_head;
    queue_head = queue_head->next;
    if (queue_head == NULL) {
        queue_tail = NULL;
    }
    thread->next = NULL;
    return thread;
}

static void wrapper() {
    current_thread->func(current_thread->arg);
    uthread_exit();
}

//thread func
void uthread_init(){
    if (initialized) return;

    main_thread.finished = false;
    main_thread.next = NULL;
    getcontext(&main_thread.context);

    current_thread = &main_thread;
    initialized = true;
}

uthread_t *uthread_create(void (*func)(int), int arg){
    if (initialized == NULL) return NULL;

    uthread_t *t = malloc(sizeof(uthread_t));
    if (t == NULL) return NULL;

    //init uthread
    t->func = func;
    t->arg = arg;
    t->finished = false;
    t->next = NULL;

    //1mb stack en 4kb guard
    size_t total_stack = STACK_SIZE + PAGE_SIZE;
    void *stack_mem = mmap(NULL, total_stack, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (stack_mem == MAP_FAILED) {
        free(t);
        return NULL;
    }

    mprotect(stack_mem, PAGE_SIZE, PROT_NONE);
    //init t en stackpointer naar top
    getcontext(&t->context);
    t->context.uc_stack.ss_sp = (char *)stack_mem + PAGE_SIZE;
    t->context.uc_stack.ss_size = STACK_SIZE;
    t->context.uc_link = NULL;

    makecontext(&t->context, (void (*)(void))wrapper, 0);

    enqueue(t);
    return t;
}

void uthread_yield(){
    if (!initialized) return;
    //thread uit queue
    uthread_t *next = dequeue();
    if (!next) return;
    //voeg opnieuw toe als niet klaar
    uthread_t *prev = current_thread;
    if (!prev->finished) {
        enqueue(prev);
    }
    //wissel context
    current_thread = next;
    swapcontext(&prev->context, &next->context);
}

void uthread_join(uthread_t *uthread){
    if (!initialized || !uthread) return;
    //blijf doorgaan tot thread klaar is
    while (!uthread->finished) {
        uthread_yield();
    }
}

void uthread_exit(){
    if (!initialized) return;
    //thread klaar
    current_thread->finished = true;
    uthread_t *next = dequeue();
    //nieuwe thread uit queue wanneer mogelijk
    if (next) {
        current_thread = next;
        setcontext(&next->context);
    }
}

void uthread_cleanup(bool force){
    if (!initialized || current_thread != &main_thread) return;
    //wacht tot queue klaar is bij geen force
    if (!force) {
        while (queue_head) {
            uthread_yield();
        }
    }
    //alles uit queue vrijgeven
    uthread_t *curr = queue_head;
    while (curr) {
        uthread_t *next = curr->next;
        void *stack_mem = (char *)curr->context.uc_stack.ss_sp - PAGE_SIZE;
        munmap(stack_mem, STACK_SIZE + PAGE_SIZE);
        free(curr);
        curr = next;
    }
    //reset state vars
    queue_head = queue_tail = NULL;
    current_thread = NULL;
    initialized = false;
}

