	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	cmpl	$1, %edi
	jg	LBB0_2
## BB#1:
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
	movl	$1, %r8d
	popq	%rbp
	movl	%r8d, %eax
	retq
LBB0_2:
	movl	$3, %ecx
	xorl	%r8d, %r8d
	xorl	%eax, %eax
	movl	$1, %edx
	## InlineAsm Start
	divl	%ecx
	## InlineAsm End
                                        ## kill: %EAX<def> %EAX<kill> %RAX<def>
                                        ## kill: %EDX<def> %EDX<kill> %RDX<def>
	movl	%edx, %ecx
	orl	$1, %ecx
	cmpl	$3, %ecx
	jne	LBB0_13
## BB#3:
	addl	$1, %eax
	cltq
	xorl	%r8d, %r8d
	movl	$2, %edx
	.p2align	4, 0x90
LBB0_4:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_5 Depth 2
	movl	$-1, %esi
	movl	%edx, %edi
	.p2align	4, 0x90
LBB0_5:                                 ##   Parent Loop BB0_4 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$1, %edi
	je	LBB0_11
## BB#6:                                ##   in Loop: Header=BB0_5 Depth=2
	cmpl	$536870910, %edi        ## imm = 0x1FFFFFFE
	jg	LBB0_8
## BB#7:                                ##   in Loop: Header=BB0_5 Depth=2
	movl	%edi, %ecx
	andl	$1, %ecx
	je	LBB0_8
## BB#9:                                ##   in Loop: Header=BB0_5 Depth=2
	leal	1(,%rdi,4), %ecx
	cmpl	$1, %ecx
	je	LBB0_11
LBB0_27:                                ##   in Loop: Header=BB0_5 Depth=2
	cmpl	$536870910, %ecx        ## imm = 0x1FFFFFFE
	jg	LBB0_29
## BB#28:                               ##   in Loop: Header=BB0_5 Depth=2
	movl	%ecx, %edi
	andl	$1, %edi
	je	LBB0_29
## BB#30:                               ##   in Loop: Header=BB0_5 Depth=2
	leal	1(,%rcx,4), %edi
	jmp	LBB0_31
	.p2align	4, 0x90
LBB0_8:                                 ##   in Loop: Header=BB0_5 Depth=2
	movslq	%edi, %rcx
	imulq	%rax, %rcx
	movq	%rcx, %rdi
	shrq	$32, %rdi
	shrq	$63, %rcx
	addl	%edi, %ecx
	cmpl	$1, %ecx
	jne	LBB0_27
	jmp	LBB0_11
	.p2align	4, 0x90
LBB0_29:                                ##   in Loop: Header=BB0_5 Depth=2
	movslq	%ecx, %rdi
	imulq	%rax, %rdi
	movq	%rdi, %rcx
	shrq	$32, %rcx
	shrq	$63, %rdi
	addl	%ecx, %edi
LBB0_31:                                ##   in Loop: Header=BB0_5 Depth=2
	addl	$2, %esi
	cmpl	$999, %esi              ## imm = 0x3E7
	jb	LBB0_5
	jmp	LBB0_12
	.p2align	4, 0x90
LBB0_11:                                ##   in Loop: Header=BB0_4 Depth=1
	addl	$1, %r8d
LBB0_12:                                ##   in Loop: Header=BB0_4 Depth=1
	addl	$1, %edx
	cmpl	$1000000, %edx          ## imm = 0xF4240
	jne	LBB0_4
	jmp	LBB0_18
LBB0_13:
	leal	(%rdx,%rdx), %ecx
	cmpl	$2, %ecx
	seta	%sil
	cmpl	%edx, %ecx
	setb	%cl
	orb	%sil, %cl
	movzbl	%cl, %ecx
	leal	(%rcx,%rax,2), %eax
	addl	$1, %eax
	cltq
	movl	$2, %edx
	.p2align	4, 0x90
LBB0_14:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_15 Depth 2
	movl	$-1, %esi
	movl	%edx, %edi
	.p2align	4, 0x90
LBB0_15:                                ##   Parent Loop BB0_14 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$1, %edi
	je	LBB0_16
## BB#19:                               ##   in Loop: Header=BB0_15 Depth=2
	cmpl	$536870910, %edi        ## imm = 0x1FFFFFFE
	jg	LBB0_22
## BB#20:                               ##   in Loop: Header=BB0_15 Depth=2
	movl	%edi, %ecx
	andl	$1, %ecx
	je	LBB0_22
## BB#21:                               ##   in Loop: Header=BB0_15 Depth=2
	leal	1(,%rdi,4), %ecx
	cmpl	$1, %ecx
	je	LBB0_16
LBB0_24:                                ##   in Loop: Header=BB0_15 Depth=2
	cmpl	$536870910, %ecx        ## imm = 0x1FFFFFFE
	jg	LBB0_26
## BB#25:                               ##   in Loop: Header=BB0_15 Depth=2
	movl	%ecx, %edi
	andl	$1, %edi
	je	LBB0_26
## BB#32:                               ##   in Loop: Header=BB0_15 Depth=2
	leal	1(,%rcx,4), %edi
	jmp	LBB0_33
	.p2align	4, 0x90
LBB0_22:                                ##   in Loop: Header=BB0_15 Depth=2
	movslq	%edi, %rcx
	imulq	%rax, %rcx
	shrq	$32, %rcx
	addl	%edi, %ecx
	movl	%ecx, %edi
	sarl	%edi
	shrl	$31, %ecx
	addl	%edi, %ecx
	cmpl	$1, %ecx
	jne	LBB0_24
	jmp	LBB0_16
	.p2align	4, 0x90
LBB0_26:                                ##   in Loop: Header=BB0_15 Depth=2
	movslq	%ecx, %rdi
	imulq	%rax, %rdi
	shrq	$32, %rdi
	addl	%ecx, %edi
	movl	%edi, %ecx
	sarl	%ecx
	shrl	$31, %edi
	addl	%ecx, %edi
LBB0_33:                                ##   in Loop: Header=BB0_15 Depth=2
	addl	$2, %esi
	cmpl	$999, %esi              ## imm = 0x3E7
	jb	LBB0_15
## BB#17:                               ##   in Loop: Header=BB0_14 Depth=1
	addl	$1, %edx
	cmpl	$1000000, %edx          ## imm = 0xF4240
	jne	LBB0_14
	jmp	LBB0_18
	.p2align	4, 0x90
LBB0_16:                                ##   in Loop: Header=BB0_14 Depth=1
	addl	$1, %r8d
	addl	$1, %edx
	cmpl	$1000000, %edx          ## imm = 0xF4240
	jne	LBB0_14
LBB0_18:
	movl	%r8d, %eax
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" **** need to give D on the command line. Abort.\n"


.subsections_via_symbols
