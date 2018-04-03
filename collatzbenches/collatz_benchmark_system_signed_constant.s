	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	cmpl	$2, %edi
	jge	LBB0_1
## BB#17:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	leaq	L_.str(%rip), %rdi
	movl	$49, %esi
	movl	$1, %edx
	callq	_fwrite
	movl	$1, %eax
	popq	%rbp
	retq
LBB0_1:
	xorl	%eax, %eax
	movl	$2, %ecx
	.p2align	4, 0x90
LBB0_2:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_3 Depth 2
	movl	$-1, %edx
	movl	%ecx, %esi
	.p2align	4, 0x90
LBB0_3:                                 ##   Parent Loop BB0_2 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$1, %esi
	je	LBB0_4
## BB#7:                                ##   in Loop: Header=BB0_3 Depth=2
	cmpl	$536870910, %esi        ## imm = 0x1FFFFFFE
	jg	LBB0_10
## BB#8:                                ##   in Loop: Header=BB0_3 Depth=2
	movl	%esi, %edi
	andl	$1, %edi
	je	LBB0_10
## BB#9:                                ##   in Loop: Header=BB0_3 Depth=2
	leal	1(,%rsi,4), %esi
	cmpl	$1, %esi
	je	LBB0_4
LBB0_12:                                ##   in Loop: Header=BB0_3 Depth=2
	cmpl	$536870910, %esi        ## imm = 0x1FFFFFFE
	jg	LBB0_14
## BB#13:                               ##   in Loop: Header=BB0_3 Depth=2
	movl	%esi, %edi
	andl	$1, %edi
	je	LBB0_14
## BB#15:                               ##   in Loop: Header=BB0_3 Depth=2
	leal	1(,%rsi,4), %esi
	jmp	LBB0_16
	.p2align	4, 0x90
LBB0_10:                                ##   in Loop: Header=BB0_3 Depth=2
	movslq	%esi, %rsi
	imulq	$1431655766, %rsi, %rsi ## imm = 0x55555556
	movq	%rsi, %rdi
	shrq	$63, %rdi
	shrq	$32, %rsi
	addl	%edi, %esi
	cmpl	$1, %esi
	jne	LBB0_12
	jmp	LBB0_4
	.p2align	4, 0x90
LBB0_14:                                ##   in Loop: Header=BB0_3 Depth=2
	movslq	%esi, %rsi
	imulq	$1431655766, %rsi, %rsi ## imm = 0x55555556
	movq	%rsi, %rdi
	shrq	$63, %rdi
	shrq	$32, %rsi
	addl	%edi, %esi
LBB0_16:                                ##   in Loop: Header=BB0_3 Depth=2
	addl	$2, %edx
	cmpl	$999, %edx              ## imm = 0x3E7
	jb	LBB0_3
## BB#5:                                ##   in Loop: Header=BB0_2 Depth=1
	addl	$1, %ecx
	cmpl	$1000000, %ecx          ## imm = 0xF4240
	jne	LBB0_2
	jmp	LBB0_6
	.p2align	4, 0x90
LBB0_4:                                 ##   in Loop: Header=BB0_2 Depth=1
	addl	$1, %eax
	addl	$1, %ecx
	cmpl	$1000000, %ecx          ## imm = 0xF4240
	jne	LBB0_2
LBB0_6:
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" **** need to give D on the command line. Abort.\n"


.subsections_via_symbols
