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
	li	$t0, 0x41		#if the code ever gets here it means $t1 is a letter, we will update $t0 to be the "start point" for letters
	sub	$t1, $t1, 10		#then we remove 10 from the letter index since the value 10 should be the first letter, 11 should be the second and so on
	
hasFixedLetter:
	add	$t0, $t1, $t0		#now the "start point" for characters should be right no matter what is going to be printed, so we add the offset to it
	
	move	$v0, $t0		#put the value of $t0 in the return value register
	jr	$ra			#return
	nop				#I've tried having move $v0, $t0 here but it doesn't seem to work

delay:
	move	$t0, $a0 			# this is "i"

while:
	ble	$t0, 0, done			# if $t0 is <= 0 we go to done

	subi	$t0, $t0, 1			# remove 1 from $t0

	li	$t1, 20 # this is the constant that needs to be changed!!
	li	$t2, 0				# this is "i"
innerLoop:
	addi	$t2, $t2, 1
	blt	$t2, $t1, innerLoop

	j while
done:
	jr	$ra
	nop
	
time2string:	
	andi	$t1, $a1, 0x0000F000	# store 4 MSB in $t1
	srl	$t1, $t1, 12
	
	PUSH	$a1			# save $a1
	PUSH	$a0			# save $a0
	
	move	$a0, $t1		# set argument for hexasc to $t1
	jal	hexasc			# call hexasc
	nop
	
	POP	$a0			# read $a0
	POP	$a1			# read $a1
	
	sb	$v0, ($a0)		# store value from hexasc at address $a0

	andi	$t1, $a1, 0x00000F00	# store 4 next MSB in $t2
	srl	$t1, $t1, 8
	
	PUSH	$a1			# re-store $a1
	PUSH	$a0			# re-store $a0
	
	move	$a0, $t1		# set argument for hexasc to $t1
	jal	hexasc			# call hexasc
	nop

	POP	$a0			# read $a0
	POP	$a1			# read $a1
	
	sb	$v0, 1($a0)		# store value from hexasc at address $a0
	
	li	$t0, 0x3A
	sb	$t0, 2($a0)
	
	andi	$t1, $a1, 0x000000F0	# store 4 LSB in $t1
	srl	$t1, $t1, 4
	
	PUSH	$a1			# re-store $a1
	PUSH	$a0			# re-store $a0
	
	move	$a0, $t1		# set argument for hexasc to $t1
	jal	hexasc			# call hexasc
	nop

	POP	$a0			# read $a0
	POP	$a1			# read $a1
	
	sb	$v0, 3($a0)		# store value from hexasc at address $a0
	
	andi	$t1, $a1, 0x0000000F	# store 4 LSB in $t1
	srl	$t1, $t1, 0
	
	PUSH	$a1			# re-store $a1
	PUSH	$a0			# re-store $a0
	
	move	$a0, $t1		# set argument for hexasc to $t1
	jal	hexasc			# call hexasc
	nop

	POP	$a0			# read $a0
	POP	$a1			# read $a1
	
	sb	$v0, 4($a0)		# store value from hexasc at address $a0
	
	li	$t0, 0x00		# load null byte
	sb	$t0, 5($a0)		# write null byte