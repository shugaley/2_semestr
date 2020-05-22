global _start
section .text


_start:
  nop
  nop
  nop
  ;pop rax
  push rbp
  mov rbp, rsp
  sub rsp, 8
  xor r15, r15

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
    add r9, r15
    mov byte [r9], dl
    inc r15
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
    xor r15, r15
    jmp .rep

.Dot:
    mov rax, 1
    mov rdx, 1
    mov rdi, 1
    mov r10, rsp
    add r10, r13
    inc r10
    mov byte [r10], 46
    mov rsi, r10
    syscall
    jmp .After_dot


.check_dec:
    cmp rax, 0
    jne .back_dec


    mov r13, r15
.rep_2:
    cmp r15, 2
    je .Dot
.After_dot:
    mov rax, 1
    mov rsi, rsp
    add rsi, r15
    dec rsi
    mov rdi, 1
    mov rdx, 1
    syscall
    dec r15
    cmp r15, 0
    jne .rep_2



    mov rsi, rsp
    mov dword [rsp], 13
    mov rax, 1
    mov rdi, 1
    mov rdx, 1
    syscall
    mov dword [rsp], 10
    syscall

    add rsp, 16
    mov rsp, rbp
    pop rbp
    push rax
    nop
    nop
    nop
