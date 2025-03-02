#include "entity.h"
#include "collision.h"
#include "enemy.h"
#include "functions.h"

extern void (*const CannonballProjectile_Functions[])(Entity*);
extern void (*const CannonballProjectile_Actions[])(Entity*);

bool32 sub_080AB5F4(Entity*);
bool32 sub_080AB634(Entity*);

void CannonballProjectile(Entity* this) {
    CannonballProjectile_Functions[GetNextFunction(this)](this);
}

void CannonballProjectile_OnTick(Entity* this) {
    CannonballProjectile_Actions[this->action](this);
}

void sub_080AB544(Entity* this) {
    u32 tmp;

    if (this->iframes < -4) {
        this->action = 2;
        this->direction = this->knockbackDirection;
        tmp = (this->type ^ 2) << 3;
        if (this->direction - tmp + 1 < 3) {
            this->direction = tmp;
        }
        this->speed = 0x280;
    }
}

void CannonballProjectile_Init(Entity* this) {
    this->action = 1;
    this->direction = this->type << 3;
    this->z.HALF.HI = 0xfffc;
    InitializeAnimation(this, this->type);
}

void CannonballProjectile_Action1(Entity* this) {
    GetNextFrame(this);
    if (ProcessMovement3(this) == 0) {
        CreateFx(this, FX_DEATH, 0);
        DeleteThisEntity();
    }
    sub_080AB5F4(this);
}

void CannonballProjectile_Action2(Entity* this) {
    GetNextFrame(this);
    ProcessMovement3(this);
    if ((sub_080AB634(this) == 0) && (this->collisions != COL_NONE)) {
        CreateFx(this, FX_DEATH, 0);
        DeleteThisEntity();
    }
}

bool32 sub_080AB5F4(Entity* this) {
    switch (sub_080043E8(this)) {
        case 1:
            CreateItemOnGround(this);
            return TRUE;
        case 2:
            sub_080043A8(this);
            return TRUE;
        case 3:
            CreateChestSpawner(this);
            return TRUE;
    }
    return FALSE;
}

bool32 sub_080AB634(Entity* this) {
    Entity** entities = ((Entity**)&this->parent->zVelocity);
    u32 i;
    for (i = 0; i <= 3; ++i) {
        if (entities[i] != NULL && (IsColliding(this, entities[i]) != 0)) {
            if (entities[i]->action < 3) {
                entities[i]->action = 3;
                entities[i]->timer = 0x1e;
                entities[i]->spriteSettings.draw = 0;
                CreateFx(entities[i], FX_WHITE_ROCK, 0);
            }
            DeleteEntity(this);
            return TRUE;
        }
    }
    return FALSE;
}

void (*const CannonballProjectile_Functions[])(Entity*) = {
    CannonballProjectile_OnTick, sub_080AB544, DeleteEntity, DeleteEntity, DeleteEntity,
};
void (*const CannonballProjectile_Actions[])(Entity*) = {
    CannonballProjectile_Init,
    CannonballProjectile_Action1,
    CannonballProjectile_Action2,
};
