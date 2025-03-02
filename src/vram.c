#include "global.h"
#include "common.h"
#include "structures.h"
#include "fileselect.h"

extern u32 gFixedTypeGfxData[];

void ReserveGFXSlots(u32, u32, u32);
void sub_080ADE74(u32);
void sub_080ADE24(void);
u32 FindFreeGFXSlots(u32);
void CleanUpGFXSlots(void);
void sub_080ADDD8(u32, u32);
void sub_080AE0C8(u32, Entity*, u32);
void SetGFXSlotStatus(GfxSlot*, u32);
u32 FindNextOccupiedGFXSlot(u32);
u32 FindFirstFreeGFXSlot(void);
void sub_080AE218(u32, u32);
void sub_080AE324(u32, u32);

void ResetPalettes(void) {
    GfxSlot* slots;
    GfxSlot* slot;
    u32 index;
    MemClear(&gGFXSlots, sizeof(gGFXSlots));
    // Reserve the first four slots for palettes.
    for (index = 0; index < 4; index++) {
        slots = gGFXSlots.slots;
        slot = &slots[index];
        ReserveGFXSlots(index, 0, 1);
        slot->status = GFX_SLOT_PALETTE;
        slot->referenceCount = 0x80;
    }
}

void sub_080ADD70(void) {
    u32 index;
    GfxSlot* slot;
    if (gGFXSlots.unk0 != 0) {
#ifndef EU
        if (gGFXSlots.unk_3 != 0) {
            sub_080ADE24();
        } else {
#endif
            index = 0;
            for (index = 0; index < MAX_GFX_SLOTS; index++) {
                slot = &gGFXSlots.slots[index];
                switch (slot->status) {
                    case GFX_SLOT_STATUS2:
                        slot->status = GFX_SLOT_UNLOADED;
                        break;
                    case GFX_SLOT_RESERVED:
                    case GFX_SLOT_GFX:
                    case GFX_SLOT_PALETTE:
                        if (slot->vramStatus == GFX_VRAM_3) {
                            sub_080ADE74(index);
                        }
                        break;
                }
            }
#ifndef EU
        }
#endif
    }
}

NONMATCH("asm/non_matching/vram/sub_080ADDD8.inc", void sub_080ADDD8(u32 index, u32 paletteIndex)) {
    GfxSlot* slot = &gGFXSlots.slots[index];
    slot->palettePointer = gGlobalGfxAndPalettes + (paletteIndex & 0xfffffc);
    if ((paletteIndex & 1) != 0) {
        slot->paletteIndex = 0xffff;
    } else {
        // TODO some cast here?
        slot->paletteIndex = ((paletteIndex)&0x7f00) >> 4;
    }
    slot->vramStatus = GFX_VRAM_3;
}
END_NONMATCH

void sub_080ADE24(void) {
    u32 index;
    GfxSlot* slot;
    gGFXSlots.unk_3 = 1;
    for (index = 0; index < MAX_GFX_SLOTS; index++) {
        slot = &gGFXSlots.slots[index];
        switch (slot->status) {
            case GFX_SLOT_FOLLOWER:
                break;
            case GFX_SLOT_RESERVED:
            case GFX_SLOT_GFX:
            case GFX_SLOT_PALETTE:
                sub_080ADE74(index);
                break;
            default:
                MemClear(slot, sizeof(GfxSlot));
                break;
        }
    }
    gGFXSlots.unk_3 = 0;
}

// Transfer gfx slot data to vram?
ASM_FUNC("asm/non_matching/vram/sub_080ADE74.inc", void sub_080ADE74(u32 index))

bool32 LoadFixedGFX(Entity* entity, u32 gfxIndex) {
#ifdef EU
    GfxSlot* slot;
    u32 index;
    u32 count;
    u32 result;
    u32 data;
    if (gfxIndex == 0) {
        result = TRUE;
    } else {
        for (index = 4; index < MAX_GFX_SLOTS; index++) {
            if (gfxIndex == gGFXSlots.slots[index].gfxIndex) {
                // Gfx is already loaded to a slot.
                sub_080AE0C8(index, entity, GFX_SLOT_RESERVED);
                result = TRUE;
                return result;
            }
        }
        data = gFixedTypeGfxData[gfxIndex];
        count = (data & 0x7f000000) >> 0x18;
        index = FindFreeGFXSlots(count);
        if (index != 0) {
            ReserveGFXSlots(index, gfxIndex, count);
            sub_080ADDD8(index, data);
        _080ADFF2:
            sub_080AE0C8(index, entity, GFX_SLOT_RESERVED);
            result = TRUE;
        } else {
            result = FALSE;
        }
    }
    return result;
#else

    GfxSlot* slot;
    u32 index;
    u32 count;

    if (gfxIndex != 0) {
        for (index = 4; index < MAX_GFX_SLOTS; index++) {
            if (gfxIndex == gGFXSlots.slots[index].gfxIndex) {
                // Gfx is already loaded to a slot.
                goto _080ADFF2;
            }
        }
        count = (gFixedTypeGfxData[gfxIndex] & 0x7f000000) >> 0x18;
        index = FindFreeGFXSlots(count);
        if (index == 0) {
            CleanUpGFXSlots();
            index = FindFreeGFXSlots(count);
            if (index == 0) {
                return 0;
            }
        }
        ReserveGFXSlots(index, gfxIndex, count);
        sub_080ADDD8(index, gFixedTypeGfxData[gfxIndex]);
    _080ADFF2:
        sub_080AE0C8(index, entity, GFX_SLOT_RESERVED);
    }
    return TRUE;
#endif
}

