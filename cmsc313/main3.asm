; File: main.asm
;
; main program that exercises the prt_dec subroutine
;

%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4


        SECTION .data                   ; initialized data section

lf:   	db  10            		; just a linefeed 

msg1:	db " plus "	
len1 equ $ - msg1

msg2: 	db " minus "
len2 equ $ - msg2

msg3:	db " equals "
len3 equ $ - msg3

        SECTION .text                   ; Code section.
        global  _start                  ; let loader see entry point
	extern	prt_dec

_start: 
	mov	ebx, 17
	mov	edx, 214123
	mov	edi, 2223187809
	mov	ebp, 1555544444 


	mov	eax, dword 0x0
	call	prt_dec
	call	prt_lf

	mov	eax, dword 0xFFFFFFFF
	call	prt_dec
	call	prt_lf

	mov	eax, 3413151
	call	prt_dec
	call	prt_lf

	mov	eax, ebx
	call	prt_dec
	call	prt_lf

	mov	eax, edx
	call	prt_dec
	call	prt_lf

	mov	eax, edi
	call	prt_dec
	call	prt_lf

	mov	eax, ebp
	call	prt_dec
	call	prt_lf

	mov	eax, 2
	call	prt_dec

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg1
        mov     edx, len1
        int     080h
	
	mov	eax, 3
	call	prt_dec

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg3
        mov     edx, len3
        int     080h

	mov	eax, 5
	call	prt_dec
	call	prt_lf

	mov	eax, 7
	call	prt_dec

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg1
        mov     edx, len1
        int     080h
	
	mov	eax, 4
	call	prt_dec

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg3
        mov     edx, len3
        int     080h

	mov	eax, 3
	call	prt_dec
	call	prt_lf


        ; final exit
        ;
exit:   mov     EAX, SYSCALL_EXIT       ; exit function
        mov     EBX, 0                  ; exit code, 0=normal
        int     080h                    ; ask kernel to take over



	; A subroutine to print a LF, all registers are preserved
prt_lf:
	push	eax
	push	ebx
	push	ecx
	push	edx

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, lf
        mov     edx, 1			; LF is a single character
        int     080h

	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret

