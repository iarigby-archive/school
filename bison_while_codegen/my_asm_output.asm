	.file	"io.c"
	.section	.rodata
.LC0:
	.string	"%u"
	.text
	.globl	read_unsigned
	.type	read_unsigned, @function
read_unsigned:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	stdin@GOT(%eax), %edx
	movl	(%edx), %edx
	subl	$4, %esp
	leal	-12(%ebp), %ecx
	pushl	%ecx
	leal	.LC0@GOTOFF(%eax), %ecx
	pushl	%ecx
	pushl	%edx
	movl	%eax, %ebx
	call	__isoc99_fscanf@PLT
	addl	$16, %esp
	movl	-12(%ebp), %eax
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	read_unsigned, .-read_unsigned
	.section	.rodata
.LC1:
	.string	"%d"
	.text
	.globl	read_signed
	.type	read_signed, @function
read_signed:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	stdin@GOT(%eax), %edx
	movl	(%edx), %edx
	subl	$4, %esp
	leal	-12(%ebp), %ecx
	pushl	%ecx
	leal	.LC1@GOTOFF(%eax), %ecx
	pushl	%ecx
	pushl	%edx
	movl	%eax, %ebx
	call	__isoc99_fscanf@PLT
	addl	$16, %esp
	movl	-12(%ebp), %eax
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	read_signed, .-read_signed
	.section	.rodata
.LC2:
	.string	"%s"
.LC3:
	.string	"true"
	.text
	.globl	read_boolean
	.type	read_boolean, @function
read_boolean:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$260, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	stdin@GOT(%ebx), %eax
	movl	(%eax), %eax
	subl	$4, %esp
	leal	-264(%ebp), %edx
	pushl	%edx
	leal	.LC2@GOTOFF(%ebx), %edx
	pushl	%edx
	pushl	%eax
	call	__isoc99_fscanf@PLT
	addl	$16, %esp
	subl	$8, %esp
	leal	.LC3@GOTOFF(%ebx), %eax
	pushl	%eax
	leal	-264(%ebp), %eax
	pushl	%eax
	call	strcmp@PLT
	addl	$16, %esp
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	read_boolean, .-read_boolean
	.section	.rodata
.LC4:
	.string	"%u\n"
	.text
	.globl	write_unsigned
	.type	write_unsigned, @function
write_unsigned:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$4, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	stdout@GOT(%eax), %edx
	movl	(%edx), %edx
	subl	$4, %esp
	pushl	8(%ebp)
	leal	.LC4@GOTOFF(%eax), %ecx
	pushl	%ecx
	pushl	%edx
	movl	%eax, %ebx
	call	fprintf@PLT
	addl	$16, %esp
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	write_unsigned, .-write_unsigned
	.section	.rodata
.LC5:
	.string	"%d\n"
	.text
	.globl	write_signed
	.type	write_signed, @function
write_signed:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$4, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	stdout@GOT(%eax), %edx
	movl	(%edx), %edx
	subl	$4, %esp
	pushl	8(%ebp)
	leal	.LC5@GOTOFF(%eax), %ecx
	pushl	%ecx
	pushl	%edx
	movl	%eax, %ebx
	call	fprintf@PLT
	addl	$16, %esp
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	write_signed, .-write_signed
	.section	.rodata
.LC6:
	.string	"true\n"
.LC7:
	.string	"false\n"
	.text
	.globl	write_boolean
	.type	write_boolean, @function
write_boolean:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$4, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	andl	$1, 8(%ebp)
	cmpl	$0, 8(%ebp)
	je	.L10
	movl	stdout@GOT(%eax), %edx
	movl	(%edx), %edx
	pushl	%edx
	pushl	$5
	pushl	$1
	leal	.LC6@GOTOFF(%eax), %edx
	pushl	%edx
	movl	%eax, %ebx
	call	fwrite@PLT
	addl	$16, %esp
	jmp	.L12
.L10:
	movl	stdout@GOT(%eax), %edx
	movl	(%edx), %edx
	pushl	%edx
	pushl	$6
	pushl	$1
	leal	.LC7@GOTOFF(%eax), %edx
	pushl	%edx
	movl	%eax, %ebx
	call	fwrite@PLT
	addl	$16, %esp
.L12:
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	write_boolean, .-write_boolean
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB6:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE6:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB7:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE7:
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
