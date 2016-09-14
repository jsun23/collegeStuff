:begin		spd     #2($1)			;set initial speed and rotation
			rot   	#20($2)			
:check		dscn    $1 				;distance scan for robots
			blez 	$1 #4			;goes to F1 if distance scan did not find robot
			fir     #5($1)			; fires at the robot if found and doesn't kill itself
			ascn	$2				; angle scans 
			beq		$2, $0, #1		;goes to F1 if the angle is 0
			add 	$2, $2, $2		; doubles the angle
			rot 	$2
			j 	:check				;F1
