/* SPDX-License-Identifier: BSD-2-Clause */

#include <asm/macros.h>

SECTION .multiboot
ALIGN 8

MULTIBOOTSTART:
U32 0xE85250D6 /* Magic */
U32 0 /* x86 Protected Mode */
U32 MULTIBOOTEND - MULTIBOOTSTART /* Header length */
U32 0 - (0xE85250D6 + 0 + (MULTIBOOTEND - MULTIBOOTSTART))

ALIGN 8
/* Framebuffer Tag */
U16 5 /* Type "framebuffer" */
U16 0 /* Not-optional */
U32 20 /* Size */
U32 1024 /* Width */
U32 768 /* Height */
U32 32 /* Bits per pixel */

ALIGN 8
/* End Tag */
U16 0 /* Type "end" */
U16 0 /* Not-optional */
U32 8 /* Size */
MULTIBOOTEND:

