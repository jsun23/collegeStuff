addi  $1  $0  12   # set initial speed
addi  $2  $0  20   # set initial rot cw
addi  $3  $0  -20  # set initial rot ccw
addi  $30 $0  1    # subtractor

spd   $1  0
addi  $9  0   0

# first scan
:scan1
addi  $9  0   0
scn   $9 
bgtz  $9  fire1

:scan_cc1
addi  $6  $0  5    # re-init scan lim reg
rot   $3  0	       # set rot to c-clockwise

# counterclockwise spin
:scan_cc
rot   $3  0
subu  $6  $6  $30
scn   $9
rot   $0  0
bgtz  $9  fire1
blez  $6  scan_cw1 # after 5 scans, change rot dir
blez  $9  scan_cc  

:scan_cw1
addi  $6  $0  5    # re-init scan lim reg
rot   $2  0	       # set rot to clockwise

# clockwise spin
:scan_cw
rot   $2  0
subu  $6  $6  $30
scn   $9
rot   $0  0
bgtz  $9  fire1
blez  $6  scan_cc1 # after 5 scans, change rot dir
blez  $9  scan_cw

# fire for 2(?) cycles
:fire1
rot   $0  0
fir   $9  0
fir   $9  0

j     scan1
