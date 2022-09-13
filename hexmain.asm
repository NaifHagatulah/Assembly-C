  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,17		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	
	
	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #

hexasc:
	li	$t0, 0x30	

	andi	$t1, $a0, 0x0000000F	#apply bitmask. Could modify $a0 directly but not sure if that's allowed. $t1 is our "fixed" argument, our character offset

	ble	$t1, 9, hasFixedLetter	#if $t1 is less than or equal to 9 we skip doing letter specific stuff since it's not a letter 
	nop
	li	$t0, 0x41		#if the code ever gets here it means $t1 is a letter, we will update $t0 to be the "start point" for letters
	addi	$t1, $t1, -10		#then we remove 10 from the letter index since the value 10 should be the first letter, 11 should be the second and so on
	
hasFixedLetter:
	add	$t0, $t1, $t0		#now the "start point" for characters should be right no matter what is going to be printed, so we add the offset to it
	
	move	$v0, $t0		#put the value of $t0 in the return value register
	jr	$ra			#return
	nop				#I've tried having move $v0, $t0 here but it doesn't seem to work
