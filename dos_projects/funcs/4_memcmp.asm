
local @@



;----------------------------------------------------------------
Comments $

Compare two parts of mem

Expects:	ES: DI - 1st mem
		DS: SI - 2nd mem
		CX - amount sym for comparing 

Destr:		CX

Returns:	CX - res ( 1: 1st > 2nd
			  -1: 1st < 2nd
		           0: 1st = 2nd)

		ES: DI - finish addr 1st mem
		DS: SI - finish addr 2nd mem
			
;--------------------------------------------------------

Memcmp		proc
		push ax

		xor ax, ax		

@@Next:		lodsw
		scasw
		
		ja @@More
		jb @@Less
		
		loop @@Next
		ret
		
@@More:		pop ax
		move cx, 1
		ret

@@Less:		pop ax
		move cx, -1
		ret
		
		endp
