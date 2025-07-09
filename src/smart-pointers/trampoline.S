.section .text
.global trampoline
.type trampoline, @function

trampoline:
# call hijacked. This pushes the address of the next instruction.
# when hijacked returns, we jump directly to the address in eax.
# eax contains the returned value of hijacked.
call hijacked
#if defined(__x86_64__)
    jmp *%rax
#elif defined(__i386__) || defined(_M_IX86)
    jmp *%eax
#endif

.section .note.GNU-stack,"",@progbits