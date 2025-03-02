#include "entity.h"
#include "asm.h"
#include "physics.h"
#include "functions.h"
#include "projectile.h"
#include "hitbox.h"
#include "collision.h"

extern u32 sub_080644C8(Entity*);
extern u8 gUnk_02027EB4[];

extern const u8 gUnk_081299C8[];

void GuardLineOfSight(Entity* this) {
    Entity* entity;
    u8 tmp;

    if (this->type == 0) {
        if (this->action == 0) {
            this->action = 1;
            this->timer = Random();
            this->spriteSettings.draw = 0;
        }
        if (this->contactFlags == 0x80) {
            if (this->parent != NULL) {
                this->parent->type = 0xff;
            }
            DeleteThisEntity();
        }
        CopyPosition(this->parent, this);
        if (this->subtimer != 0) {
            this->subtimer -= 1;
        } else {
            if (sub_080644C8(this) != 0) {
                if (((this->timer++) & 3) == 0) {
                    entity = CreateProjectile(GUARD_LINE_OF_SIGHT);
                    if (entity != NULL) {
                        entity->type = 1;
                        tmp = this->parent->knockbackDirection;
                        entity->direction = (gUnk_081299C8[(this->timer >> 2 & 7)] + (tmp << 3)) & 0x1f;
                        entity->parent = this->parent;
                        CopyPosition(this, entity);
                    }
                }
            }
        }
    } else {
        if (this->action == 0) {
            this->action = 1;
            this->timer = 0x12;
            this->spriteSettings.draw = 0;
            this->speed = 0x800;
            this->hitbox = (Hitbox*)&gUnk_080FD1E4;
            InitializeAnimation(this, 0);
        }
        if (this->contactFlags == 0x80) {
            if (this->parent != NULL) {
                this->parent->type = 0xff;
            }
            DeleteThisEntity();
        }
        if (--this->timer == 0) {
            DeleteThisEntity();
        }
        LinearMoveUpdate(this);
        if (IsTileCollision(gUnk_02027EB4, this->x.HALF.HI, this->y.HALF.HI, 2)) {
            DeleteThisEntity();
        }
    }
}

const u8 gUnk_081299C8[] = {
    0, 254, 0, 254, 0, 2, 0, 2,
};
