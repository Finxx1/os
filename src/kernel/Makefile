# SPDX-License-Identifier: BSD-2-Clause

KPREFIX = $(PREFIX)
PREFIX = src/kernel/

KOBJS := $(PREFIX)entry.o $(PREFIX)kmain.o

ifeq ($(CONFIG_MULTIBOOT),y)
include src/kernel/multiboot/Makefile
endif

$(PREFIX)entry.o: $(PREFIX)entry.S
	$(AS) $(ASFLAGS) $< -o $@

$(PREFIX)kmain.o: $(PREFIX)kmain.c
	$(CC) $(CFLAGS) $< -o $@
	
hd/boot/kernel.elf: $(KOBJS)
	$(CC) $(LDFLAGS) -T $(PREFIX)link.ld -o $@ $(KOBJS)

OBJS += $(KOBJS) hd/boot/kernel.elf

PREFIX := $(KPREFIX)
