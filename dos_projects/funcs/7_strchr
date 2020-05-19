
local @@


;------------------------------------------------
Comments $

Find 1st sym in str
	
Expects:	AX - sym
		ES: DI - addr of str
		

Dstr:		CX

Returns:	ES: DI - addr of symbol or if not found CX == 0
;--------------------------------------------------

Strchr		proc
		
		call strlen
		repne scasw	

		ret
