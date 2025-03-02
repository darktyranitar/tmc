#include "entity.h"
#include "collision.h"
#include "enemy.h"
#include "player.h"
#include "physics.h"
#include "functions.h"

extern void (*const V3ElectricProjectile_Functions[])(Entity*);
extern void (*const V3ElectricProjectile_Actions[])(Entity*);
static const u16 projectileSpeeds[];
static const u8 gUnk_0812A982[];
static const u8 projectileDirections[];

void V3ElectricProjectile(Entity* this) {
    V3ElectricProjectile_Functions[GetNextFunction(this)](this);
}

void V3ElectricProjectile_OnTick(Entity* this) {
    V3ElectricProjectile_Actions[this->action](this);
}

void sub_080ABFE4(Entity* this) {
    DeleteThisEntity();
}

void sub_080ABFEC(Entity* this) {
    Sound sound;
    InitializeAnimation(this, this->type + 1);

    switch (this->type) {
        case 0: {
            this->action = 1;
            this->timer = 0;
            this->subtimer = 0x7;
            this->cutsceneBeh.HALF.HI = 0x18;
            this->damage = 0x88;
            CopyPositionAndSpriteOffset(this->parent, this);
            this->z.HALF.HI -= 0x14;
            sound = SFX_149;
            break;
        }
        case 1: {
            this->action = 1;
            this->flags &= ~ENT_COLLIDE;
            this->cutsceneBeh.HALF.HI = 0x18;
            CopyPositionAndSpriteOffset(this->parent, this);
            this->z.HALF.HI -= 0x14;
            sound = SFX_149;
            break;
        }
        default: {
            this->action = 2;
            this->timer = 0;
            this->subtimer = 0xff;
            this->speed = projectileSpeeds[this->type2];
            this->damage = 0x88;
            sound = SFX_193;
            break;
        }
    }

    SoundReq(sound);
}

void V3ElectricProjectile_Action1(Entity* this) {
    if (this->parent->next == NULL) {
        DeleteThisEntity();
    }
    CopyPositionAndSpriteOffset(this->parent, this);
    this->z.HALF.HI -= 0x14;
    if (this->cutsceneBeh.HALF.HI != 0) {
        if (((--this->cutsceneBeh.HALF.HI) & 7) == 0) {
            SoundReq(SFX_149);
        }
    }
    GetNextFrame(this);
    if ((this->frame & 1) != 0) {
        if (this->type == 0) {
            this->action = 2;
            this->direction = GetFacingDirection(this, &gPlayerEntity);
            this->speed = 0x180;
            SoundReq(SFX_193);
        } else {
            this->action = 3;
            this->timer = 0x10;
        }
        this->z.HALF.HI -= 0x28;
    }
}

void V3ElectricProjectile_Action2(Entity* this) {
    u8 bVar1;
    s32 iVar2;
    u32 uVar3;

    if (this->z.HALF.HI < -6) {
        this->z.HALF.HI += 3;
    }
    ProcessMovement3(this);
    if (this->collisions != COL_NONE) {
        DeleteThisEntity();
    }
    GetNextFrame(this);
    if (IsProjectileOffScreen(this)) {
        DeleteThisEntity();
    }
    if (this->timer < 0x1e) {
        if (((++this->timer) & this->subtimer) == 0) {
            sub_08004596(this, GetFacingDirection(this, &gPlayerEntity));
        }
    }
}

void sub_080AC168(Entity* this) {
    u8 timer;
    GetNextFrame(this);
    this->z.WORD -= Q_16_16(0.5);
    timer = --this->timer;
    if (timer == 0) {
        u32 rand;
        u32 dir;
        this->action = 4;
        this->timer = 4;
        rand = Random() & 0x7;
        this->subtimer = gUnk_0812A982[rand];
        dir = GetFacingDirection(this, &gPlayerEntity);
        if (this->parent->cutsceneBeh.HALF.LO == 3) {
            dir -= projectileDirections[rand];
            this->type2 = 0;
        } else if (this->parent->cutsceneBeh.HALF.LO == 2) {
            dir -= projectileDirections[rand];
            this->type2 = 1;
        } else {
            dir -= projectileDirections[rand] >> 1;
            this->type2 = 2;
        }

        this->direction = dir & 0x1f;
    }
}

void sub_080AC200(Entity* this) {
    Entity* proj;
    GetNextFrame(this);

    if (--this->timer)
        return;

    this->timer = 0x10;
    proj = CreateProjectile(V3_ELECTRIC_PROJECTILE);

    if (proj) {
        proj->type = 2;
        proj->type2 = this->type2;
        proj->direction = this->direction;
        proj->parent = this->parent;
        CopyPosition(this, proj);
    }

    if (--this->subtimer == 0) {
        DeleteThisEntity();
    }

    if (this->parent->cutsceneBeh.HALF.LO == 3) {
        this->direction = (this->direction + 3) & 0x1f;
    } else if (this->parent->cutsceneBeh.HALF.LO == 2) {
        this->direction = (this->direction + 3) & 0x1f;
    } else {
        this->direction = (this->direction + 2) & 0x1f;
    }
}

void (*const V3ElectricProjectile_Functions[])(Entity*) = {
    V3ElectricProjectile_OnTick, sub_080ABFE4, DeleteEntity, DeleteEntity, DeleteEntity,
};
void (*const V3ElectricProjectile_Actions[])(Entity*) = {
    sub_080ABFEC, V3ElectricProjectile_Action1, V3ElectricProjectile_Action2, sub_080AC168, sub_080AC200,
};
static const u16 projectileSpeeds[] = { 352, 480, 480 };
static const u8 gUnk_0812A982[] = {
    5, 6, 7, 8, 5, 6, 7, 6,
};
static const u8 projectileDirections[] = {
    6, 9, 9, 12, 6, 9, 9, 9, 0, 0,
};
