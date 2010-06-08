/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of jonny nor the name of any other
 *    contributor may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY jonny AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL jonny OR ANY OTHER
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CART_H
#define _CART_H

#include "gbem.h"


#define CART_ROM_ENTRY		0x0100
#define CART_SG_DATA		0x0104
#define CART_ROM_TITLE		0x0134
#define CART_COLOR			0x0143
#define CART_LICENSEE_MSB	0x0144
#define CART_LICENSEE_LSB	0x0145
#define CART_SGB_FUNC		0x0146
#define CART_INFO			0x0147
#define CART_ROM_SIZE		0x0148
#define CART_RAM_SIZE		0x0149
#define CART_DEST_CODE		0x014A
#define CART_OLD LICENSEE	0x014B
#define CART_ROM_VER		0x014C
#define CART_COMP_CHECKSUM	0x014D
#define CART_CHECKSUM		0x014E

#define MBC1_MODE_16MROM_8KRAM		0
#define MBC1_MODE_4MROM_32KRAM		1

typedef struct {
	Byte *rom;
	Byte *ram;
	char *rom_title;
	char *rom_path;
	unsigned int ram_size, rom_size, ram_banks, rom_banks, rom_block;
	unsigned int rom_bank, ram_bank;
	unsigned int mbc, mbc_mode;
	int is_for_cgb, is_for_sgb;
	int has_batt, has_ram, has_sram, has_rumble, has_timer, has_mmm01;
	int is_loaded;
	unsigned int mbc3_rtc_map;
} Cart;

int load_rom(const char* fn);
void unload_rom();
void cart_reset();

// accessors
void write_rom(Word address, Byte value);
Byte read_rom(Word address);
static inline void write_cart_ram(Word address, Byte value);
static inline Byte read_cart_ram(Word address);

static inline void write_cart_ram(Word address, Byte value) {
	extern Cart cart;
	cart.ram[address + (cart.ram_bank * 0x2000)] = value;
}

static inline Byte read_cart_ram(Word address) {
	extern Cart cart;
	return cart.ram[address + (cart.ram_bank * 0x2000)];
}


#endif /* _CART_H */
