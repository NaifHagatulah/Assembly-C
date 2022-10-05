  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  hexasc:
	li	$t3, 0x0000000F		#bitmask to only use 4 least significant bits
	li	$t0, 0x30	

	and	$t1, $a0, $t3		#apply bitmask. Could modify $a0 directly but not sure if that's allowed. $t1 is our "fixed" argument, our character offset

	ble	$t1, 9, hasFixedLetter	#if $t1 is less than or equal to 9 we skip doing letter specific stuff since it's not a letter 
	nop
	li	$t0, 0x41		#if the code ever gets here it means $t1 is a letter, we will update $t0 to be the "start point" for letters
	sub	$t1, $t1, 10		#then we remove 10 from the letter index since the value 10 should be the first letter, 11 should be the second and so on
hasFixedLetter:
	add	$t0, $t1, $t0		#now the "start point" for characters should be right no matter what is going to be printed, so we add the offset to it
	
	move	$v0, $t0
			#put the value of $t0 in the return value register
	jr	$ra			#return
	nop						#then we remove 10 from the letter index since the value 10 should be the first letter, 11 should be the second and so on
	
delay:
				#my number that is going to count upp to given value
	move 	$t0,$a0			
delay_loop:
	li	$t1,1
	
delay_timer:
	addi	$t1,$t1,1
	ble	$t1,13,delay_timer
	nop
	addi	$t0,$t0,-1
	bge	$t0,1,delay_loop
	nop
	jr $ra
	nop
time2string: 
	
	andi 	$t1,$a1,0x0000F000	#store four bit value to t1
	srl	$t1,$t1,12		#shift right så de är rätt position
	PUSH	$ra			#spara #ra då den ändras i hexasc
	PUSH	$a1			#spara a1
	PUSH	$a0			#spara a2
	move	$a0,$t1			#sett a1 to t1
	jal 	hexasc			#jump tp hexasv
	nop				#make sure next line doesnt run
	POP	$a0			#return bvalue of a0 needs to be in right oder
	POP	$a1
				#return a1
	sb	$v0,($a0)		#store value from hexasc to a0
	
	andi	$t1,$a1,0x00000F00	#store four bit value t t1
	srl	$t1,$t1,8		#shift all bits to the right
	PUSH	$a1			#save a1 in stack
	PUSH	$a0			#svae a0 to stack
	move	$a0,$t1			#change value of a0 to t1
	jal	hexasc			#call hexasc with new value a0
	nop				#stop from running next line
	POP	$a0			#restore value a0
	POP	$a1			#restore value a1
	sb	$v0,1($a0)		#insert value from hexasv to next position using pointer
	
	li	$s0,0x3A		#load imidiate value to s0
	sb	$s0,2($a0)		#insert to a0 using pointer
	
	andi	$t1,$a1,0x000000F0	#mask t1 to hold four bits from a0
	srl	$t1,$t1,4		#shift four bits to the right
	PUSH	$a1			#save a1 to stack
	PUSH	$a0			#save a0 to stack (oder imoirant
	move	$a0,$t1			#move value t1 to a0
	jal	hexasc			#use new value of a0 in hexasc
	nop				#make sure next line doesnt run
	POP	$a0			#return value for a0
	POP	$a1
				#return value of a1 important 
	sb 	$v0,3($a0)		#insert value from hexasc to next point in a0 using pointer
	
	andi $t1,$a1,0x0000000F		#mask value of a1 and only insert last four bits to t1
	PUSH	$a1			#save value a1 in stack	
	PUSH	$a0			#save value in stack oder is important
	move	$a0,$t1			#move value from t1 to a0
	jal	hexasc			#send new a0 to hexasc
	nop				#make sure next line doesnt run
	POP	$a0			#take back value for a0
	POP	$a1
	POP	$ra
				#take back value for a1 make sure oder is correk
	sb	$v0,4($a0)		#insert value of hexasc to a1 using pointer
	
	
					#insert null to right position
	li	$s2,0x58
	andi 	$t3,$a1,0x000000F0	
	andi 	$t4,$a1,0x0000000F	
	beq 	$t1,0x00,zero
	nop
back:
	li 	$t1,0x00			#load nullinging 
	sb	$t1,5($a0)
	jr	$ra
	nop
	
zerot:
	
	sb	$s2,5($a0)
	li 	$t1,0x00
	sb	$t1,6($a0)
	jr	$ra
	nop
zero:
	beq	$t2,0x00,zerot
	nop
	beq	$t2,$t2,back
	nop
