global _start
section .text


_start:
  pop r14
  push 15
  pop rax
  push rbp
  mov rbp, rsp
  sub rsp, 8
  xor rcx, rcx

  mov rbx, 10

.rep:
    xor rdx, rdx
    div rbx
    cmp rax, rdx
    je .check_dec
.back_dec:
    add rdx, '0'
    mov r9, rsp
    add r9, rcx
    mov [r9], rdx
    inc rcx
    jmp .rep

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
    push r14
    ret
