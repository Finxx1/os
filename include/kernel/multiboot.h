/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * <kernel/multiboot.h>
 * Provides structures and enums for using the Multiboot2 Info structure.
 */

#include <stdint.h>
#include <stddef.h>

typedef struct mbi_t mbi_t;
typedef struct mbi_tag_t mbi_tag_t;

typedef struct mbi_t {
	uint32_t total_size;
	uint32_t reserved;
	mbi_tag_t* tag;
} __attribute__((packed)) mbi_t;

typedef struct mbi_tag_t {
	uint32_t type;
	uint32_t size;
	void* data;
} __attribute__((packed)) mbi_tag_t;

enum {
	MULTIBOOT_TAG_TYPE_MEMMAP = 6,
	MULTIBOOT_TAG_TYPE_FB = 8,
	MULTIBOOT_TAG_TYPE_RSDP2 = 15,
};

typedef struct mbi_tag_memmap_entry_t {
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
	uint32_t reserved;
} __attribute__((packed)) mbi_tag_memmap_entry_t;

typedef struct mbi_tag_memmap_t {
	uint32_t type;
	uint32_t size;
	uint32_t entry_size;
	uint32_t entry_version;
	mbi_tag_memmap_entry_t entries;
} __attribute__((packed)) mbi_tag_memmap_t;

typedef struct mbi_tag_fb_t {
	uint32_t type;
	uint32_t size;
	uint8_t* addr;
	uint32_t pitch;
	uint32_t width;
	uint32_t height;
	uint8_t bpp;
	uint8_t fb_type;
	uint8_t reserved;
	union {
		struct {
			uint32_t color_count;
			struct {
				uint8_t r;
				uint8_t g;
				uint8_t b;
			} __attribute__((packed)) colors;
		} __attribute__((packed)) paletted;
		struct {
			uint8_t r_pos;
			uint8_t r_size;
			uint8_t g_pos;
			uint8_t g_size;
			uint8_t b_pos;
			uint8_t b_size;
		} __attribute__((packed)) direct;
	};
} __attribute__((packed)) mbi_tag_fb_t;

