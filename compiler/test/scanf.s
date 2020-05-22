global _start
section .text


;dstr

_start:
;save if you need
            push rsi
            push rdi
            push r9
            push rdx

            push rbp
            mov rbp, rsp
            sub rsp, 8



read:       mov rdi, 2
            mov rsi, rsp
            mov rdx, 8
            xor rax, rax
            syscall

            dec rsi
check_dec:  inc rsi
            mov dl, [rsi]
            cmp dl, 10
            jne check_dec

            mov rdi, 1
            xor r9, r9
scanf_dec:  dec rsi
            xor rax, rax

            mov al, [rsi]
            sub al, '0'

            mul rdi
            add r9, rax

            cmp rsi, rsp
            je finish

            mov rax, rdi
            mov rdi, 10
            mul rdi
            mov rdi, rax
            jmp scanf_dec

finish:     mov rax, r9

            add rsp, 8
            mov rsp, rbp
            pop rbp

;save if you need
            pop rdx
            pop r9
            pop rdi
            pop rsi

            push rax
