#include "entity.h"
#include "asm.h"
#include "object.h"
#include "functions.h"
#include "effects.h"

void sub_08089874(Entity* this);
void sub_08089944(Entity* this);
void sub_08089A7C(Entity* this);
void sub_08089AE0(Entity* this);

void AmbientClouds(Entity* this) {
    static void (*const actionFuncs[])(Entity*) = {
        sub_08089874,
        sub_08089944,
        sub_08089A7C,
        sub_08089AE0,
    };
    actionFuncs[this->action](this);
    UpdateAnimationVariableFrames(this, (Random() & 1) + 1);
}

void sub_08089874(Entity* this) {
    Entity* pEVar2;

#ifndef EU
    if ((this->flags & ENT_DID_INIT) != 0) {
#endif
        this->collisionLayer = 3;
        if (this->type2 == 0) {
            if (this->type == 0x80) {
                this->action = 3;
                this->spriteRendering.b3 = 3;
                InitializeAnimation(this, 0);
                sub_08089AE0(this);
                return;
            } else {
                this->parent = NULL;
                CreateObjectWithParent(this, AMBIENT_CLOUDS, 0, 0xff);
                for (; this->type != 0; --this->type) {
                    pEVar2 = CreateObjectWithParent(this, AMBIENT_CLOUDS, 0, this->type);
                    this->child = pEVar2;
                    if (pEVar2 != NULL) {
                        pEVar2->parent = this->parent;
                        if (this->parent != NULL) {
                            this->parent->child = this->child;
                        }
                        this->parent = this->child;
                    }
                }
            }
            DeleteThisEntity();
        } else {
            this->action = 1;
            if (this->parent == NULL) {
                InitializeAnimation(this, 0);
            } else {
                InitializeAnimation(this, 1);
            }
            if (this->type2 == 0xff) {
                this->collisionLayer = 1;
                ResolveCollisionLayer(this);
                ChangeObjPalette(this, 0x15);
            } else {
                this->z.HALF.HI = this->type2 * -0x24;
            }
        }
#ifndef EU
    }
#endif
}

void sub_08089944(Entity* this) {
    int iVar1;
    Entity* pEVar2;

    if (this->type2 == 0xff) {
        this->spritePriority.b0 = 7;
        this->spriteRendering.b3 = 3;
    } else {
        this->spriteOrientation.flipY = 1;
        this->spriteRendering.b3 = 0;
        if ((this->type2 == 1) || (this->child->action == 2)) {
            if (gPlayerEntity.z.HALF.HI < -0x24)
                this->timer = 1;
            else
                this->timer = 0;
            this->y.HALF.HI += (this->type2 - 1) * -0x24;
            iVar1 = EntityInRectRadius(this, &gPlayerEntity, 0xf, 0xf);
            if ((iVar1 != 0) && (this->timer != 0)) {
                this->action = 2;
                this->spriteOrientation.flipY = 2;
                this->spriteRendering.b3 = 3;
                if (this->type2 != 1) {
                    this->child->action = 1;
                }
                gPlayerState.field_0x14 = 1;
                gPlayerEntity.y.HALF.HI -= 0x24;
                gPlayerEntity.z.HALF.HI += 0x24;
                sub_0807AA80(&gPlayerEntity);
                if (this->subtimer == 0) {
                    pEVar2 = CreateFx(&gPlayerEntity, FX_DEATH, 0);
                    if (pEVar2 != NULL) {
                        pEVar2->x.HALF.HI += 8;
                    }
                    pEVar2 = CreateFx(&gPlayerEntity, FX_DEATH, 0);
                    if (pEVar2 != NULL) {
                        pEVar2->x.HALF.HI -= 8;
                    }
                    pEVar2 = CreateFx(&gPlayerEntity, FX_DEATH, 0);
                    if (pEVar2 != NULL) {
                        pEVar2->y.HALF.HI += 8;
                    }
                    pEVar2 = CreateFx(&gPlayerEntity, FX_DEATH, 0);
                    if (pEVar2 != NULL) {
                        pEVar2->y.HALF.HI -= 8;
                    }
                }
            }
            this->y.HALF.HI += (this->type2 - 1) * 0x24;
            this->subtimer = this->timer;
        }
    }
}

void sub_08089A7C(Entity* this) {
    this->y.HALF.HI += this->type2 * -0x24;
    if (EntityInRectRadius(this, &gPlayerEntity, 0xf, 0xf)) {
        gPlayerState.field_0x14 = 1;
        gPlayerState.flags |= PL_FLAGS2;
    } else {
        this->action = 1;
        gPlayerEntity.z.HALF_U.HI += this->z.HALF_U.HI;
        gPlayerEntity.y.HALF_U.HI -= this->z.HALF_U.HI;
        gPlayerEntity.collisionLayer = 1;
    }
    this->y.HALF.HI += this->type2 * 0x24;
}

void sub_08089AE0(Entity* this) {
    if (EntityInRectRadius(this, &gPlayerEntity, 0xf, 0xf)) {
        gPlayerState.field_0x14 = 1;
    }
}
