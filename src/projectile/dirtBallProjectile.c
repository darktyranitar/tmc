#include "sound.h"
#include "entity.h"
#include "enemy.h"
#include "player.h"
#include "physics.h"
#include "functions.h"

extern void (*const DirtBallProjectile_Functions[])(Entity*);
extern void (*const DirtBallProjectile_Actions[])(Entity*);
extern const Hitbox3D gUnk_08129764;

void DirtBallProjectile(Entity* this) {
    DirtBallProjectile_Functions[GetNextFunction(this)](this);
}

void DirtBallProjectile_OnTick(Entity* this) {
    if (this->type == 1) {
        if (this->child == NULL) {
            DeleteThisEntity();
        }
        if (this->child->next == NULL) {
            DeleteThisEntity();
        }
    }
    DirtBallProjectile_Actions[this->action](this);
}

void sub_080A881C(Entity* this) {
    this->knockbackSpeed = 0;
    if (this->type == 0) {
        this->parent->child = NULL;
        if (this->contactFlags == 0x80) {
            gPlayerState.hurtBlinkSpeed = 0xf0;
            ModHealth(-2);
        }
        DeleteThisEntity();
    } else {
        if (this->action < 2) {
            this->action = 2;
            this->parent->field_0x82.HALF.HI = 0xc0;
        }
    }
}

void DirtBallProjectile_Init(Entity* this) {
    this->action = 1;
    this->subAction = 0;
    this->spriteSettings.shadow = 1;
    this->zVelocity = Q_16_16(0.5);
    this->hitbox = (Hitbox*)&gUnk_08129764;
    this->collisionFlags |= 0x10;
    switch (this->type) {
        case 0:
            InitializeAnimation(this, 0);
            break;
        case 1:
            this->timer = 0;
            this->subtimer = 0;
            break;
        case 2:
            InitializeAnimation(this, 5);
            break;
    }
}

void DirtBallProjectile_Action1(Entity* this) {
    Entity* entity;
    Entity* parent;

    parent = this->parent;
    if (parent == NULL) {
        this->action = 2;
    }
    if (parent->next == NULL) {
        this->action = 2;
    }
    PositionRelative(parent, this, 0, Q_16_16(-1.0));
    switch (this->type) {
        case 0:
            this->z.HALF.HI += Q_8_8(1.0 / 16.0);
            break;
        case 1:
            this->z.HALF.HI += Q_8_8(1.0 / 16.0 - 1.0 / 128.0);
            FreeCarryEntity(this->child);
            CopyPosition(this, this->child);
            if ((0xf < (u8)(this->timer++ + 1)) && (entity = this->child, entity->timer == 0)) {
                if ((this->timer & 2) != 0) {
                    entity->subtimer += 1;
                }
                if ((this->child->subtimer < 0x20) && ((this->child->subtimer & 3) == 3)) {
                    parent->field_0x82.HALF.HI = 0xc0;
                    this->action = 2;
                }
            }
            break;
        case 2:
            this->z.HALF.HI += Q_8_8(1.0 / 16.0 - 1.0 / 128.0);
            if (EntityInRectRadius(this, &gPlayerEntity, 0xe, 0xe) != 0) {
                this->action = 2;
                parent->field_0x82.HALF.HI = 0xc0;
            }
            break;
    }
}

void DirtBallProjectile_Action2(Entity* this) {
    u8 bVar1;
    u32 uVar2;
    u32 tmp;
    Entity* entity;

    if (this->type == 1) {
        entity = this->child;
        if (entity == NULL) {
            DeleteThisEntity();
        }
        if (entity->next == NULL) {
            DeleteThisEntity();
        }
        FreeCarryEntity(entity);
        CopyPosition(this, entity);
    }
    if (sub_080044EC(this, 0x2800) != 1) {
        return;
    }

    tmp = sub_080043E8(this);
    if (tmp != 0) {
        switch (tmp) {
            case 2:
                CreateFx(this, FX_WATER_SPLASH, 0);
                break;
            case 1:
                CreateFx(this, FX_FALL_DOWN, 0);
                break;
            case 3:
                CreateFx(this, FX_LAVA_SPLASH, 0);
                break;
        }
        DeleteThisEntity();
    }

    switch (this->type) {
        case 0:
            InitializeAnimation(this, 1);
            EnqueueSFX(SFX_WATER_SPLASH);
            this->action = 3;
            return;
        case 2:
            entity = CreateFx(this, FX_POT_SHATTER, 0x80);
            if (entity != NULL) {
                entity->parent = NULL;
            }
        case 1:
            DeleteEntity(this);
            break;
    }
}

void DirtBallProjectile_Action3(Entity* this) {
    GetNextFrame(this);
    if ((this->frame & ANIM_DONE) != 0) {
        DeleteEntity(this);
    }
}

void (*const DirtBallProjectile_Functions[])(Entity*) = {
    DirtBallProjectile_OnTick, sub_080A881C, DeleteEntity, DeleteEntity, DeleteEntity,
};
void (*const DirtBallProjectile_Actions[])(Entity*) = {
    DirtBallProjectile_Init,
    DirtBallProjectile_Action1,
    DirtBallProjectile_Action2,
    DirtBallProjectile_Action3,
};
const Hitbox3D gUnk_08129764 = { 0, -3, { 5, 3, 3, 5 }, 6, 6, 10, { 0, 0, 0 } };
