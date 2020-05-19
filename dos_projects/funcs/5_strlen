
local @@



;-------------------------------------------------
Comments $

Count size of str

Expects:	ES: DI - addr of str

Destr:		DI

Reterns:	ES: DI - addr of end of str
		CX - len


$
;------------------------------------------------

Strlen		proc
		push ax
		xor ax, ax
		xor cx, cx
		
		mov cx, di
		mov ah, '$'
		repne scasb
		
		mov ax, di
		sub di, cx + 1
		add cx, di
		mov di, ax

		pop ax
		endp
