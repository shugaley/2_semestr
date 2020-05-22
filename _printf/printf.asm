section .text

size_cell equ 8   ;sizeof one cell (of stack)
size_mem  equ 1   ;one byte

bin_mask  equ 0b00000001

global _printfx
;--------------------------------------------------------
;
;--------------------------------------------------------

_printfx:       pop r14

                push r9
                push r8
                push rcx
                push rdx
                push rsi
                push rdi

                push rbp          ;saving rbp
                xor rbp, rbp

                push rax          ;saving rax
                mov rax, size_cell
                mov rbp, 2        ;2 = rax + rbp
                mul rbp
                add rax, rsp
                mov rbp, rax      ;rbp = ptr to prt to str in stack
                pop rax

                push rdi          ;saving reg
                push rsi
                push rax
                push rcx
                push rdx
                push r10
                push r13

                push r8           ;saving r8
                mov r8, rsp

                call printfx

                mov rsp, r8
                pop r8

                pop r13
                pop r10
                pop rdx
                pop rcx
                pop rax
                pop rsi
                pop rdi
                ;pop rbp?????????????????
;??????????

                pop rbp
                add rsp, size_cell * 6     ;size_cell * 6

;??????????
                push r14

                ret

section .text

global printfx
;-----------------------------------------------
;
;printfx == printf("str", op1, op2, ....)
;
;Entry:        ptr to str, op in stack
;              rbp - ptr to ptr to str in stack
;              rdi - ptr to str ???????????????
;              (rbp + size_cell ptr to op1 in stack, ...)
;
;               r8 == rsp (dont use!!!!!)
;               r14 - system (dont use!!!!!!)
;
;Destroy:      rdi rsi rax rcx rdx r10 r13
;
;Return:
;------------------------------------------------

printfx:        mov rsi, rdi   ;rsi = copy of ptr to str

repeat:         add rbp, size_cell  ;rbp = ptr to now op in stack
                mov rdi, rsi

                xor rax, rax   ;finding %
                mov rax, '%'
                push rbx
                call Strchr    ;rdi = [%]
                pop rbx

                call Print_str   ;print from rsi to rdi
                add rsi, rdx     ;rsi = old rdi (rdi before Print_str)

                xor rax, rax     ;checking end of str
                mov al, [rsi]
                cmp al, 0
                je exitt

                inc rsi         ;rsi = [%]++
                xor rax, rax
                mov al, [rsi]

                cmp al, '%'     ;Switch print %
                je p_perc

                mov r10, [rbp]   ; r10 = op
                mov r13, buf_size - 1 ;

                inc rsi
                push rsi            ;saving rsi, rdi
                push rdi

                cmp al, 'c'
                je p_chr

                cmp al, 's'
                je p_str

                xor rcx, rcx

                cmp al, 'b'
                je p_bin

                cmp al, 'd'
                je p_dec

                cmp al, 'o'
                je p_oct

                cmp al, 'x'
                je p_hex



exitt:          ;...............
                ret

p_perc:         mov rdi, rsi
                inc rdi
                call Print_str
                inc rsi
                sub rbp, size_cell
                jmp repeat


p_chr:          xor rax, rax
                mov rax, r10
                mov [buf + r13], al

                mov rsi, r13
                mov rdi, rsi
                add rdi, size_mem
                call Print_str

                pop rdi
                pop rsi
                jmp repeat

p_str:          mov rsi, [rbp]
                mov rdi, 0
                call Print_str

                pop rdi
                pop rsi
                jmp repeat

                NOP
                NOP
                NOP

p_bin:          xor rax, rax
                mov rax, r10
                shr rax, cl

                cmp rax, 0
                je p_end

                and al, bin_mask
                add al, '0'

                mov [buf + r13], al

                dec r13
                inc cl

                cmp cl, 64
                jne p_bin

                NOP
                NOP
                NOP

p_dec:          xor rax, rax
                mov rax, r10
                mov r10, 10
                jmp p_d_o_h_rep

p_oct:          xor rax, rax
                mov rax, r10
                mov r10, 8
                jmp p_d_o_h_rep

p_oct_sign:     dec r13
                mov dl, 'o'
                mov [buf + r13], dl

                dec r13
                mov dl, '0'
                mov [buf + r13], dl
                jmp p_end_back

p_hex:          xor rax, rax
                mov rax, r10
                mov r10, 16
                jmp p_d_o_h_rep

p_hex_sign:     dec r13
                mov dl, 'x'
                mov [buf + r13], dl

                dec r13
                mov dl, '0'
                mov [buf + r13], dl
                jmp p_end_back


p_d_o_h_rep:    xor rdx, rdx
                div r10

                cmp rdx, 9
                jbe p_d_o_next

                sub rdx, 10
                add rdx, 'A'           ;ASCII number
                jmp p_d_o_h_next

p_d_o_next:     add rdx, '0'           ;ASCII number

p_d_o_h_next:   mov [buf + r13], dl    ;ASCII to buffer

                cmp rax, 0
                je p_end

                cmp r13, 0
                je p_end

                dec r13
                jmp p_d_o_h_rep


p_end:          cmp r10, 8
                je p_oct_sign

                cmp r10, 16
                je p_hex_sign

p_end_back:     mov rsi, buf
                add rsi, r13
                mov rdi, buf + buf_size
                call Print_str

                pop rdi
                pop rsi
                jmp repeat



section .bss

buf:        resb 66
buf_size:   equ $ - buf





section .text

global Print_str
;----------------------------------------------------
;
;Print_str - print str from 1st ptr to 2nd (or to the end it 2nd == 0)
;
;Entry:        rsi - ptr to str
;              rdi - ptr to the end of printed part of str (or == 0 if print to the end)
;
;Destroy:      rax rdi
;
;Return:       if rdi was 0 rdi = the end of str
;              rdx = rdi - rsi
;---------------------------------------------------------------

Print_str:      cmp rdi, 0
                jne not_to_end

                xor rax, rax
                mov rax, 0
                push rbx
                mov rdi, rsi
                call Strchr     ;rdi = the end of str
                pop rbx

not_to_end:     mov rax, 0x01
                mov rdx, rdi
                mov rdi, 1
                sub rdx, rsi
                syscall

                ret


section .text

global Strchr
;------------------------------------------------
;
; strchr - find 1st char in str
;
; Expects:	rax - wanted char
;		        rdi - ptr to str
;
;
; Dstr:		  rbx
;
; Returns:	rdi - ptr to 1st char in str OR rdi == 0 if not found
;--------------------------------------------------

Strchr:

rep_strchr:   xor rbx, rbx
              mov bl, [rdi]

              cmp bl, al
              je found

              cmp bl, 0
              je not_found

              inc rdi
              jmp rep_strchr

found:        ret

not_found:    xor rdi, rdi
              ret
