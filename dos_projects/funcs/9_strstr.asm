
local @@



;-----------------------------------------------
Comments $

Find 1st 1st str in 2nd

Expects:	DS: SI - 1st str
		ES: DI - 2nd str

Dstr:		CX 

Return:		ES: DI - addr of 1st in 2nd or of not found CX == 0

$
;----------------------------------------------------

Strstr		proc
		push ax bx

		xor ax, ax
		xor cx, cx

		push es di		
		mov es, ds
		mov di, si
		strlen		
		mov bx, cx		; bx - len of 1st
		pop di es
		strlen			; cx - len of 2nd

@@Next:		lodsw			
		push cx
		strchr			; find 1st sym of 1st str in 2nd str		
		cmp cx, 0
		je @@NotFound
		pop cx		
		
		push cx
		push si di
		mov cx, bx
		memcmp			; cmp str
		pop di si
		cmp cx, 0		
		je @@Found
		pop cx
		
		inc si
		inc di
		loop @@Next 
		

@@NotFound:	pop bx ax
		ret

@@Found:	pop cx
		pop bx ax
		ret
		endp
