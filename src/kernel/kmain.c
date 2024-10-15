/* SPDX-License-Identifier: BSD-2-Clause */

#include <kernel/multiboot.h>
#include <kernel/kernel.h>

kernel_t kernel_data = {0};

static mbi_tag_t* next_tag(mbi_tag_t* tag) {
	if (tag->type == 0) return NULL;
	char* r = (char*)tag;
	r += tag->size;

	unsigned int rem = (uint64_t)r % 8;
	if (rem != 0) r += 8 - rem;

	return (mbi_tag_t*)r;
}

static size_t get_memmap_entry_count(mbi_tag_memmap_t* memmap) {
	size_t r = memmap->size;
	r -= 16; /* sizeof everything except entries */
	r /= memmap->entry_size;
	return r;
}

void kmain(mbi_t* mbi) {
	mbi_tag_t* tag = mbi->tag;

	do {
		switch (tag->type) {
		case MULTIBOOT_TAG_TYPE_MEMMAP:;
			mbi_tag_memmap_t* memmap = (mbi_tag_memmap_t*)tag;
			kernel_data.memmap_count = get_memmap_entry_count(memmap);
			kernel_data.memmaps = (memmap_t*)(&memmap->entries);
			break;
		case MULTIBOOT_TAG_TYPE_FB:;
			mbi_tag_fb_t* fb = (mbi_tag_fb_t*)tag;
			kernel_data.fb.addr = fb->addr;
			kernel_data.fb.pitch = fb->pitch;
			kernel_data.fb.width = fb->width;
			kernel_data.fb.height = fb->height;
			kernel_data.fb.bpp = fb->bpp;
			kernel_data.fb.type = fb->fb_type;
			if (fb->fb_type == 1)
				kernel_data.fb.direct = fb->direct;
			else
				kernel_data.fb.paletted = fb->paletted;
			break;
		case MULTIBOOT_TAG_TYPE_RSDP2:
			kernel_data.rsdp2_size = tag->size - 8;
			kernel_data.rsdp2 = ((char*)(tag)) + 8;
			break;
		}
	} while ((tag = next_tag(tag)) != NULL);


}
