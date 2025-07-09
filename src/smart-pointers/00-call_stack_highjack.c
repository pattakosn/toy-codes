#include <stdio.h>
#include <stdint.h>

// The function to hijack to
void hijacked () {
  printf ("hijacked\n");
}

void f () {
  printf ("f starts\n");

  // Use uintptr_t for pointer arithmetic, and select correct base pointer
  // get the value of ebp/rbp
  uintptr_t *base;
#if defined(__x86_64__)
  __asm__("movq %%rbp, %0" : "=r"(base));
#elif defined(__i386__)
  __asm__("movl %%ebp, %0" : "=r"(base));
#endif

  // Overwrite the return address on the stack
  // base[1] is the saved return address in the stack frame layout
  base[1] = (uintptr_t) hijacked;

  printf ("f ends\n");
}

int main () {
  printf ("main starts\n");
  f ();
  printf ("main ends\n");
  return 0;
}