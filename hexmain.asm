  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,11		# change this to test different values

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
	li	$t3, 0x0000000F
	li	$t0, 0x30

	and	$t1, $a0, $t3	#only use the 4 least significant bits. Could modify $a0 directly but not sure if that's allowed

	li	$t3, 9
	
	ble	$t1, $t3, hasFixedLetter
	li	$t0, 0x41
	sub	$t1, $t1, 10
	
hasFixedLetter:
	add	$t0, $t1, $t0
	
	move	$v0, $t0
	jr	$ra
	nop			#I've tried having move $v0, $t0 here but it doesn't seem to work
