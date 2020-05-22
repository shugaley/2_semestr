global _start
section .text


_start:

    ;mov rax, 15

  ;pop rax

  push rcx
  push rbx
  push rdx
  push rsi
  push rdi
  push r9

  push rbp
  mov rbp, rsp
  sub rsp, 8
  xor rcx, rcx

  mov rbx, 10

  cmp rax, 0
  je .back_dec_1


.rep:
    xor rdx, rdx
    div rbx
    cmp rax, rdx
    je .check_dec
.back_dec:
    add rdx, '0'
    mov r9, rsp
    add r9, rcx
    mov [r9], dl
    inc rcx
    jmp .rep

.back_dec_1:
    mov rdx, rax
    jmp .back_dec

.check_dec:
    cmp rax, 0
    jne .back_dec

.rep_2:
    mov rax, 1
    mov rsi, rsp
    add rsi, rcx
    dec rsi
    mov rdi, 1
    mov rdx, 1
    push rcx
    syscall
    pop rcx
    dec rcx
    cmp rcx, 0
    jne .rep_2

    add rsp, 8
    mov rsp, rbp
    pop rbp

    pop r9
    pop rdi
    pop rsi
    pop rdx
    pop rbx
    pop rcx

    push rax
