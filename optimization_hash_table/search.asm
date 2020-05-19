section .text

sizeof_size_t equ 8
sizeof_ptr    equ 8
sizeof_elem   equ 24

;extern strcmp

global _nListSearch

;------------------------------------------
;Func search word in word_list
;
;Entry:     rsi - ptr to list (list_name)
;           rdi - ptr to char* (word)
;
;Destroy:   rbx rcx r12 r8 r9
;           rsi rdi rax
;
;Return:    rax == pos (if not found rax == 0)
;------------------------------------------

_nListSearch:   push rbx
                push rcx
                push r12
                push r8
                push r9

                mov r8, rdi                             ;r8 - ptr to list (list_name)
                mov rbx, QWORD [r8]                     ;rbx = list_name->elem
                add rbx, sizeof_elem

                mov r9, rsi                             ;r9 - ptr to char* (word)
                mov rcx, QWORD [r8 + sizeof_ptr]        ;rcx = list_name->head
                mov r12, QWORD [r8 + sizeof_ptr + 4 * sizeof_size_t] ;r12 = list_name->free

next:           test rcx, rcx
                jz not_found

                cmp rcx, r12            ;rcx(i_pos) != list_name->free;
                je not_found

                mov rdi, QWORD [rbx]    ;rdi = list_name->elem->data
                mov rsi, r9             ;rsi = ptr to char* (word)
                xor al, al
                call Strcmp
                test al, al
                jz found

                add rbx, sizeof_elem
                inc rcx
                jmp next

found:          mov rax, rcx
                jmp finish

not_found:      xor rax, rax

finish:         pop r9
                pop r8
                pop r12
                pop rcx
                pop rbx
                ret

;---------------------------------------------------------------
;Strcmp == strcmp
;
;Entry:     rdi - the first  str
;           rsi - the second str
;
;Destroy:   rsi rdi dl al
;
;Return:    al - res (== 0 --> 1str == 2str)
;                      > 0 --> 1str >  1str)
;                      < 0 --> 1str <  2str)
;-------------------------------------------------------------

Strcmp:         mov dl, [rdi]       ;check end of 1str
                test dl, dl
                jz finish_cmp

                mov dl, [rsi]       ;check end of 2str
                test dl, dl
                jz finish_cmp

                mov al, [rdi]       ;cmp(1str[i], 2str[i])
                mov dl, [rsi]
                cmp al, dl
                jne finish_cmp

                inc rdi             ;i++
                inc rsi
                jmp Strcmp

finish_cmp:     mov al, [rdi]       ;1str[i] - 2str[i]
                sub al, [rsi]
                ret