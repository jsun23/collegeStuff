;;Project: Project 4
;;Class: CMSC 313
;;Name: Dong Sun
;;Email: dongsun1@umbc.edu
;;Date: 10/13/2014


%define TITLE_OFFSET 0
%define AUTHOR_OFFSET 48
%define SUBJECT_OFFSET 96
%define YEAR_OFFSET 116
%define NEXT_OFFSET 120


	SECTION .data
Message db "Fantasy", 10
Meglen equ $Message

	SECTION .bss
	SECTION .text

	extern library	
	global _start



ReaTitle:
	push edi
	push esi
	push ecx
	mov esi,[library]
	lea edi,[esi*8+TITLE_OFFSET]
	pop ecx
	pop edi
	pop esi
	ret

ReaAuthor:
	push edi
	push esi
	push ecx
	mov esi,[library]
	lea edi,[esi*8+AUTHOR_OFFSET]
	pop ecx
	pop esi
	pop edi
	ret
ReaSubject:
	pushad
	mov esi,[library]
	lea edi,[esi*8+SUBJECT_OFFSET]
	popad
	ret
ReaYear:
	push edi
	push esi
	push ecx
	mov esi,[library]
	lea edi,[esi*8+YEAR_OFFSET]
	pop ecx
	pop esi
	pop edi
	ret


start:
	nop
Read:
	mov eax,3
	mov ebx,0
	mov ecx,0
loop1:
	call ReaTitle
	call ReaAuthor
	call ReaYear
	call ReaSubject
	cmp edi,Message
	je print
	cmp eax,0
	jne ReaNext
	je done
	inc ecx
	loop loop1
	
	
ReaNext:
	push esi
	push ecx
	mov esi,[library]
	mov esi,[esi+NEXT_OFFSET]
	pop ecx
	pop esi
	ret
	
print:
	mov eax,4
	mov ebx,1
	mov ecx,edi
	mov edx,esi
	int 80h
	
done:
	mov eax,1
	mov ebx,0
	int 80h