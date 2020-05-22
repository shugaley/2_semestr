section .text

global _start
_start:     nop
            nop
            nop
            mov rax, 1
            mov rdi, 1
            mov rsi, $
            mov rdx, 10
            syscall
            mov rax, 60
            mov rdi, 0
            syscall
            nop
            nop
            nop
