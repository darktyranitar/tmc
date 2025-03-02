/**
 * @file vaatiTransfiguredEye.c
 * @ingroup Enemies
 *
 * @brief Vaati Transfigured Eye enemy
 */

#include "entity.h"
#include "enemy.h"
#include "message.h"
#include "physics.h"
#include "functions.h"

void sub_08045A00(Entity*);
void sub_08045A28(Entity*);

void VaatiTransfiguredEye_OnTick(Entity*);
void VaatiTransfiguredEye_OnCollision(Entity*);
void VaatiTransfiguredEye_OnDragged(Entity*);
void VaatiTransfiguredEyeFunction0Action0(Entity*);
void VaatiTransfiguredEyeFunction0Action1(Entity*);
void VaatiTransfiguredEyeFunction0Action2(Entity*);
void VaatiTransfiguredEyeFunction0Action3(Entity*);
void VaatiTransfiguredEyeFunction0Action4(Entity*);

void (*const VaatiTransfiguredEye_Functions[])(Entity*) = {
    VaatiTransfiguredEye_OnTick,
    VaatiTransfiguredEye_OnCollision,
    VaatiTransfiguredEye_OnTick,
    GenericDeath,
    GenericConfused,
    VaatiTransfiguredEye_OnDragged,
};

void (*const vaatiTransfiguredEyeFunction0Actions[])(Entity*) = {
    VaatiTransfiguredEyeFunction0Action0, VaatiTransfiguredEyeFunction0Action1, VaatiTransfiguredEyeFunction0Action2,
    VaatiTransfiguredEyeFunction0Action3, VaatiTransfiguredEyeFunction0Action4,
};

struct xy {
    s8 x;
    s8 y;
} PACKED;

const struct xy gUnk_080D18B4[] = { { 0xe8, 0xf6 }, { 0xf6, 0xe8 }, { 0x0a, 0xe8 }, { 0x18, 0xf6 },
                                    { 0x18, 0x0a }, { 0x0a, 0x18 }, { 0xf6, 0x18 }, { 0xe8, 0x0a } };

void VaatiTransfiguredEye(Entity* this) {
    EnemyFunctionHandler(this, VaatiTransfiguredEye_Functions);
}

void VaatiTransfiguredEye_OnTick(Entity* this) {
    vaatiTransfiguredEyeFunction0Actions[this->action](this);
}

void VaatiTransfiguredEye_OnCollision(Entity* this) {
    u8 bVar1;
    Entity* pEVar4;

    if (this->type != 0) {
        pEVar4 = this->parent->parent;
        if ((this->contactFlags & 0x80) != 0) {
            bVar1 = this->contactFlags & 0x3f;
            if ((bVar1 == 0xe) || (bVar1 == 0x15)) {

                if (this->field_0x80.HALF.HI == 0) {
                    this->action = 3;
                    this->field_0x80.HALF.HI += 1;
                    InitializeAnimation(this, (this->type << 3) | (this->timer + 2));
                    InitializeAnimation(this->parent, (this->parent->type << 3) | (this->timer + 2));
                }
                if (this->timer != 0) {
                    SoundReq(SFX_17A);
                } else {
                    SoundReq(SFX_ITEM_GLOVES_KNOCKBACK);
                }
            } else {
                if (this->health != 0xff) {
                    this->health = 0xff;
                    if (this->timer != 0 && (pEVar4->field_0x80.HALF.HI != 0)) {
                        pEVar4->field_0x76.HALF.LO |= (1 << this->type2);
                        if (this->cutsceneBeh.HALF.HI == 0) {
                            this->cutsceneBeh.HALF.HI += 1;
                            InitializeAnimation(this, this->type << 3 | 6);
                            InitializeAnimation(this->parent, this->parent->type << 3 | 6);
                        }
                    }
                }
            }
        }
    }
    EnemyFunctionHandlerAfterCollision(this, VaatiTransfiguredEye_Functions);
}

void VaatiTransfiguredEye_OnDragged(Entity* this) {
}

void VaatiTransfiguredEyeFunction0Action0(Entity* this) {
    Entity* child;
    u8 bVar2;

    bVar2 = gMessage.doTextBox & 0x7f;
    if ((gMessage.doTextBox & 0x7f) == 0) {
        this->action = 1;
        this->spriteSettings.draw = 0;
        this->field_0x80.HALF.LO = bVar2;
        this->field_0x80.HALF.HI = bVar2;
        this->cutsceneBeh.HALF.HI = bVar2;
        this->subtimer = bVar2;
        this->field_0x82.HALF.LO = 0x30;
        this->field_0x82.HALF.HI = bVar2;
        if (this->type == 0) {
            sub_08045A00(this);
            child = CreateEnemy(VAATI_TRANSFIGURED_EYE, 1);
            if (child != NULL) {
                child->parent = this;
                this->child = child;
                child->timer = this->timer;
                child->type2 = this->type2;
                CopyPosition(this, child);
            }
        } else {
            this->spriteOffsetY = 1;
        }
        InitializeAnimation(this, (u32)this->type << 3 | 1);
    }
}

