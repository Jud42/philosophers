	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.globl	_routine                ## -- Begin function routine
	.p2align	4, 0x90
_routine:                               ## @routine
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$-1, -4(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	cmpl	$10000000, %eax         ## imm = 0x989680
	jge	LBB0_3
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	_i(%rip), %eax
	addl	$1, %eax
	movl	%eax, _i(%rip)
	jmp	LBB0_1
LBB0_3:
	movl	_i(%rip), %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%ecx, %edx
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	movq	%rdx, %rax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -36(%rbp)
	movl	%edi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpl	$4, -40(%rbp)
	jge	LBB1_2
## %bb.1:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -36(%rbp)
	jmp	LBB1_8
LBB1_2:
	movl	$-1, -52(%rbp)
LBB1_3:                                 ## =>This Inner Loop Header: Depth=1
	movl	-52(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -52(%rbp)
	cmpl	$2, %eax
	jge	LBB1_7
## %bb.4:                               ##   in Loop: Header=BB1_3 Depth=1
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	_routine(%rip), %rdx
	movslq	-52(%rbp), %rsi
	shlq	$3, %rsi
	leaq	-32(%rbp), %rdi
	addq	%rsi, %rdi
	movq	%rcx, %rsi
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_6
## %bb.5:
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -36(%rbp)
	jmp	LBB1_8
LBB1_6:                                 ##   in Loop: Header=BB1_3 Depth=1
	xorl	%eax, %eax
	movl	%eax, %esi
	movslq	-52(%rbp), %rcx
	movq	-32(%rbp,%rcx,8), %rdi
	callq	_pthread_join
	jmp	LBB1_3
LBB1_7:
	movl	$0, -36(%rbp)
LBB1_8:
	movl	-36(%rbp), %eax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movl	%eax, -56(%rbp)         ## 4-byte Spill
	jne	LBB1_10
## %bb.9:
	movl	-56(%rbp), %eax         ## 4-byte Reload
	addq	$64, %rsp
	popq	%rbp
	retq
LBB1_10:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_i                      ## @i
.zerofill __DATA,__common,_i,4,2
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"my pthread [%d]\n"

L_.str.1:                               ## @.str.1
	.asciz	"philo: missing argument\n"

L_.str.2:                               ## @.str.2
	.asciz	"error: pthread_create\n"

.subsections_via_symbols
