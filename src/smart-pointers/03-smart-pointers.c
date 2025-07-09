#ifndef _SMART
#define _SMART
void *free_on_exit (void *);
#endif
#include <stdlib.h> // free
#include <string.h> // memset
#include <stdint.h> // uintptr_t
#include <stdio.h> // printf

/* these limits are arbitrary. */
#define STACK_SIZE 256
#define MAX_PER_FRAME 32

typedef struct {
  uintptr_t caller_ebp; /* ebp of the caller. This identifes the frame. */
  uintptr_t caller_eip; /* the original return eip of the caller. */
  void *tracked_pointers[MAX_PER_FRAME];
  int tail; /* points to one past last entry. */
} tracked_stack_entry_t;

typedef struct {
  tracked_stack_entry_t stack[STACK_SIZE];
  int tail; /* points to one past last entry. */
} tracked_stack_t;

/* forward declare the assembly trampoline. */
void trampoline(void);

tracked_stack_t tracked = {0};

uintptr_t do_free () {
  tracked_stack_entry_t *entry = tracked.stack + (tracked.tail - 1);
  tracked.tail--; /* pop. */
  for (int i = 0; i < MAX_PER_FRAME; i++) {
    if (entry->tracked_pointers[i] == 0) break;
    free(entry->tracked_pointers[i]);
  }
  return entry->caller_eip;
}

void *free_on_exit (void *entry) {
  uintptr_t *caller_fp;
  /* get the value of ebp. */
#if defined(__x86_64__)
  __asm__("movq %%rbp, %0" : "=r"(caller_fp));
#elif defined(__i386__)
  __asm__("movl %%ebp, %0" : "=r"(caller_fp));
#endif

  /* check if there is a pre-existing stack entry for this caller
   * (identified by caller's ebp). */
  tracked_stack_entry_t *tracked_entry = NULL;
printf
  if (tracked.tail > 0 &&
      tracked.stack[tracked.tail - 1].caller_ebp == (uintptr_t) caller_fp) {
        /* re-use. */
        tracked_entry = &tracked.stack[tracked.tail - 1];
      } else {
        /* make a new entry. */
        tracked_entry = &tracked.stack[tracked.tail++];
        memset (tracked_entry, 0, sizeof (*tracked_entry));
        tracked_entry->caller_ebp = (uintptr_t) caller_fp;
        /* hijack caller's return eip to return to do_free. */
        tracked_entry->caller_eip = caller_fp[1];
        caller_fp[1] = (uintptr_t) trampoline;
      }

  /* push the passed pointer. */
  if (tracked_entry->tail < MAX_PER_FRAME) {
    tracked_entry->tracked_pointers[tracked_entry->tail++] = entry;
  } else {
    /* Optional: handle overflow */
    fprintf(stderr, "Too many allocations tracked in this frame!\n");
    abort();
  }
  return entry;
}

void sample_function() {
  // Allocate and automatically track pointers for freeing at function exit
  char *a = (char*)free_on_exit(malloc(8  * sizeof(char)));
  char *b = (char*)free_on_exit(malloc(16 * sizeof(char)));
  char *c = (char*)free_on_exit(malloc(32 * sizeof(char)));
  strcpy(a, "Hello");
  strcpy(b, "Smart");
  strcpy(c, "World!");

  printf("a: %s, b: %s, c: %s\n", a, b, c);

  // You can manually free some if you want, but all tracked pointers are freed on return
  //free(a); // This is safe but not required
  // free(b);
  // free(c);
}

int main() {
  printf("Testing smart free-on-exit stack\n");
  sample_function();
  printf("Function returned, memory should be freed!\n");
  return 0;
}