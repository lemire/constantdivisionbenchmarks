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
	xorl	%r8d, %r8d
	movl	$2, %r10d
	movabsq	$6148914691236517206, %r9 ## imm = 0x5555555555555556
	.p2align	4, 0x90
LBB0_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_2 Depth 2
	movl	$-1, %ecx
	movl	%r10d, %esi
	.p2align	4, 0x90
LBB0_2:                                 ##   Parent Loop BB0_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$1, %esi
	je	LBB0_3
## BB#6:                                ##   in Loop: Header=BB0_2 Depth=2
	cmpl	$536870910, %esi        ## imm = 0x1FFFFFFE
	jg	LBB0_9
## BB#7:                                ##   in Loop: Header=BB0_2 Depth=2
	movl	%esi, %eax
	andl	$1, %eax
	je	LBB0_9
## BB#8:                                ##   in Loop: Header=BB0_2 Depth=2
	leal	1(,%rsi,4), %edi
	cmpl	$1, %edi
	je	LBB0_3
LBB0_11:                                ##   in Loop: Header=BB0_2 Depth=2
	cmpl	$536870910, %edi        ## imm = 0x1FFFFFFE
	jg	LBB0_13
## BB#12:                               ##   in Loop: Header=BB0_2 Depth=2
	movl	%edi, %eax
	andl	$1, %eax
	je	LBB0_13
## BB#14:                               ##   in Loop: Header=BB0_2 Depth=2
	leal	1(,%rdi,4), %esi
	jmp	LBB0_15
	.p2align	4, 0x90
LBB0_9:                                 ##   in Loop: Header=BB0_2 Depth=2
	movslq	%esi, %rax
	imulq	%r9
	movq	%rdx, %rdi
	shrl	$31, %esi
	addl	%esi, %edi
	cmpl	$1, %edi
	jne	LBB0_11
	jmp	LBB0_3
	.p2align	4, 0x90
LBB0_13:                                ##   in Loop: Header=BB0_2 Depth=2
	movslq	%edi, %rax
	imulq	%r9
	movq	%rdx, %rsi
	shrl	$31, %edi
	addl	%edi, %esi
LBB0_15:                                ##   in Loop: Header=BB0_2 Depth=2
	addl	$2, %ecx
	cmpl	$999, %ecx              ## imm = 0x3E7
	jb	LBB0_2
## BB#4:                                ##   in Loop: Header=BB0_1 Depth=1
	addl	$1, %r10d
	cmpl	$1000000, %r10d         ## imm = 0xF4240
	jne	LBB0_1
	jmp	LBB0_5
	.p2align	4, 0x90
LBB0_3:                                 ##   in Loop: Header=BB0_1 Depth=1
	addl	$1, %r8d
	addl	$1, %r10d
	cmpl	$1000000, %r10d         ## imm = 0xF4240
	jne	LBB0_1
LBB0_5:
	movl	%r8d, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
