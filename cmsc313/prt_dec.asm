;; Project: Project3
;; Class: CMSC313
;; Name: Dong Sun
;; Date: 10/6/2014

; Print Decimal Subroutine

	SECTION data

	SECTION .bss
	SECTION .text
	
	global prt_dec

prt_dec:
	push eax
	push ebx
	push ecx
	push edx

	mov edi,eax
	mov ebx,10
	div ebx
	cmp edx, 0fh
	je hex_dec
	mov eax, edi

	pop edx
	pop ecx
	pop ebx
	pop eax
	ret
       
hex_dec:
	mov ecx,0
	mov ebx,10
	jp loop
	
loop:
	mov edx,0
	div ebx
	add dl,30h
	inc ecx
	cmp eax,9
	jg loop
	add al,30h
	mov [si], al
loop1:
	inc esi
	mov [esi], al
	loop loop1
	ret
	
	
	
