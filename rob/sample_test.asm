       addi  $3  $0  40
       addi  $4  $0  80
       divu  $4  $4  $3

:move  addi  $5  $0  3
       addi  $7  $0  76
       rot   $0  1
       spd   $1  3
       
       addi  $20 $10 1000
       addi  $29 $29 1
       
:shot  scn   $1
       fir   $1  0
       addi  $1  $3  3
       addi  $2  $2  1
       
:two   rot   $7  4  
       fir   $7  1
       addi  $7  $7  -2
       blez  $7  two
       
       addi  $5  $5  -1       
       bgtz  $5  shot
       
:zzz 
       addiu $17 $0  1
       xor   $12 $23 $17
       rot   $12 1
       fir   $17 0
       bne   $12 $0  zzz
       
:extr  lw    $3  $1  data
       sub   $3  $3  1
       mult  $10 $3  $4
       sub   $4  $0  2
       
       fir   $10 0
       bgtz  $10 extr
       
:three 
       fir   $20 $0
       bne   $20 $29 three 
       
       j     move

:data 
       int   0   1   2   3   4
       int   5   6   7   8   9
       int   10  11  12  13  14
       int   20  40  90  99  298
