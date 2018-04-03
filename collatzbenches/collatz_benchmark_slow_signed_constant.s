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
	subq	$16, %rsp
	cmpl	$1, %edi
	jg	LBB0_3
## BB#1:
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	leaq	L_.str(%rip), %rdi
	movl	$49, %esi
	movl	$1, %edx
	callq	_fwrite
	movl	$1, %ecx
	jmp	LBB0_2
LBB0_3:
	movl	$2, -4(%rbp)
	xorl	%ecx, %ecx
	movl	$2, %esi
	.p2align	4, 0x90
LBB0_4:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_5 Depth 2
	movl	$-1, %edi
	movl	%esi, %eax
	.p2align	4, 0x90
LBB0_5:                                 ##   Parent Loop BB0_4 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$1, %eax
	je	LBB0_6
## BB#8:                                ##   in Loop: Header=BB0_5 Depth=2
	cmpl	$715827881, %eax        ## imm = 0x2AAAAAA9
	jg	LBB0_11
## BB#9:                                ##   in Loop: Header=BB0_5 Depth=2
	movl	%eax, %edx
	andl	$1, %edx
	je	LBB0_11
## BB#10:                               ##   in Loop: Header=BB0_5 Depth=2
	leal	(%rax,%rax,2), %eax
	addl	$1, %eax
	cmpl	$1, %eax
	je	LBB0_6
LBB0_13:                                ##   in Loop: Header=BB0_5 Depth=2
	cmpl	$715827881, %eax        ## imm = 0x2AAAAAA9
	jg	LBB0_15
## BB#14:                               ##   in Loop: Header=BB0_5 Depth=2
	movl	%eax, %edx
	andl	$1, %edx
	je	LBB0_15
## BB#16:                               ##   in Loop: Header=BB0_5 Depth=2
	leal	(%rax,%rax,2), %eax
	addl	$1, %eax
	jmp	LBB0_17
	.p2align	4, 0x90
LBB0_11:                                ##   in Loop: Header=BB0_5 Depth=2
                                        ## kill: %EAX<def> %EAX<kill> %RAX<kill>
	cltd
	idivl	-4(%rbp)
                                        ## kill: %EAX<def> %EAX<kill> %RAX<def>
	cmpl	$1, %eax
	jne	LBB0_13
	jmp	LBB0_6
	.p2align	4, 0x90
LBB0_15:                                ##   in Loop: Header=BB0_5 Depth=2
                                        ## kill: %EAX<def> %EAX<kill> %RAX<kill>
	cltd
	idivl	-4(%rbp)
                                        ## kill: %EAX<def> %EAX<kill> %RAX<def>
LBB0_17:                                ##   in Loop: Header=BB0_5 Depth=2
	addl	$2, %edi
	cmpl	$999, %edi              ## imm = 0x3E7
	jb	LBB0_5
	jmp	LBB0_7
	.p2align	4, 0x90
LBB0_6:                                 ##   in Loop: Header=BB0_4 Depth=1
	addl	$1, %ecx
LBB0_7:                                 ##   in Loop: Header=BB0_4 Depth=1
	addl	$1, %esi
	cmpl	$1000000, %esi          ## imm = 0xF4240
	jne	LBB0_4
LBB0_2:
	movl	%ecx, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" **** need to give D on the command line. Abort.\n"


.subsections_via_symbols