void VaatiTransfiguredEyeFunction0Action1(Entity* this) {
    sub_08045A28(this);
    if (this->field_0x82.HALF.LO == 0) {
        if ((this->frame & ANIM_DONE) != 0) {
            if (this->type != 0) {
                COLLISION_ON(this);
            }
            this->action = 2;
            InitializeAnimation(this, this->type << 3);
        }
    } else {
        if (--this->field_0x82.HALF.LO == 0) {
            this->spriteSettings.draw = 1;
        }
    }
}

void VaatiTransfiguredEyeFunction0Action2(Entity* this) {
    Entity* parent;

    sub_08045A28(this);
    parent = this->parent;
    if (this->type != 0) {
        parent = parent->parent;
    }
    if ((parent->action == 3) && (parent->field_0x80.HALF.LO == 1)) {
        this->action = 4;
        this->subtimer = 0;
        if (this->type != 0) {
            COLLISION_OFF(this);
            if (this->timer != 0) {
                InitializeAnimation(this, this->type << 3 | 5);
                InitializeAnimation(this->parent, this->parent->type << 3 | 5);
            } else {
                InitializeAnimation(this, this->type << 3 | 4);
                InitializeAnimation(this->parent, this->parent->type << 3 | 4);
            }
        }
    }
}

void VaatiTransfiguredEyeFunction0Action3(Entity* this) {
    sub_08045A28(this);
    if ((this->frame & ANIM_DONE) != 0) {
        this->action = 2;
        if (this->type != 0) {
            if (this->timer == 0) {
                this->hitType = 0x32;
            } else {
                this->parent->parent->field_0x76.HALF.LO |= (1 << this->type2);
                this->hitType = 0x31;
            }
        }
    }
}

void VaatiTransfiguredEyeFunction0Action4(Entity* this) {
    Entity* parent;

    sub_08045A28(this);
    if (this->subtimer == 0) {
        if ((this->frame & ANIM_DONE) != 0) {
            this->subtimer = 0x20;
        }
    } else {
        parent = this->parent;
        if (this->type != 0) {
            parent = parent->parent;
        }
        if ((parent->animationState < 3) && (parent->action != 3)) {
            this->action = 1;
            this->subtimer = 0;
            this->field_0x80.HALF.HI = 0;
            this->cutsceneBeh.HALF.HI = 0;
            if (this->type != 0) {
                this->hitType = 0x33;
            }
            if ((parent->field_0x74.HALF.HI >> this->type2 & 1U) != 0) {
                this->timer = 1;
            } else {
                this->timer = 0;
            }
            InitializeAnimation(this, this->type << 3 | 1);
        }
    }
}

void sub_08045A00(Entity* this) {
    const struct xy* t = &gUnk_080D18B4[this->type2];
    PositionRelative(this->parent, this, Q_16_16(t->x), Q_16_16(t->y + 3));
}

void sub_08045A28(Entity* this) {
    u32 frames;
    u32 type;

    if (this->field_0x82.HALF.LO == 0) {
        GetNextFrame(this);
    }
    frames = this->frame & 0x70;
    type = this->type;
    if (type == 0) {
        sub_08045A00(this);
        switch (this->field_0x82.HALF.HI) {
            case 0:
                switch (frames) {
                    case 0x20:
                        this->field_0x82.HALF.HI = 1;
                        ChangeObjPalette(this, 0x13e);
                        break;
                    case 0x00:
                    case 0x40:
                        this->field_0x82.HALF.HI = 2;
                        ChangeObjPalette(this, 0x13f);
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                switch (frames) {
                    case 0x10:
                        this->field_0x82.HALF.HI = type;
                        ChangeObjPalette(this, 0x13b);
                        break;
                    case 0:
                        this->field_0x82.HALF.HI = 2;
                        ChangeObjPalette(this, 0x13f);
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                switch (frames) {
                    case 0x20:
                        this->field_0x82.HALF.HI = 1;
                        ChangeObjPalette(this, 0x13e);
                        break;
                    case 0x10:
                        this->field_0x82.HALF.HI = 0;
                        ChangeObjPalette(this, 0x13b);
                        break;
                    case 0x40:
                        this->field_0x82.HALF.HI = 2;
                        ChangeObjPalette(this, 0x13f);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                switch (frames) {
                    case 0:
                        this->field_0x82.HALF.HI = 2;
                        ChangeObjPalette(this, 0x13f);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    } else {
        PositionRelative(this->parent, this, 0, Q_16_16(-1.0));
        switch (this->field_0x82.HALF.HI) {
            case 0:
                switch (this->frame & 0x70) {
                    case 0x10:
                        this->field_0x82.HALF.HI = 2;
                        ChangeObjPalette(this, 0x13b);
                        break;
                    case 0x20:
                        this->field_0x82.HALF.HI = 1;
                        ChangeObjPalette(this, 0x13e);
                        break;
                    default:
                        break;
                }
                break;
            case 1: {
                u32 temp = this->frame & 0x70;
                switch (temp) {
                    case 0:
                        this->field_0x82.HALF.HI = temp;
                        ChangeObjPalette(this, 0x13f);
                        break;
                    case 0x10:
                        this->field_0x82.HALF.HI = 2;
                        ChangeObjPalette(this, 0x13b);
                        break;
                    default:
                        break;
                }
            } break;
            case 2:
                switch (this->frame & 0x70) {
                    case 0:
                        this->field_0x82.HALF.HI = this->frame & 0x70;
                        ChangeObjPalette(this, 0x13f);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}
