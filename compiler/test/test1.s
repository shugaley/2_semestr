
section .test
global _start

_start:     NOP
            NOP
            NOP
next:       ret
            nop
            nop
            nop
            call next
            NOP
            NOP
