	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
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
	movl	$1234, %eax             ## imm = 0x4D2
	movabsq	$6148914691236517226, %rcx ## imm = 0x555555555555556A
	movl	$100000000, %esi        ## imm = 0x5F5E100
	leaq	-20(%rcx), %r8
	movl	$3, %edi
	.p2align	4, 0x90
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	%eax, %edx
	shll	$5, %edx
	subl	%eax, %edx
	addl	$27961, %edx            ## imm = 0x6D39
	imulq	%r8, %rdx
	mulxq	%rdi, %rax, %rdx
	imulq	%rcx, %rdx
	addq	%rcx, %rdx
	addq	$18620, %rdx            ## imm = 0x48BC
	mulxq	%rdi, %rax, %rdx
	imulq	%rcx, %rdx
	addq	%rcx, %rdx
	addq	$18620, %rdx            ## imm = 0x48BC
	mulxq	%rdi, %rax, %rdx
	imulq	%rcx, %rdx
	addq	%rcx, %rdx
	addq	$18620, %rdx            ## imm = 0x48BC
	mulxq	%rdi, %rax, %rdx
	imulq	%rcx, %rdx
	addq	%rcx, %rdx
	addq	$18620, %rdx            ## imm = 0x48BC
	mulxq	%rdi, %rdx, %rax
	addq	$-5, %rsi
	jne	LBB0_1
## BB#2:
                                        ## kill: %EAX<def> %EAX<kill> %RAX<kill>
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
