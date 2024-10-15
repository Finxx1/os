# SPDX-License-Identifier: BSD-2-Clause

# This file contains all the options for building the operating system. Some
# may enable or disable other options, and each has a comment explaining what
# they do. To disable an option, comment the line that sets it to 'y' OR set
# it to 'n'.

# CONFIG_DEBUG - generate debug symbols
# if set, the kernel binary will be built with debug symbols
# if not set, no debug symbols will be generated
CONFIG_DEBUG = y

# CONFIG_MULTIBOOT - use multiboot2 booting
# if set, the kernel binary supports the multiboot2 boot protocol
# if not set, another method must be used
CONFIG_MULTIBOOT = y
