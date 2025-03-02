#define NENT_DEPRECATED
#include "entity.h"
#include "flags.h"
#include "sound.h"
#include "functions.h"
#include "asm.h"
#include "object.h"
#include "effects.h"

typedef struct {
    Entity base;
    u8 filler[0x10];
    u16 tilePos;
    u8 unk7a;
    u8 unk7b;
    u8 filler2[0xA];
    u16 objFlags;
} ObjectBlockingStairsEntity;

extern const Hitbox gUnk_080FD288;

void ObjectBlockingStairs_Init(ObjectBlockingStairsEntity*);
void ObjectBlockingStairs_Action1(ObjectBlockingStairsEntity*);
void ObjectBlockingStairs_Action2(ObjectBlockingStairsEntity*);
void ObjectBlockingStairs_Action3(ObjectBlockingStairsEntity*);
void sub_080932A8(ObjectBlockingStairsEntity*);
void sub_08093248(ObjectBlockingStairsEntity*);
void sub_08093280(ObjectBlockingStairsEntity*);
void sub_08093334(ObjectBlockingStairsEntity*);
void sub_08093364(ObjectBlockingStairsEntity*);
void ObjectBlockingStairs_Action4(ObjectBlockingStairsEntity*);
u32 sub_080932D8(u32);
void sub_080931A4(ObjectBlockingStairsEntity*, u32);

void ObjectBlockingStairs(Entity* this) {
    static void (*const actionFuncs[])(ObjectBlockingStairsEntity*) = {
        ObjectBlockingStairs_Init,    ObjectBlockingStairs_Action1, ObjectBlockingStairs_Action2,
        ObjectBlockingStairs_Action3, ObjectBlockingStairs_Action4,
    };

    actionFuncs[this->action]((ObjectBlockingStairsEntity*)this);
}

void ObjectBlockingStairs_Init(ObjectBlockingStairsEntity* this) {
    int iVar1;
    u32 uVar2;

    switch (sub_080932D8(super->type)) {
        case 1:
            super->action = 4;
            super->x.HALF.HI -= 0x20;
            uVar2 = 2;
            break;
        case 2:
            super->action = 4;
            super->x.HALF.HI += 0x20;
            uVar2 = 3;
            break;
        default:
            super->action = 1;
            super->speed = 0x80;
            super->carryFlags = 1;
            super->timer = 0;
            super->subtimer = 0;
            this->unk7a = 0x20;
            this->unk7b = 0x80;
            if (super->type == 0) {
                super->hitbox = (Hitbox*)&gUnk_080FD288;
            }
            uVar2 = 0;
            if ((this->objFlags) && !CheckFlags(this->objFlags)) {
                uVar2 = 1;
            }
            break;
    }

    sub_080931A4(this, uVar2);
}

