
section .text
global _start

_start:     push rax
            finit
            fild dword [rsp]
            fsqrt
            push 10
            fimul dword [rsp]
            fist dword [rsp]
            movsx rax, dword [rsp]
            add rsp, 16
            push rax
