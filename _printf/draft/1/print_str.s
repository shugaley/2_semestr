section .text

global _start

_start:       mov rax, 0x01
              mov rdi, 1
              mov rsi, Msg
              mov rdx, MsgLen
              syscall

              mov rax, 0x3c
              xor rdi, rdi
              syscall

section       .data

Msg:          db "_Hello", 0x0a
MsgLen        equ $ - Msg
