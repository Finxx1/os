# SPDX-License-Identifier: BSD-2-Clause
VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_PATCH = 0

OBJS :=

CC = x86_64-elf-gcc
CFLAGS = -c -mno-red-zone -I include -ffreestanding
AS = x86_64-elf-gcc
ASFLAGS = -c -I include -ffreestanding
LDFLAGS = -mno-red-zone -ffreestanding -O2 -nostdlib

ifeq ($(CONFIG_DEBUG),y)
CFLAGS += -g
ASFLAGS += -g
LDFLAGS += -g
endif

all: hd/boot/kernel.elf
	grub-mkrescue -o myos.iso hd

clean:
	rm -f $(OBJS) myos.iso

debug: clean all
	qemu-system-x86_64 -bios OVMF.fd -cdrom myos.iso -s -S &
	gdb hd/boot/kernel.elf

include config.mk
include src/Makefile

