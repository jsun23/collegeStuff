; Project: Project 1
; Class: CMSC313
; Name: Dong Sun
; Date: 9/22/2014
; Email: dongsun1@umbc.edu

;; ISBN Validation
;; Validate the 10-digit ISBN number
;; sample like:   10*a0 + 9*a1 + 8*a2 + 7*a3 + 6*a4 + 5*a5 + 4*a6 + 3*a7 + 2*a8 + a9
;; using loop and push to access the values

	SECTION data      ;Data section
msg1: 	db "Enter 10 digit ISBN: ", 10  ; Create a string to ask user to enter a 10 digit number
len1:	equ $-msg1
	
msg2:	db "This is a valid ISBN number.", 10 
len2:	equ $-msg2

msg3:	db "This is not a valid ISBN number.", 10
len3:	equ $-msg3

	SECTION .bss
ISBN equ 10			; set up the uninitialized valiable
ISBNBuffer: resb ISBN	
	SECTION .text
	
	global main
main:
	nop
	push bx	
	push cx
	push dx
	push si
;; reference from text book, xlat1.asm
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1	; pass enter aking of the message
	mov edx, len1	; pass the length of the message
	int 80h
	mov eax, 3
	mov ebx, 0
	mov ecx, ISBNBuffer	; pass the input into the buffer
	mov edx, ISBN		; pass the length
	int 80h
	cmp eax, 0
	je done
;; reference from online http://assembly.happycodings.com/code17.html

	
	mov bx,[ISBNBuffer] 	;read the input into bx
	mov dx, 10		;number of digits 
	xor ax, ax		;clear
	cld
loop1: 
	mov si,bx	
	mov cx,dx
loop2:
	and al, 0fh	 ;convert from ASCII
	add ah, al	

	loop loop2	 ;loop the loop2 to do all the digits
	inc bx		 ;advance the digit pointer	
	dec dx 		 ;decrease digit count	
	jnz loop1	 ;keep looping if count is not zero	
	mov al,ah  	 ;move sum to al	
	xor ah,ah	 ;clear
	mov cl,11	 ;pass 11 to cl	
	div cl		 ;ah = sum mod 11
	mov al,ah	 
	xor ah,ah
	or al,30h
	cmp al,30h
	jnz message2 	 ;jump to message2 if not zero
	
	jz message1 	 ;jump to message1 if zero
	
	
	

;; if the ISBN is valide, print the massage
message1:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, len2
	int 80h
	jp done
;; if the ISBN is not valide, print the message
message2:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg3
	mov edx, len3
	int 80h 
	jp done
;; exit the program	
done:
	pop bx
	pop cx
	pop dx
	pop si
	mov eax, 0
	mov ebx, 1
	int 80h
	

	