void ObjectBlockingStairs_Action1(ObjectBlockingStairsEntity* this) {
    u32 tileType;
    int xDist;
    Entity* ent;

    xDist = (int)gPlayerEntity.x.HALF.HI - super->x.HALF.HI;

    if (this->objFlags) {
        if (!CheckFlags(this->objFlags)) {
            return;
        }
        if (this->unk7a != 0) {
            sub_080932A8(this);
            return;
        }
    }

    if ((this->unk7b & 0x3f) == 0) {
        this->unk7b |= 0xf;
        sub_080931A4(this, 0);
        if (xDist < 0) {
            this->unk7b |= 0x40;
        }
    }

    if (this->unk7b & 0x40) {
        tileType = (u32)GetTileType(this->tilePos - 1, super->collisionLayer);
    } else {
        tileType = (u32)GetTileType(this->tilePos + 1, super->collisionLayer);
    }

    switch (tileType) {
        case 0x4030:
        case 0x4031:
            super->action = 3;
            super->direction = Direction8FromAnimationState(gPlayerEntity.animationState);
            super->speed = 0x80;
            super->timer = 0x40;
            RequestPriorityDuration(super, 0x50);
            EnqueueSFX(SFX_10F);
            sub_08093248(this);
            return;
    }

    if ((gPlayerEntity.animationState & 2) == 0) {
        return;
    }
    RegisterCarryEntity(super);

    if (this->unk7b & 0x80) {
        this->unk7b &= ~0x80;
        if ((this->unk7b & 0x40) != 0) {
            SetTile(0x402c, this->tilePos - 1, super->collisionLayer);
            SetTile(0x403d, this->tilePos + 1, super->collisionLayer);
        } else {
            SetTile(0x403d, this->tilePos - 1, super->collisionLayer);
            SetTile(0x402d, this->tilePos + 1, super->collisionLayer);
        }
    } else if (this->unk7b & 0x40) {
        if (xDist >= 5) {
            this->unk7b &= ~(0x40 | 0x80);
            SetTile(0x403d, this->tilePos - 1, super->collisionLayer);
            SetTile(0x402d, this->tilePos + 1, super->collisionLayer);
        }
    } else {
        if (-xDist > 4) {
            this->unk7b |= 0x40;
            SetTile(0x402c, this->tilePos - 1, super->collisionLayer);
            SetTile(0x403d, this->tilePos + 1, super->collisionLayer);
        }
    }
}

void ObjectBlockingStairs_Action2(ObjectBlockingStairsEntity* this) {
    if (super->timer) {
        sub_08093280(this);
    } else {
        if (gPlayerState.heldObject == 0x12) {
            if ((gPlayerEntity.frame & 2) != 0 && ++super->subtimer > 8) {
                gPlayerState.queued_action = 16;
                gPlayerState.field_0x38 = 0x40;
                gPlayerState.flags |= PL_BUSY;
                gPlayerEntity.x.HALF.LO = 0;
                gPlayerEntity.y.HALF.LO = 0;
                super->direction = (gPlayerEntity.animationState ^ 4) << 2;
                super->timer = 0x40;
                EnqueueSFX(SFX_10F);
                sub_08093248(this);
            }
        } else if (super->subAction == 6) {
            super->action = 1;
            super->subtimer = 0;
        }
    }
}

void ObjectBlockingStairs_Action3(ObjectBlockingStairsEntity* this) {
    sub_0800445C(super);
    LinearMoveUpdate(super);
    if (--super->timer == 0) {
        sub_08093334(this);
    }
    sub_08093364(this);
}

void ObjectBlockingStairs_Action4(ObjectBlockingStairsEntity* this) {
}

void sub_080931A4(ObjectBlockingStairsEntity* this, u32 param_2) {
    static const u16 gUnk_08122850[] = { 0x4027, 0x4023, 0x4028, 0x402c, 0x402b, 0x402d, 0x4029, 0x4026, 0x402a };
    static const u16 gUnk_08122862[] = { 0x4027, 0x4023, 0x4028, 0x4024, 0x4022, 0x4025, 0x4029, 0x4026, 0x402a };
    static const u16 gUnk_08122874[] = { 0x4027, 0x4023, 0x4023, 0x4024, 0x4022, 0x4022, 0x4029, 0x4026, 0x4026 };
    static const u16 gUnk_08122886[] = { 0x4023, 0x4023, 0x4028, 0x4022, 0x4022, 0x4025, 0x4026, 0x4026, 0x402a };

    u32 collisionLayer;
    const u16* pTileTypes;
    u32 index;
    u32 tilePos;
    int iVar5;

    this->tilePos = COORD_TO_TILE(super);
    tilePos = this->tilePos - 0x40;
    collisionLayer = super->collisionLayer;

    switch (param_2) {
        case 1:
            pTileTypes = gUnk_08122862;
            break;
        case 2:
            pTileTypes = gUnk_08122874;
            break;
        case 3:
            pTileTypes = gUnk_08122886;
            break;
        default:
        case 0:
            pTileTypes = gUnk_08122850;
            break;
    }

    for (index = 0, iVar5 = 0; index < 9; index++) {
        u32 pos = tilePos + iVar5 + index - 1;
        SetTile(pTileTypes[index], pos, collisionLayer);
        switch (index) {
            case 2:
                iVar5 = 0x3d;
                break;
            case 5:
                iVar5 = 0x7a;
                break;
        }
    }
}

