;; File: strrev.asm
;; Class: CMSC313
;; Name: Dong Sun
;; Date: 11/10/2014
;; Email: dongsun1@umbc.edu



;  Implements a C function with the prototype:
;    void strrev(char *str) 
;	


	SECTION .text			
	global strrev			


strrev:						
	push ebp
	mov ebp, esp

	push ebx				;save all the register
	push esi
	push edi
	push ecx
	push edx

	mov eax, 0				;initialize all register to 0
	mov ebx, 0
	mov ecx, 0
	mov edx, 0
	mov edi, 0
	mov esi, [ebp + 8]

getNull:					;check that string is null or not
	cmp esi, 0h
	je exit				;jump if the string is null

getSize:					;count down the size of string
	mov al, [esi+ecx]
	inc ecx
	cmp al, 0h				;check that string  is null
	je getNull			;jump if the string reach end
	jmp getSize

ifempty:					;check that string is empty or not
	dec ecx
	cmp ecx, 0
	je exit


init:
	mov ebx, 0 				;reinitialze ebx register  ;count

Loop:
	mov al, [esi+ebx]			;get nth element from string and store it to eax
	push eax				;push it to stack
	inc ebx
	cmp ecx, ebx 				;compare ebx with string length
	je Pop_init  				;if ebx reach size of string, move to forPop_init
	jmp Loop				;keep running for loop until ebx reach string length

Pop_init:
	mov ebx, 0 				;initialize
	mov edx, 0
Pop:

	pop edx				;pop out from stack
	mov dl, dl
	mov [esi +ebx], edx 			;place dl at string's front
	inc ebx
	cmp ecx, ebx
	je exit
	jmp Pop


exit:
	pop edx				;restore 
	pop ecx
	pop edi
	pop esi
	pop ebx
	mov esp, ebp
	pop ebp

	ret