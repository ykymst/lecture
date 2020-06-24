	.globl mystrcat
	.align 2
mystrcat:
	addi sp, sp, -32
	sd ra, 24(sp)
	sw a0, 20(sp)
	sw a1, 16(sp)
	jal mystrlen
	sw a0, 12(sp)
	lw a0, 16(sp)
	jal mystrlen
	sw a0, 8(sp)
	lw a0, 20(sp)
	lw a1, 12(sp)
	add a0, a0, a1
	lw a1, 16(sp)
	lw a2, 8(sp)
label1:
	beqz a2, label2
	lw a3, 0(a1)
	sw a3, 0(a0)
	addi a0, a0, 1
	addi a1, a1, 1
	addi a2, a2, -1
	j label1
label2:
	lw a0, 20(sp)
	ld ra, 24(sp)
	addi sp, sp, 32
	ret
mystrlen:
	li a1, 0
label3:
	lb a2, 0(a0)
	beqz a2, label4
	addi a0, a0, 1
	addi a1, a1, 1
	j label3
label4:	
	mv a0, a1
	ret