void sub_08093248(ObjectBlockingStairsEntity* this) {
    u32 collisionLayer;
    u32 tilePos;
    u32 index;
    int iVar4;

    tilePos = this->tilePos - 0x40;
    collisionLayer = super->collisionLayer;
    for (index = 0, iVar4 = 0; index < 9; index++) {
        RestorePrevTileEntity(tilePos + iVar4 + index - 1, collisionLayer);
        switch (index) {
            case 2:
                iVar4 = 0x3d;
                break;
            case 5:
                iVar4 = 0x7a;
                break;
        }
    }
}

void sub_08093280(ObjectBlockingStairsEntity* this) {
    sub_0800445C(super);
    LinearMoveUpdate(super);
    if (--super->timer == 0) {
        sub_08093334(this);
    }
    sub_08093364(this);
}

void sub_080932A8(ObjectBlockingStairsEntity* this) {
    this->unk7a--;
    switch (this->unk7a & 3) {
        case 1:
            super->spriteOffsetX = 1;
            break;
        case 3:
            super->spriteOffsetX = -1;
            break;
        default:
            super->spriteOffsetX = 0;
            break;
    }
}

typedef struct {
    u32 flagBank;
    u16 unk4;
    u16 unk6;
} struct_gUnk_08122898;

const struct_gUnk_08122898 gUnk_08122898[] = {
    { FLAG_BANK_2, 0xa1, 0xa2 },
    { FLAG_BANK_10, 0x6f, 0x70 },
};

u32 sub_080932D8(u32 param_1) {
    const struct_gUnk_08122898* ptr = gUnk_08122898 + param_1;

    if (CheckLocalFlagByBank(ptr->flagBank, ptr->unk4)) {
        return 1;
    } else {
        if (CheckLocalFlagByBank(ptr->flagBank, ptr->unk6)) {
            return 2;
        } else {
            return 0;
        }
    }
}

void sub_08093308(u32 param_1, u32 param_2) {
    const struct_gUnk_08122898* ptr = gUnk_08122898 + param_1;
    if (param_2 == 1) {
        SetLocalFlagByBank(ptr->flagBank, ptr->unk4);
    } else if (param_2 == 2) {
        SetLocalFlagByBank(ptr->flagBank, ptr->unk6);
    }
}

void sub_08093334(ObjectBlockingStairsEntity* this) {
    u32 uVar1;

    super->action = 4;
    if (super->direction & 0x10) {
        uVar1 = 1;
    } else {
        uVar1 = 2;
    }
    sub_080931A4(this, uVar1 + 1);
    sub_08093308(super->type, uVar1);
    EnqueueSFX(SFX_SECRET);
}

void sub_08093364(ObjectBlockingStairsEntity* this) {
    s32 sVar1;
    Entity* dashEffectEnt;

    if ((super->timer & 3) == 0) {
        dashEffectEnt = CreateObject(SPECIAL_FX, FX_DASH, 0);
        if (dashEffectEnt != NULL) {
            dashEffectEnt->parent = super;
            CopyPosition(super, dashEffectEnt);
            if (super->direction & 0x10) {
                dashEffectEnt->x.HALF.HI += 0x12;
            } else {
                dashEffectEnt->x.HALF.HI -= 0x12;
            }

            sVar1 = dashEffectEnt->y.HALF.HI;
            if (super->timer & 8) {
                dashEffectEnt->y.HALF.HI = sVar1 + 8;
            } else {
                dashEffectEnt->y.HALF.HI = sVar1 - 8;
            }
        }
    }
}
