
.model tiny
.code
org 100h

;---------------------------------------
Comments $

Fill some amount of memory in symbols

Expects:	AL -  symbol
		ES: DI - addr of start
		CX - amount

Destr:		DI CX
$
;--------------------------------------------


Memset		proc
		rep stosb
		
		ret
		endp
