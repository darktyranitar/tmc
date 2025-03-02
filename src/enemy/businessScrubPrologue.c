#define NENT_DEPRECATED
#include "entity.h"
#include "enemy.h"
#include "functions.h"

typedef struct {
    Entity base;
    u8 filler[0x10];
    u16 unk_78;
    u16 unk_7a;
    u8 filler2[8];
    u32 unk_84;
} BusinessScrubPrologueEntity;

extern void sub_080954AC(Entity*, u32);
extern u16 script_BusinessScrubIntro[];

void (*const BusinessScrubPrologue_Functions[])(Entity*);
void (*const gUnk_080D1A14[])(BusinessScrubPrologueEntity*);
const u8 gUnk_080D1A38[];
const s8 gUnk_080D1A3E[];
const u16 gUnk_080D1A4E[];

void sub_08046030(BusinessScrubPrologueEntity*, u32);
bool32 sub_08045F54(BusinessScrubPrologueEntity*, u32);
void sub_08045FF0(BusinessScrubPrologueEntity*);
bool32 sub_08045F98(BusinessScrubPrologueEntity*);
void sub_0804604C(BusinessScrubPrologueEntity*);
void sub_08045FA0(BusinessScrubPrologueEntity*);

void BusinessScrubPrologue(Entity* this) {
    EnemyFunctionHandler(this, BusinessScrubPrologue_Functions);
}

void BusinessScrubPrologue_OnTick(BusinessScrubPrologueEntity* this) {
    super->spriteSettings.draw = 1;
    gUnk_080D1A14[super->action](this);
    sub_0800445C(super);
}

void BusinessScrubPrologue_OnCollision(BusinessScrubPrologueEntity* this) {
    Entity* ent;
    if (super->hitType == 1) {
        if ((super->contactFlags & 0x7f) == 0x42) {
            super->action = 4;
            super->subAction = 0;
            super->timer = 0x28;
            super->flags &= ~ENT_COLLIDE;
            sub_08046030(this, 4);
            ent = CreateFx(super, FX_BUSH, 0);
            if (ent != NULL) {
                ent->z.HALF.HI -= 8;
            }

            gPlayerState.field_0x27[0] = 0xff;
            EnqueueSFX(SFX_EM_DEKUSCRUB_HIT);
            SetDefaultPriority(super, PRIO_MESSAGE);
        }
    }
}

void BusinessScrubPrologue_OnGrabbed(BusinessScrubPrologueEntity* this) {
}

void sub_08045C3C(BusinessScrubPrologueEntity* this) {
    super->subtimer = 0;
    this->unk_78 = super->x.HALF.HI;
    this->unk_7a = super->y.HALF.HI;
    super->animationState = 0;
    super->direction = 0x10;
    super->action = 5;
    super->timer = 0x78;
    super->spritePriority.b1 = 1;
    super->spriteSettings.draw = 1;
    sub_08046030(this, 0);
    sub_08095C48(super);
    StartCutscene(super, script_BusinessScrubIntro);
    sub_0807DD50(super);
}

void sub_08045CA4(BusinessScrubPrologueEntity* this) {
    super->spriteSettings.draw = 0;
    if (super->timer) {
        super->timer--;
    } else if (sub_08045F54(this, 0)) {
        sub_08045FF0(this);
        super->subAction = 0;
        super->subtimer = 1;
    }
}

void nullsub_24(BusinessScrubPrologueEntity* this) {
}

void sub_08045CE0(BusinessScrubPrologueEntity* this) {
    Entity* ent;
    u32 r6;
    GetNextFrame(super);

    switch (super->subAction) {
        case 0:
            r6 = 1;
            if (super->frame & ANIM_DONE) {
                super->subAction = 1;
                super->timer = 0x3c;
                super->subtimer = 0x10;
                sub_08045F98(this);
                sub_08046030(this, 1);
            }
            break;
        case 1:
            r6 = 1;
            if (--super->timer == 0) {
                super->subAction = 2;
                super->timer = 0x20;
                super->subtimer = 0;
                sub_08045F98(this);
                sub_08046030(this, 2);
            }
            break;
        case 2:
            r6 = 1;
            sub_0804604C(this);
            if (super->frame & 1) {
                ent = CreateProjectileWithParent(super, DEKU_SEED_PROJECTILE, 0);
                if (ent != NULL) {
                    ent->parent = super;
                    ent->direction = super->direction;
                    super->frame &= 0xfe;
                    super->subAction = 3;
                }
            }
            break;
        case 3:
            r6 = 2;
            if (super->frame & ANIM_DONE) {
                super->subAction = 4;
                super->timer = 0x50;
                sub_08046030(this, 1);
            }
            break;
        case 4:
            r6 = 2;
            if (--super->timer == 0) {
                if (sub_08045F54(this, 0)) {
                    super->subAction = 1;
                    super->timer = 0x3c;
                    super->subtimer = 0x10;
                    sub_08045F98(this);
                } else {
                    sub_08045FA0(this);
                    super->timer = 0x50;
                    super->subtimer = 0;
                }
            }
            break;
    }

    if (sub_08045F54(this, r6) == 0) {
        sub_08045FA0(this);
        super->subAction = 0;
        super->timer = 0;
        super->subtimer = 0;
    }
}

