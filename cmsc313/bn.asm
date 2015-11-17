
;/***************************************************************************
;
;   Name:
;       isbncheck
;
;   Purpose:
;       Calculates the check digit for a ten digit ISBN, converts that
;       digit to its ASCII representation and returns that answer.
;
;   Algorithm:
;       An ISBN consists of nine digits plus a validation digit.
;       Number the digits from left to right as d1, d2, ... d9, with
;       d10 being the validation digit.  The calculation is then
;
;       d10 = (1(d1) + 2(d2) + 3(d3) + ... + i(di) + ... + 9(d9))%11
;
;       or the weighted sum of each digit mod eleven.
;
;       In our assembly language implementation, we simulate the
;       multiplications by looping through and summing as in the
;       following psuedocode:
;
;       sum = 0
;       for i=1 to 9
;       {
;           for j=i to 9
;           {
;               sum = sum + isbn[j]
;           }
;       }
;
;   Entry:
;
;      isbn = a nine digit ASCII string containing the ISBN
;             (with or without the check digit which is not used here)
;
;   Register usage within the routine:
;
;        AL = current ISBN digit
;        AH = sum of digits so far
;        BX = start pointer into ISBN for each outer loop
;        CX = digit counter (inner loop)
;        DX = start value for digit counter
;        SI = points to current ISBN digit
;
;   Exit:
;
;        AX = ASCII representation of calculated check digit
;
;   Trashed:
;       none
;
;***************************************************************************/
isbncheck proc C isbn:ptr byte
        push    bx
        push    cx
        push    dx
        push    si
        mov     bx,[isbn]               ;
        mov     dx,9                    ; number of digits in raw ISBN
        xor     ax,ax                   ; clear out our total
        cld                             ; count up
@@bigloop:                              ;
        mov     si,bx                   ; point to a digit in the ISBN
        mov     cx,dx                   ; get digit count in CX
@@AddEmUp:                              ;
        lodsb                           ; fetch digit into AL
        and     al,0fh                  ; convert from ASCII
        add     ah,al                   ; add it to our total in AH
        loop    @@AddEmUp               ; do all digits
        inc     bx                      ; and advance the digit pointer
        dec     dx                      ; now decrement digit count
        jnz     @@bigloop               ;   keep going if digits left
        mov     al,ah                   ; move sum into al
        xor     ah,ah                   ; clear out high half
        mov     cl,11                   ; we'll be doing a mod 11 operation
        div     cl                      ; ah = sum mod 11
        mov     al,ah                   ; move calculated check digit to AL
        xor     ah,ah                   ; clear out high half
        or      al,30h                  ; convert to ASCII digit
        cmp     al,3Ah                  ;
        jnz     NotTen                  ;
        mov     al,'X'                  ;
NotTen:                                 ;
        pop     si
        pop     dx
        pop     cx
        pop     bx
        ret                             ; return
isbncheck endp

        END
