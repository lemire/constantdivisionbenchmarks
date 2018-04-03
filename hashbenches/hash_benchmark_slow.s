	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_slowmod                ## -- Begin function slowmod
	.p2align	4, 0x90
_slowmod:                               ## @slowmod
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	xorl	%edx, %edx
	movl	%edi, %eax
	divl	%esi
	movl	%edx, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	movl	$2, -4(%rbp)
	movl	$1234, %edx             ## imm = 0x4D2
	movl	$100000000, %ecx        ## imm = 0x5F5E100
	.p2align	4, 0x90
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	%edx, %eax
	shll	$5, %eax
	subl	%edx, %eax
	addl	$27961, %eax            ## imm = 0x6D39
	xorl	%edx, %edx
	divl	-4(%rbp)
	movl	%edx, %eax
	shll	$5, %eax
	subl	%edx, %eax
	leal	27961(%rax), %eax
	xorl	%edx, %edx
	divl	-4(%rbp)
	movl	%edx, %eax
	shll	$5, %eax
	subl	%edx, %eax
	leal	27961(%rax), %eax
	xorl	%edx, %edx
	divl	-4(%rbp)
	movl	%edx, %eax
	shll	$5, %eax
	subl	%edx, %eax
	leal	27961(%rax), %eax
	xorl	%edx, %edx
	divl	-4(%rbp)
	movl	%edx, %eax
	shll	$5, %eax
	subl	%edx, %eax
	leal	27961(%rax), %eax
	xorl	%edx, %edx
	divl	-4(%rbp)
	addq	$-5, %rcx
	jne	LBB1_1
## BB#2:
	movl	%edx, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
