/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

extern unsigned BOOTLOADER_START;
extern unsigned BOOTLOADER_HEAP_ADDR;

static unsigned __alloc_next = (unsigned) &BOOTLOADER_HEAP_ADDR;


unsigned get_heap_next()
{
	return __alloc_next;
}

void *alloc(unsigned sz)
{
    void *ptr;
	void (*entry)(void) = (void*)(BOOTLOADER_START+4);

	if(__alloc_next == 0)
	{
		entry();
	}
    ptr = (void*) __alloc_next;
    __alloc_next = (__alloc_next + sz + 31) & (~31);

    return ptr;
}

void *alloc_page_aligned(unsigned sz)
{
    __alloc_next = (__alloc_next + 4095) & (~4095);

    return alloc(sz);
}

void free(void * addr)
{
	addr = addr;
}

void func(unsigned n)
{
    __alloc_next *= n;
    __alloc_next *= n;
}