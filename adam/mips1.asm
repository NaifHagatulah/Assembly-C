.data
.align 2
msg:    .space  32

.text
main: 	
	la $t1,msg
	addi $t2,$zero,0x61
	addi $t3,$zero,1
	addi $t4,$zero,5
	addi $t5,$t5,0x61
	addi $t7,$t7,8
	
	loop:
	sll $t5,$t5,8
	or $t5,$t5,$t2
	
	
	
	
	
	addi $t2,$t2,1
	addi $t3,$t3,1
	
	
	
	
	beq $t4,$t3,leep
	j 	loop
	leep:
	sw $t5,($t1)
	subi $t2,$t2,1
	
	addi $t1,$t1,4
	addi $t6,$t6,1
	subi $t3,$t3,5
	beq $t6,$t7,done
	j	loop
	
	
	done: 
	la $t1, msg
	li $v0, 4
	add $a0, $zero, $t1
	syscall
	
stop: j 	stop
	