void sub_08045E14(BusinessScrubPrologueEntity* this) {
    Entity* ent;
    gPlayerState.field_0x27[0] = 0xff;
    switch (super->subAction) {
        case 0:
            if (super->timer == 0) {
                if (super->frame & ANIM_DONE) {
                    super->subAction = 1;
                    sub_08045F98(this);
                    sub_08046030(this, 5);
                    super->spritePriority.b1 = 1;
                }
            } else {
                super->timer--;
            }
            break;
        case 1:
            if (super->frame & ANIM_DONE) {
                super->action = 5;
                super->subAction = 0;
                sub_08046030(this, 0);
                ent = Create0x68FX(super, FX_STARS);
                if (ent != NULL) {
                    ent->spritePriority.b0 = 3;
                    ent->z.HALF.HI -= 0xc;
                    SetDefaultPriority(ent, PRIO_MESSAGE);
                }
            }
            break;
    }

    GetNextFrame(super);
    sub_0800445C(super);
}

void sub_08045EC8(BusinessScrubPrologueEntity* this) {
    sub_0807DD94(super, 0);
}

void sub_08045ED4(BusinessScrubPrologueEntity* this) {
    sub_08045FA0(this);
}

void sub_08045EDC(BusinessScrubPrologueEntity* this) {
    if (super->subAction == 0) {
        super->subAction++;
        super->timer = 0x20;
        super->subtimer = 0;
        sub_08045F98(this);
        sub_08046030(this, 2);
    }

    GetNextFrame(super);
    sub_0804604C(this);
    if (super->frame & 1) {
        super->frame &= 0xfe;
        sub_080954AC(super, this->unk_84);
        EnqueueSFX(SFX_18D);
    } else if (super->frame & ANIM_DONE) {
        super->action = 5;
        super->subAction = 0;
        sub_08046030(this, 1);
    }
}

void nullsub_25(BusinessScrubPrologueEntity* this) {
}

bool32 sub_08045F54(BusinessScrubPrologueEntity* this, u32 arg2) {
    Entity* ent = sub_08049DF4(1);
    u32 r3;
    if (ent == NULL)
        return 0;

    if (EntityInRectRadius(super, ent, 0x20, 0x20))
        return 0;
    if (arg2 == 2)
        return 1;
    r3 = 0x50;
    if (arg2) {
        r3 = 0x58;
    }

    if (EntityInRectRadius(super, ent, r3, r3))
        return 1;
    return 0;
}

bool32 sub_08045F98(BusinessScrubPrologueEntity* this) {
    super->direction = 0x10;
    return 1;
}

void sub_08045FA0(BusinessScrubPrologueEntity* this) {
    super->action = 1;
    COLLISION_OFF(super);
    super->spriteSettings.draw = 0;
    super->spritePriority.b1 = 0;
    super->x.HALF.HI = this->unk_78;
    super->y.HALF.HI = this->unk_7a;
    super->spriteOffsetX = 0;
    super->spriteOffsetY = 0;
    InitializeAnimation(super, 0);
}

void sub_08045FF0(BusinessScrubPrologueEntity* this) {
    super->action = 3;
    COLLISION_ON(super);
    super->spriteSettings.draw = 1;
    super->spritePriority.b1 = 1;
    sub_08045F98(this);
    sub_08046030(this, 1);
}

void sub_08046030(BusinessScrubPrologueEntity* this, u32 arg2) {
    InitializeAnimation(super, (super->direction >> 3) | gUnk_080D1A38[arg2]);
}

void sub_0804604C(BusinessScrubPrologueEntity* this) {
    if (super->timer) {
        if (--super->timer <= 0xf) {
            super->spriteOffsetY = gUnk_080D1A3E[super->timer];
        }
    }
}

void sub_08046078(BusinessScrubPrologueEntity* this) {
    s32 index;
    Entity* ent;
    const u16* ptr;
    gPlayerState.field_0x27[0] = 0;
    ptr = gUnk_080D1A4E;
    for (index = 0; index <= 4; index++) {
        ent = CreateFx(super, FX_DEATH, 0x40);

        if (ent != NULL) {
            ent->x.HALF.HI = gRoomControls.origin_x + *ptr;
            ptr++;
            ent->y.HALF.HI = gRoomControls.origin_y + *ptr;
            ptr++;
        }
    }

    EnqueueSFX(SFX_16E);
    RestorePrevTileEntity(0x7a2, 1);
    RestorePrevTileEntity(0x7a3, 1);
    RestorePrevTileEntity(0x7a5, 1);
    RestorePrevTileEntity(0x7a6, 1);
    RestorePrevTileEntity(0x7a7, 1);

    ent = CreateFx(super, FX_BIG_EXPLOSION2, 0x40);
    if (ent != NULL) {
        CopyPosition(super, ent);
        EnqueueSFX(SFX_184);
    }

    if (super->child != NULL) {
        super->child->action = 0xff;
    }

    sub_0804AA1C(super);
}

void (*const BusinessScrubPrologue_Functions[])(Entity*) = {
    (EntityActionPtr)BusinessScrubPrologue_OnTick,
    (EntityActionPtr)BusinessScrubPrologue_OnCollision,
    GenericKnockback,
    GenericDeath,
    GenericConfused,
    (EntityActionPtr)BusinessScrubPrologue_OnGrabbed,
};

void (*const gUnk_080D1A14[])(BusinessScrubPrologueEntity*) = {
    sub_08045C3C, sub_08045CA4, nullsub_24,   sub_08045CE0, sub_08045E14,
    sub_08045EC8, sub_08045ED4, sub_08045EDC, nullsub_25,
};

const u8 gUnk_080D1A38[] = { 0, 4, 8, 12, 16, 20 };

const s8 gUnk_080D1A3E[] = { 0, -1, -2, -3, -4, -5, -6, -7, -7, -6, -5, -4, -3, -2, -1, 0 };
const u16 gUnk_080D1A4E[] = { 0x228, 0x1e8, 0x238, 0x1e8, 0x258, 0x1e8, 0x268, 0x1e8, 0x278, 0x1e8, 0 };
