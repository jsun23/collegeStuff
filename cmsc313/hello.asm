;
; Linux style "fast call". Assemble using NASM
;
        SECTION .data                   ; Data section

msg:    db "The more you ate, the big you would be!", 10           ; The string to print.
len:    equ $-msg

	SECTION .bss
        SECTION .text
				; Code section.
	global main
main:	
	nop                             ; Entry point.
        mov     edx, len                ; Arg 3: length of string.
        mov     ecx, msg                ; Arg 2: pointer to string.
        mov     ebx, 1                  ; Arg 1: file descriptor.
        mov     eax, 4                  ; Write.
        int     080H

        mov     ebx, 0                  ; exit code, 0=normal
        mov     eax, 1                  ; Exit.
        int     080H                    ; Call kernel.