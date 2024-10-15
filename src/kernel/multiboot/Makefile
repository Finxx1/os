# SPDX-License-Identifier: BSD-2-Clause

JPREFIX := $(PREFIX)
PREFIX = src/kernel/multiboot/

KOBJS += $(PREFIX)entry.o

$(PREFIX)entry.o: $(PREFIX)entry.S
	$(AS) $(ASFLAGS) $< -o $@

PREFIX = $(JPREFIX)
