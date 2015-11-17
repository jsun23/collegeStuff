;; File: strrepl.asm
;; Class: CMSC313
;; Name: Dong Sun
;; Date: 11/10/2014
;; Email: dongsun1@umbc.edu

; Implements a C function with the prototype:
;
;   int strrepl(char *str, int c, int (* isinsubset) (int c) ) ;
;
; 
; Result: chars in string are replaced with the replacement character and string is returned.

    SECTION .text
    global  strrepl



strrepl:
    push    ebp         		; set up stack 
    push    esi         		; save registers
    push    ebx
    mov ebp, esp
   
    xor eax, eax
    mov ecx, [ebp + 8]      	;load string into ecx
    cmp ecx, 0
    je   end         		;jump if eax is zero
    mov al, [ebp + 12]      	;replace esi
    mov edx, [ebp + 16]     	;move function pointer into edx
    xor bl, bl

firstLoop:
    xor eax, eax
    mov edi, [ecx]
    cmp edi, 0
    je  end
    mov edi, ecx        		; save array

    movzx   eax, byte [ecx]     	;load single byte into eax  
    push    eax         		
    mov edx, [ebp + 16]         
    call    edx         		

    mov ecx, edi        		; restore array
    cmp eax, 0
    jne secondLoop  
    add esp, 4          		
    add ecx, 1
    jmp firstLoop

secondLoop:
    mov eax, [ebp+12]
    mov [ecx], al
    inc bl
    mov edx, [ebp+16]
    add esp, 4
    add ecx, 1
    jmp     firstLoop

end:
    xor eax, eax
    mov al, bl
    pop ebx         			; restore registers
    pop esi
    mov esp, ebp        		; take down stack
    pop ebp
    ret