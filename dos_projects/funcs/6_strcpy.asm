
local @@


;------------------------------------------
Comments $

Copy 1st str in 2nd

Entry:		DS: SI - 1st str
		ES: DI - 2nd str

Returns:	DS: SI - end of 1st str
		ES: DI - end of copy in 2nd str

$
;--------------------------------------------

Strcpy		proc
		push ax cx

		xor ax, ax
		xor cx, cx
		
		push es di
		mov es, di
		mov di, si
		call strlen
		pop di es

		rep movsw

		pop cx ax
		endp
