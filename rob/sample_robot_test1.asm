# speed stored in $1
# rotation stored in $2
# result of scan stored in $3

addi  $1  $0  3
addi  $2  $0  25
addi  $3  $0  0
addi  $4  $0  0

addi  $6  $0  -4

addi  $9  $0  0   # amount to rotate by
addi  $10 $0  180 # variable turn speed

:set_speed
spd   $1  1
rot   $2  0

:scan1
scn   $3          # scan and shoot always
fir   $3  1

subi  $10  $10 12 # turn around by $10 - 12 degrees (if needed)

:check            # check if wall
sub   $7  $3  $1  # use speed step
bgtz  $7  scan1   # no object nearby, scan and shoot again

:scan             # if wall is close
spd   $1  -1      # slow down and 
rot   $10 0       # turn around
j scan1
