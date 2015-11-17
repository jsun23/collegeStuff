;; Project: Project2
;; Class: CMSC 313
;; Name: Dong Sun
;; Date: 9/29/2014
;; Email: dongsun1@umbc.edu

;; An Error-Correcting Code
;; 



	SECTION data
p4: db 100
p3: db 010
p2: db 001
p1: db 000


	SECTION .bss
		Buff resb 1
	SECTION .text


	global main
main:
	nop
	push eax
	push ebx
	push ecx
	push edx
write:
	mov eax,4
	mov ebx,1
	mov bl, [Buff]
	mov edx, 1
	int 80h
	jmp Test
Test:
	
	mov ebx,eax
	shr eax,16
	xor ax,bx
	xor al,ah
	mov ebx,0
	cmp bl, 0
	je done
	jne Read
Read:
	shr bl,3
	jmp test
test:
	mov al,bl
	mov cl, 3
	div cl
	mov al, ah
	xor al,ah
	cmp al, 0
	je test1
	jnz test2
	cmp al,3
	je test3
	jmp done
	
test1:
	mov bl, [Buff]
	and bl,1
	cmp bl,1
	je test
	cmp byte[Buff],p4
	jne corr
	

test2:
	mov bl, [Buff]
	and bl,1
	cmp bl,1
	je test
	cmp byte[Buff],p3
	jne corr
	
test3:
	mov bl,[Buff]
	and bl,1
	cmp bl,1
	je test
	cmp byte[Buff],p2
	jne corr

corr:
	and bl,1
	mov al,bl
		

	pop eax
	pop ebx
	pop ecx
	pop edx	
	ret
	
done:
	mov eax,1
	mov ebx,0
	int 80h	