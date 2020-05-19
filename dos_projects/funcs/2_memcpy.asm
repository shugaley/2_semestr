


;-----------------------------------------------
COMMENTS $

Copy one part of memory to other part (amount byte)

Expects:	ES: DI - addres of accepting memory
		DS: SI - addres of replicating memory
		CX - amount 

Destr:	CX DI SI



$
;-----------------------------------------------

MEMCPY:		proc
		
		rep movsb

		ret
		endp		
