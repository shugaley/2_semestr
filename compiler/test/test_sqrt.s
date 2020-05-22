
section .text
global _start

_start:     ;call cmpr
            jge u
            jg u
            jl u
            jle u

            push -600
            push -600
            finit
            fild dword [rsp + 8]
            fimul dword [rsp]
            push 100
            fidiv dword [rsp]
            fist dword [rsp]

            movsx rax, dword [rsp]
            add rsp, 24
            push rax

div:
            push 0
            push 1
            xor rax, rax
            finit
            fild qword [rsp - 8]
            fcom qword [rsp]
            fstsw ax
            test rax, 0x4500

            jz next
            NOP
            NOP
            NOP



next:       nop
            ;fist qword [rsp]



cmpr:       push 0
            push 0
            xor rax, rax
            finit
            fild dword [rsp + 8]
            fild dword [rsp]
            fcom
            fstsw ax
            add rsp, 16
            sahf
            cmp rax, 0x7000
            jb else
            mov rcx, 1
else:       mov rcx, 2


        NOP
        NOP

        NOP

        mov rbx, 0x7000


        NOP
        NOP

       NOP
       NOP
       nop
       NOP
       NOP

      NOP
      NOP
      nop
      NOP
      NOP

     NOP
     NOP
     nop
     NOP
     NOP

    NOP
    NOP
    nop
    NOP
    NOP

   NOP
   NOP
   nop
   NOP
   NOP

  NOP
  NOP
  nop
  NOP
  NOP

 NOP
 NOP
 nop
 NOP
 NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
NOP
NOP

NOP
NOP
nop
 u:
