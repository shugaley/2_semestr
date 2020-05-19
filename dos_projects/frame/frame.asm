locals @@

.186
.model tiny
.code
org 100h

include S:\PROJECTS\MACRO\macro.asm

xl equ 25
xr equ 55
yu equ 3
yd equ 15

space      equ  0e20h
space_back equ 0ee20h
hor_line   equ  0ecdh
ver_line   equ  0ebah
lu_corner  equ  0ec9h
ru_corner  equ  0ebbh
ld_corner  equ  0ec8h
rd_corner  equ  0ebch

video_seg equ 0b800h

hor_long equ 80
ver_lond equ 25

;----------------------------------------------------------

Start:		mov di, ((yu - 1) * hor_long + xl) * 2    ;HOR_LINE
		mov ax, hor_line 
		mov cx, xr - xl
		call Draw_HorLine

		mov di, ((yd - 1) * hor_long + xl) * 2
		mov ax, hor_line
		mov cx, xr - xl
		call Draw_HorLine

		mov si, yu                                 ;INSIDE
Draw_inside:	mov ax, hor_long
		mul si
		add ax, xl
		mov bx, 02h
		mul bx
		xor bx, bx
		mov di, ax

		mov cx, xr - xl
		mov ax, space
		call Draw_HorLine
		inc si
		cmp si, yd - 1
		jne draw_inside

		mov di, ((yu - 1) * hor_long + xl) * 2   ;VER_LINE
		mov ax, ver_line
		mov cx, yd - yu + 1
		call Draw_VerLine

		mov di, ((yu - 1) * hor_long + xr) * 2
		mov ax, ver_line
		mov cx, yd - yu + 1
		call Draw_VerLine

		
		mov di, ((yu - 1) * hor_long + xl) * 2    ;CORNERS
		mov ax, lu_corner
		mov cx, 1
		call Draw_HorLine

		mov di, ((yu - 1) * hor_long + xr) * 2
		mov ax, ru_corner
		mov cx, 1
		call Draw_HorLine

		mov di, ((yd - 1) * hor_long + xl) * 2
		mov ax, ld_corner
		mov cx, 1
		call Draw_HorLine

		mov di, ((yd - 1) * hor_long + xr) * 2
		mov ax, rd_corner
		mov cx, 1
		call Draw_HorLine

		
		mov di, (yd * hor_long + xl + 1) * 2       ;BACK
		mov ax, space_back
		mov cx, xr - xl + 1
		call Draw_HorLine

		mov di, (yu * hor_long + xr + 1) * 2
		mov ax, space_back
		mov cx, yd - yu + 1
		call Draw_VerLine

		.exitt 1


;-----------------------------------------------------------
Comment $

Draw a horizontal line

Expects:	AH - color attr
		AL - symbol to draw
		DI - addr to start line
		CX - amount of symbols

Destr:		DI CX ES

$
;-----------------------------------------------------------

Draw_HorLine	proc
		push video_seg
		pop es

		cld 
		rep stosw
		
		ret 
		endp

		
;----------------------------------------------------------------
Comment $

Draw a vertical line

Expects:	AH - color attr
		AL - symbol to draw
		DI - addr to start line
		CX - amount of symbols

Destr:		CX DI ES
		
$
;-----------------------------------------------------------------

Draw_VerLine	proc
		push video_seg
		pop es
		
@@Next:		cld
		stosw
		add di, (hor_long - 1) * 2
		loop @@Next
		
		ret
		endp 		
		
end		Start
  
