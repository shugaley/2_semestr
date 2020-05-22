
section .text
global _start

_start:     call next
            mov rax, 60
            xor rdi, rdi
            syscall

next:       pop r14
            push r14
            ret
