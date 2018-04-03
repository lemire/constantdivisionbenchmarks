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
	movl	$3, %esi
	xorl	%r8d, %r8d
	xorl	%eax, %eax
	movl	$1, %edx
	## InlineAsm Start
	divl	%esi
	## InlineAsm End
                                        ## kill: %EAX<def> %EAX<kill> %RAX<def>
                                        ## kill: %EDX<def> %EDX<kill> %RDX<def>
	leal	(%rdx,%rdx), %esi
	cmpl	$2, %esi
	seta	%dil
	cmpl	%edx, %esi
	setb	%dl
	orb	%dil, %dl
	movzbl	%dl, %edx
	leal	(%rdx,%rax,2), %eax
	addl	$1, %eax
	cltq
	movl	$2, %edx
	.p2align	4, 0x90
LBB0_3:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_4 Depth 2
	movl	$-1, %esi
	movl	%edx, %edi
	.p2align	4, 0x90
LBB0_4:                                 ##   Parent Loop BB0_3 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$1, %edi
	je	LBB0_5
## BB#8:                                ##   in Loop: Header=BB0_4 Depth=2
	cmpl	$536870910, %edi        ## imm = 0x1FFFFFFE
	jg	LBB0_11
## BB#9:                                ##   in Loop: Header=BB0_4 Depth=2
	movl	%edi, %ecx
	andl	$1, %ecx
	je	LBB0_11
## BB#10:                               ##   in Loop: Header=BB0_4 Depth=2
	leal	1(,%rdi,4), %edi
	cmpl	$1, %edi
	je	LBB0_5
LBB0_13:                                ##   in Loop: Header=BB0_4 Depth=2
	cmpl	$536870910, %edi        ## imm = 0x1FFFFFFE
	jg	LBB0_15
## BB#14:                               ##   in Loop: Header=BB0_4 Depth=2
	movl	%edi, %ecx
	andl	$1, %ecx
	je	LBB0_15
## BB#16:                               ##   in Loop: Header=BB0_4 Depth=2
	leal	1(,%rdi,4), %edi
	jmp	LBB0_17
	.p2align	4, 0x90
LBB0_11:                                ##   in Loop: Header=BB0_4 Depth=2
	movslq	%edi, %rcx
	imulq	%rax, %rcx
	shrq	$32, %rcx
	addl	%edi, %ecx
	movl	%ecx, %edi
	shrl	$31, %edi
	leal	(%rcx,%rdi,2), %edi
	sarl	%edi
	cmpl	$1, %edi
	jne	LBB0_13
	jmp	LBB0_5
	.p2align	4, 0x90
LBB0_15:                                ##   in Loop: Header=BB0_4 Depth=2
	movslq	%edi, %rcx
	imulq	%rax, %rcx
	shrq	$32, %rcx
	addl	%edi, %ecx
	movl	%ecx, %edi
	shrl	$31, %edi
	leal	(%rcx,%rdi,2), %edi
	sarl	%edi
LBB0_17:                                ##   in Loop: Header=BB0_4 Depth=2
	addl	$2, %esi
	cmpl	$999, %esi              ## imm = 0x3E7
	jb	LBB0_4
## BB#6:                                ##   in Loop: Header=BB0_3 Depth=1
	addl	$1, %edx
	cmpl	$1000000, %edx          ## imm = 0xF4240
	jne	LBB0_3
	jmp	LBB0_7
	.p2align	4, 0x90
LBB0_5:                                 ##   in Loop: Header=BB0_3 Depth=1
	addl	$1, %r8d
	addl	$1, %edx
	cmpl	$1000000, %edx          ## imm = 0xF4240
	jne	LBB0_3
LBB0_7:
	movl	%r8d, %eax
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" **** need to give D on the command line. Abort.\n"


.subsections_via_symbols
