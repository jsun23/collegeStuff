# will test the following:
# test lw with another instruction after
# test scn with another instruction after
# do for all possible instructions
# check with 2 instructions after

# = works fine

# lw    $3  $1  1
addi   $4  $3  5
addi   $2  $4  5

# lw    $3  $1  1
# addiu $4  $3  3

# lw    $3  $1  1
# andi  $4  $3  3

# lw    $3  $1  1
# ori   $4  $3  3

# lw    $3  $1  data
# xori  $4  $3  3

# lw    $3  $1  data
# lui   $3  1

# lw    $3  $1  1
# sw    $5  $3  3

# lw    $3  $1  1
# lw    $4  $3  1

# lw    $3  $1  1
# mult  $4  $3  $5

# lw    $3  $1  1
# multu $4  $3  $3

# lw    $3  $1  1
# div   $4  $3  $5

# lw    $3  $1  1
# divu  $4  $3  $3

# lw    $3  $1  1
# add   $4  $3  $5

# lw    $3  $1  1
# addu  $4  $3  $3

# lw    $3  $1  1
# sub   $4  $3  $5

# lw    $3  $1  1
# subu  $4  $3  $3

# lw    $3  $1  1
# and   $4  $3  $3

# lw    $3  $1  1
# or    $4  $3  $3

# lw    $3  $1  data
# xor   $4  $3  $3

# lw    $3  $1  data
# nor   $4  $3  $5

# lw    $3  $1  1			
# scn   $3

# lw    $3  $1  data
# spd   $3  5

# lw    $3  $1  data
# rot   $3  2

# lw    $3  $1  data
# fir   $3  1

# scn   $3
# addi  $3  $4  5

# scn   $3
# addiu $4  $3  3

# scn   $3
# andi  $4  $3  3

# scn   $3
# ori   $4  $3  3

# scn   $3
# xori  $4  $3  3

# scn   $3
# lui   $3  1

# scn   $3
# sw    $5  $3  3

# scn   $3
# lw    $4  $3  1

# scn   $3
# mult  $4  $3  $5

# scn   $3
# multu $4  $3  $3

# scn   $3
# div   $4  $3  $5

# scn   $3
# divu  $4  $3  $3

# scn   $3
# add   $4  $3  $5

# scn   $3
# addu  $4  $3  $3

# scn   $3
# sub   $4  $3  $5

# scn   $3
# subu  $4  $3  $3

# scn   $3
# and   $4  $3  $3

# scn   $3
# or    $4  $3  $3

# scn   $3
# xor   $4  $3  $3

# scn   $3
# nor   $4  $3  $5

:data
int     22 21 12 13 34
