/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * <asm/macros.h>
 * Provides preprocessor assembly macros for miscellaneous things
 *
 * Size of directives taken from https://stackoverflow.com/a/63892588.
 * Why is it so god-darn hard to figure out how big a .word and .long are???
 */

#define SECTION .section
#define ALIGN .align
#define SKIP .skip
#define SIZE .size
#define GLOBAL .globl
#define TYPE .type
#define CODE(bits) .code ## bits

#define U8 .byte
#define U16 .word
#define U32 .long
#define U64 .quad