// If slotIndex != 0 the gfx loaded starting from that slot, else in the first fitting free one.
NONMATCH("asm/non_matching/vram/LoadSwapGFX.inc", u32 LoadSwapGFX(Entity* entity, u32 count, u32 slotIndex)) {
    u32 status;
    if ((slotIndex == 0) && (slotIndex = FindFreeGFXSlots(count), slotIndex == 0)) {
#ifndef EU
        CleanUpGFXSlots();
#endif
        slotIndex = FindFreeGFXSlots(count);
        if (slotIndex == 0) {
            goto _080AE058;
        }
    }
    status = gGFXSlots.slots[slotIndex].status;
    if (status != GFX_SLOT_PALETTE) {
        ReserveGFXSlots(slotIndex, 0, count);
        status = GFX_SLOT_GFX;
    }
    sub_080AE0C8(slotIndex, entity, status);
_080AE058:
    if (slotIndex != 0) {
        slotIndex = 1;
    }
    return slotIndex;
}
END_NONMATCH

void UnloadGFXSlots(Entity* param_1) {
    u32 slotIndex;
    GfxSlot* slot;
    s32 slotCount;

    slotIndex = param_1->spriteAnimation[0];
    param_1->spriteAnimation[0] = 0;
    if (slotIndex != 0) {
        slot = &gGFXSlots.slots[slotIndex];
        switch (slot->status) {
            case GFX_SLOT_RESERVED:
            case GFX_SLOT_GFX:
                if (slot->referenceCount != 0) {
                    if (--slot->referenceCount == 0) {
                        slotCount = slot->slotCount;
                        while (slotCount-- > 0) {
                            slot->status = GFX_SLOT_UNLOADED;
                            slot++;
                        }
                    }
                }
                break;
        }
    }
}

void sub_080AE0C8(u32 index, Entity* entity, u32 status) {
    GfxSlot* slot;
    entity->spriteVramOffset = index * 0x10 + 0x140;
    entity->spriteAnimation[0] = index;
    slot = &gGFXSlots.slots[index];
    if (*(s8*)&slot->referenceCount >= 0) {
        slot->referenceCount++;
    }
    SetGFXSlotStatus(slot, status);
}

void ReserveGFXSlots(u32 index, u32 gfxIndex, u32 slotCount) {
    GfxSlot* slot = &gGFXSlots.slots[index];
    MemClear(slot, slotCount * sizeof(GfxSlot));
    slot->slotCount = slotCount;
    slot->gfxIndex = gfxIndex;
    SetGFXSlotStatus(slot, GFX_SLOT_RESERVED);
}

void SetGFXSlotStatus(GfxSlot* slot, u32 status) {
    s32 index;
    slot->status = status;
    index = slot->slotCount;
    if (status != GFX_SLOT_PALETTE) {
        status = GFX_SLOT_FOLLOWER;
    }
    for (index--; index > 0; index--) {
        slot++;
        slot->status = status;
    }
}

/**
 * Finds slotCount continous free slots and returns the index of the first slot or 0 if not enough free slots could be
 * found.
 */
u32 FindFreeGFXSlots(u32 slotCount) {
    u32 index;
    u32 continuousFreeSlots = 0;

    // First search for enough continous free slots.
    for (index = 4; index < MAX_GFX_SLOTS; index++) {
        if (gGFXSlots.slots[index].status == GFX_SLOT_FREE) {
            continuousFreeSlots++;
            if (slotCount <= continuousFreeSlots) {
                return (index - continuousFreeSlots) + 1;
            }

        } else {
            continuousFreeSlots = 0;
        }
    }

    // Now also search for enough continous free or unused slots.
    continuousFreeSlots = 0;
    index = 4;
    for (index = 4; index < MAX_GFX_SLOTS; index++) {
#ifdef EU
        if (gGFXSlots.slots[index].status == GFX_SLOT_UNLOADED) {
#else
        if (gGFXSlots.slots[index].status == GFX_SLOT_FREE || gGFXSlots.slots[index].status == GFX_SLOT_UNLOADED) {
#endif
            continuousFreeSlots++;
            if (slotCount <= continuousFreeSlots) {
                return (index - continuousFreeSlots) + 1;
            }
        } else {
            continuousFreeSlots = 0;
        }
    }
    return 0;
}

#ifndef EU
void CleanUpGFXSlots(void) {
    u32 occupiedIndex;
    u32 firstFreeIndex;
    if (gGFXSlots.unk0 != 0) {
        for (occupiedIndex = 4; (occupiedIndex = FindNextOccupiedGFXSlot(occupiedIndex)) != 0; occupiedIndex++) {
            firstFreeIndex = FindFirstFreeGFXSlot();
            if (firstFreeIndex <= occupiedIndex) {
                sub_080AE218(occupiedIndex, firstFreeIndex);
                sub_080AE324(occupiedIndex, firstFreeIndex);
                occupiedIndex = firstFreeIndex;
            }
        }
    }
}

// Swap gfx
ASM_FUNC("asm/non_matching/vram/sub_080AE218.inc", void sub_080AE218(u32 a, u32 b))

// Swap palettes
ASM_FUNC("asm/non_matching/vram/sub_080AE324.inc", void sub_080AE324(u32 a, u32 b))

u32 FindNextOccupiedGFXSlot(u32 index) {
    for (; index < MAX_GFX_SLOTS - 1; index++) {
        switch (gGFXSlots.slots[index].status) {
            case GFX_SLOT_RESERVED:
            case GFX_SLOT_GFX:
                return index;
        }
    }
    return 0;
}

u32 FindFirstFreeGFXSlot(void) {
    u32 index;
    for (index = 4; index < MAX_GFX_SLOTS; index++) {
        switch (gGFXSlots.slots[index].status) {
            case GFX_SLOT_FREE:
            case GFX_SLOT_UNLOADED:
                return index;
            default:
                break;
        }
    }
    return 0;
}
#endif
