


;-------------------------------------------------
COMMENTS$

Find symbol in memory

Expects:	AL - symbol
		ES: DI	- addr of memory
		CX - size of memory

DSTR:		CX DI


Returns:	ES: DI - addr of symbol or CX == 0 if not found

$
;-------------------------------------------------

Memchar		proc
		
		repne scasw

		ret
		endp
