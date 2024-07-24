/*
 * Author: Tomo (@indiegdevstdio)
 * Battle system for XV
 */
#pragma bank 255

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <gb/hardware.h>
#include "vm.h"
#include "compat.h"
#include "bankdata.h"
#include "gbs_types.h"
#include "actor.h"
#include "vm_actor.h"

/*
void SetBankedSpriteDataEx(UBYTE i, UBYTE l, const unsigned char* ptr, UBYTE bank, UBYTE vram_bank) OLDCALL NONBANKED NAKED {
	i; l; ptr; bank; vram_bank;
__asm
	ldh a, (__current_bank)
	ld  (#__save), a

	ldhl  sp, #6
	ld  a, (hl)
	ldh	(__current_bank), a
	ld  (_rROMB0), a

	; Get vram_bank param (7 bytes away from stack pointer)
	ldhl sp, #7
	ld a, (hl)
	; Preserve current VRAM bank
	ldh (__save_vbk), a
	ldh a, (_VBK)
	ld (__current_vbk), a
	ld a, (__save_vbk)
	; Switch to desired VRAM bank
	ldh (_VBK), a

	pop bc
	call _set_sprite_data ; preserves bc

	; Restore original VRAM bank
	ld a, (__current_vbk)
	ldh (_VBK), a

	ld  a, (#__save)
	ldh (__current_bank), a
	ld  (_rROMB0), a
	ld  h, b
	ld  l, c
	jp  (hl)

__endasm;
}
*/

void SpriteTileReplace(SCRIPT_CTX * THIS, UBYTE actor_id, UBYTE target_tile, UBYTE tileset_bank, const tileset_t * tileset, UBYTE start_tile, UBYTE vram_bank) BANKED {
	vm_set_const(THIS, FN_ARG0, actor_id);
	UBYTE * n_actor = VM_REF_TO_PTR(FN_ARG0);
	actor_t * actor = actors + *n_actor;
	VBK_REG = vram_bank;
	SetBankedSpriteData(actor->base_tile + target_tile, 1, tileset->tiles + (start_tile << 4), tileset_bank);
	VBK_REG = 0;
}

void SetupSpriteTileReplace(SCRIPT_CTX * THIS) OLDCALL BANKED {
	tileset_t* tileset = *(tileset_t**)VM_REF_TO_PTR(FN_ARG0);
	uint8_t tileset_bank = *(uint8_t*)VM_REF_TO_PTR(FN_ARG1);
	UBYTE target_tile_idx = *(uint8_t*)VM_REF_TO_PTR(FN_ARG2);
	UBYTE source_tile_idx = *(uint8_t*)VM_REF_TO_PTR(FN_ARG3);
	UBYTE vram_bank = *(uint8_t*)VM_REF_TO_PTR(FN_ARG4);
	UBYTE actor_id = *(uint8_t*)VM_REF_TO_PTR(FN_ARG5);
	SpriteTileReplace(THIS, actor_id, target_tile_idx, tileset_bank, tileset, source_tile_idx, vram_bank);
}
