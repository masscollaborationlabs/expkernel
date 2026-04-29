.intel_syntax noprefix

.section .text
.code32
.global _start
.extern kernel_main

_start:
    call kernel_main
1:
    cli
    hlt
    jmp 1b

.section .note.GNU-stack,"",@progbits
