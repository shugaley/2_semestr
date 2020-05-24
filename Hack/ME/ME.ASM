
locals @@

.186
.model tiny
.code
org 100h


;--------------------------------------------

Start:		mov dx, offset PromptMsg
		call PutS

		mov di, offset Password
		push di
		call GetS
		pop di

		call Check

		mov ax, 4c00h
		int 21h

;--------------------------------------------

PromptMsg 	  db  0dh, 0ah, 'Enter Admin password:  $'
CheckingMsg 	  db  0dh, 0ah, 'Checking the password: $'
CheckFailedMsg    db  0dh, 0ah, 'Fuck off Iskan!        $'
CheckRightsMsg    db  0dh, 0ah, 'Yoy are Pidar.         $'

AdminPassword     db 'GOD'
AdminPasswordLen  equ $ - AdminPassword 

;---------------------------------------------
Comment $

Check - check password and give admin rights or fuck you

Entry:	  	DI - ptr to password	

Dstr:	  	DX SI DI CX

Return:
$
;----------------------------------------------

Check		proc
		
		mov dx, offset CheckingMsg
		call PutS

		mov si, offset AdminPassword 
		mov cx, AdminPasswordLen
		call CmpPwd
				
		jcxz @@CheckFailed
		
		mov dx, offset CheckRightsMsg
		call PutS
		ret

@@CheckFailed:	mov dx, offset CheckFailedMsg
		call PutS
		ret
		
		endp

;---------------------------------------------
Comment $

CmpPwd - cmp AdmPwd and Pwd

Entry:		DI - pwd 
		SI - AdmPwd
		CX - len of AdmPwd

Dstr:		DI SI

Return:		CX - res (0 - false
			  1 - true)	
$
;--------------------------------------------

CmpPwd		proc

		cld
		repe cmpsb      ; while (cx-- && ds:[si++] == es:[di++]) 

		jne @@PwdFalse

		mov cx, 1
		ret

@@PwdFalse:	mov cx, 0
		ret
			
		endp
	
;---------------------------------------------
Comment $

PutS - print a string
 
Entry: DX - ptr to string to print
 
Destr: AH

$
;--------------------------------------------

PutS		proc
		mov ah, 09h
		int 21h
		ret
		endp



;--------------------------------------------
Comment $

GetS - Get a string
 
Entry:  DI - ptr to string
 
Destr:  AX

Return: DI - ptr to end of the string

$
;--------------------------------------------

GetS		proc

@@Next: 	mov ah, 01h
		int 21h

		cmp al, 0dh
		je @@End

		stosb         ; { es:[di] = al; inc di; }
	        jmp @@Next

@@End:	        ret
		endp


Password: 	db 10 dup ('$')

end             Start
