
.model tiny
.code
org 100h

;----------------------------------------------------------------------

.exitt		macro ret
	ifnb <ret>
		mov ax, 4c00h or (ret and 0FFh)
	else
		mov ah, 4ch
	endif
		
		int 21h
		nop
		endm
