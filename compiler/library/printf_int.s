global _start
section .text


_start:


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

  cmp rax, 2147483646
  ja .minus

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

.back_dec_1:
    mov rdx, rax
    jmp .back_dec

.minus:
    mov rdx, rax ;превращение в отрицательное число и пишем минус
    xor rax, rax
    sub rax, rdx

    mov rsi, rsp
    mov dword [rsp], 45
    push rax
    mov rax, 1
    mov rdi, 1
    mov rdx, 1
    syscall
    pop rax
    xor rcx, rcx
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

    mov rsi, rsp
    mov dword [rsp], 13
    mov rax, 1
    mov rdi, 1
    mov rdx, 1
    syscall
    mov dword [rsp], 10
    syscall

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
