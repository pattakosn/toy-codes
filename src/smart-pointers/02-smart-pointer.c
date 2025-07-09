#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* forward declare the assembly trampoline. */
void trampoline(void);
uintptr_t return_address = 0;
void *tracked_pointer;

uintptr_t do_free () {
  free (tracked_pointer);
  return return_address;
}

void *free_on_exit (void *ptr) {
  uintptr_t* base;
#if defined(__x86_64__)
  __asm__("movq %%rbp, %0" : "=r"(base));
#elif defined(__i386__)
  __asm__("movl %%ebp, %0" : "=r"(base));
#endif

  // save and change the caller's return address.
  return_address = base[1];
  base[1] = (uintptr_t) trampoline;
  tracked_pointer = ptr;
  return ptr;
}

void f () {
  char *resource = free_on_exit (malloc (1));
  (void) resource;
}

int main () {
  f ();
}