#ifndef UTHREADS_H
#define UTHREADS_H


#include <ucontext.h>
#include <stdbool.h>

typedef struct uthread {
  ucontext_t context; 	 // context of the thread
  void (*func)(int);  	 // function pointer
  int arg;    	      	 // argument passed a creation
  bool finished;      	 // thread finished execution
  struct uthread *next;  // pointer to the next thread in the queue
} uthread_t;

void uthread_init();
uthread_t *uthread_create(void (*func)(int), int arg);
void uthread_yield();
void uthread_join(uthread_t *uthread);
void uthread_exit();
void uthread_cleanup(bool force);
#endif // UTHREADS_H
