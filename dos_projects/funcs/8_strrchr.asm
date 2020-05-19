
local @@


;-------------------------------------------
Comments $

Find last sym in str

Expects:	AX - sym
		ES: DI - addr of str

Dstr:		CX

Returns:	ES: DI - addr of last sym in str or if not found CX == 0

;--------------------------------------------

Strrchr		proc

		xor cx, cx

		call strlen
		add di, cx
		
@@Next:		cmp ax, es: [di]
		je @@Find
		dec di
		loop @@Next


@@Find:		ret
		endp
