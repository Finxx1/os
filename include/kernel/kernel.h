/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * <kernel/kernel.h>
 * Provides general kernel structures and enums.
 */

typedef struct memmap_t {
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
	uint32_t reserved;
} __attribute__((packed)) memmap_t;

typedef struct framebuffer_t {
	uint8_t* addr;
	uint32_t pitch;
	uint32_t width;
	uint32_t height;
	uint8_t bpp;
	uint8_t type;
	
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
} framebuffer_t;

typedef struct kernel_t {
	size_t memmap_count;
	memmap_t* memmaps;

	framebuffer_t fb;

	size_t rsdp2_size;
	void* rsdp2;
} kernel_t;

extern kernel_t kernel_data;
