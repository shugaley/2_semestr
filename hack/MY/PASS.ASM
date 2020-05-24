
.model tiny
.code
org 100h

Start:		mov ah, 02h
		mov cx, 64980d
		mov dl, 90h

Next:		int 21h
		loop Next

		mov dl, 53h
		int 21h
		mov dl, 01h
		int 21h
		mov dl, 0dh
		int 21h

		mov ax, 4c00h
		int 21h

end 		Start