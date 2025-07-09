# This is GNU assembler syntax (aka AT-T syntax) (src, dest)
.section .text
.globl trampoline
.type trampoline, @function

trampoline:
# call hijacked. This pushes the address of the next instruction.
# when hijacked returns, we jump directly to the address in eax.
# eax contains the returned value of hijacked.
call do_free
#if defined(__x86_64__)
jmp *%rax
#elif defined(__i386__) || defined(_M_IX86)
jmp *%eax
#endif

.section .note.GNU-stack,"",@progbits