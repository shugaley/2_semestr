global _start
section .text


;dstr

_start:
;save if you need
            push rsi
            push rdi
            push r9
            push rdx
            push rcx

            push rbp
            mov rbp, rsp
            sub rsp, 16


            mov rdi, 2        ;reading
            mov rsi, rsp
            mov rdx, 16
            xor rax, rax
            syscall

            xor rcx, rcx
            mov dl, [rsi]    ;chech -
            cmp dl, '-'
            jne check_dec
            mov rcx, 1


            ;dec rsi
check_dec:  inc rsi
            mov dl, [rsi]
            cmp dl, 10         ;cmp end of input
            jne check_dec

            mov rdi, 1
            xor r9, r9
scanf_dec:  dec rsi
            xor rax, rax

            mov al, [rsi]
            cmp al, '.'     ;check .
            je scanf_dec
            sub al, '0'

            mul rdi
            add r9, rax

            mov rax, rcx
            add rax, rsp
            cmp rsi, rax
            je finish_scanf

            mov rax, rdi
            mov rdi, 10
            mul rdi
            mov rdi, rax
            jmp scanf_dec

finish_scanf:
            mov rax, r9

            cmp rcx, 1
            jne finish
            xor r9, r9
            sub r9, rax
            mov rax, r9

finish:     add rsp, 16
            mov rsp, rbp
            pop rbp

;save if you need
            pop rcx
            pop rdx
            pop r9
            pop rdi
            pop rsi

            push rax
