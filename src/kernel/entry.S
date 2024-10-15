/* SPDX-License-Identifier: BSD-2-Clause */

#include <asm/macros.h>

SECTION .bss
ALIGN 16
STACKBOTTOM:
SKIP 0x4000 /* 16 KiB */
STACKTOP:

SECTION .text
GLOBAL _start
CODE(32)
TYPE _start, @function
_start:
	movl $STACKTOP, %esp

	/*
	 * We are still in 32-bit mode right now. We need to enter 64-bit mode
	 * before we call kmain. Multiboot2 has already enabled A20 for us; we
	 * need to do everything else though, like setting up paging and a GDT.
	 */
	pushl %ebx /* Save MBI for later */

	movl $0x1000, %edi
	movl %edi, %cr3
	xor %eax, %eax
	mov $0x2000, %ecx
	rep stosl /* Clear page table */
	movl %cr3, %edi

	movl $0x2003, 0(%edi)
	movl $0x3003, 0x1000(%edi)
	movl $0x4003, 0x2000(%edi)
	movl $0x5003, 0x2008(%edi)

	/* Map 0-2Mb */
	movl $0x4000, %edi
	movl $0x3, %ebx
	movl $0x200, %ecx
_setentry:
	movl %ebx, (%edi)
	add $0x1000, %ebx
	add $8, %edi
	loop _setentry

	/* Map 2-4Mb */
	movl $0x5000, %edi
	movl $0x200003, %ebx
	movl $0x200, %ecx
_setentry2:
	movl %ebx, (%edi)
	add $0x1000, %ebx
	add $8, %edi
	loop _setentry2
	/*
	 * This could be clever and reuse _setentry, but that introduces
	 * unnecessary complexity.
	 */

	movl %cr4, %eax
	or $1<<5, %eax
	movl %eax, %cr4 /* Enable PAE */

	movl $0xC0000080, %ecx /* EFER MSR */
	rdmsr
	or $1<<8, %eax
	wrmsr /* Enable Long Mode */

	movl %cr0, %eax
	or $1<<31, %eax
	movl %eax, %cr0 /* Enable Paging */

	popl %ecx /* Restore MBI */

	lgdt (_gdt_ptr)
	jmp $8,$_j64

CODE(64)
_j64:
	movq %rcx, %rdi /* Move MBI into param 1 */
	call kmain

	cli
_loop:	hlt
	jmp _loop

SIZE _start, . - _start

SECTION .data
ALIGN 16
_gdt:
	_gdt_null:
		U64 0
	_gdt_code:
		U32 0xFFFF
		U8 0
		U8 1<<7|1<<4|1<<3|1<<1 /* Present | Not_Sys | Exec | Rw */
		U8 1<<7|1<<5|0xF /* Gran_4k | Long_Mode */
		U8 0
	_gdt_data:
		U32 0xFFFF
		U8 0
		U8 1<<7|1<<4|1<<1 /* Present | Not_Sys | Rw */
		U8 1<<7|1<<6|0xF /* Gran_4k | Sz_32 */
		U8 0
	_gdt_tss:
		U32 0x00000068
		U32 0x00CF8900
	_gdt_ptr:
		U16 . - _gdt - 1
		U64 _gdt
