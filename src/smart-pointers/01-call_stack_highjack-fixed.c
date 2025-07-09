#include <stdio.h>
#include <stdint.h>

// forward declare the assembly trampoline.
void trampoline();
uintptr_t return_address = 0;

uintptr_t hijacked () {
  printf ("hijacked\n");
  return return_address;
}

void f () {
  printf ("f starts\n");

  // Use uintptr_t for pointer arithmetic, and select correct base pointer
  // get the value of ebp/rbp
  uintptr_t* base;
#if defined(__x86_64__)
  __asm__("movq %%rbp, %0" : "=r"(base));
#elif defined(__i386__)
  __asm__("movl %%ebp, %0" : "=r"(base));
#endif

  // save the return address.
  return_address = base[1];
  // Overwrite the return address on the stack
  // base[1] is the saved return address in the stack frame layout
  // change the return address.
  base[1] = (uintptr_t) trampoline;

  printf ("f ends\n");
}

int main () {
  printf ("main starts\n");
  f ();
  printf ("main ends\n");
  return 0;
}