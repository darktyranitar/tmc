/**
 * @file object12.c
 * @ingroup Objects
 *
 * @brief Object12 object
 */

#define NENT_DEPRECATED
#include "global.h"
#include "object.h"
#include "functions.h"
#include "screen.h"

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u8 unk_68[30];
    /*0x86*/ u16 unk_86;
} Object12Entity;

void Object12_Init(Object12Entity*);
void Object12_Action1(Object12Entity*);
void Object12_Action2(Object12Entity*);
void Object12_Action3(Object12Entity*);
void Object12_Action4(Object12Entity*);
void sub_080850FC(Object12Entity*);

void Object12(Object12Entity* this) {
    static void (*const Object12_Actions[])(Object12Entity*) = {
        Object12_Init, Object12_Action1, Object12_Action2, Object12_Action3, Object12_Action4,
    };
    Object12_Actions[super->action](this);
}

void Object12_Init(Object12Entity* this) {
    if (super->type == 0) {
        if (CheckFlags(this->unk_86)) {
            DeleteThisEntity();
        }
        super->action = 1;
        super->spritePriority.b0 = 7;
        sub_080850FC(this);
    } else {
        super->action = 2;
        super->timer = 0xf0;
        super->speed = 0x80;
        super->direction = 0x18;
    }
    super->frameIndex = 0;
}

void Object12_Action1(Object12Entity* this) {
}

void Object12_Action2(Object12Entity* this) {
    u32 tmp;
    u32 tmp2;
    if (--super->timer == 0) {
        super->action = 3;
        super->timer = 0x1e;
        super->spriteOffsetY = 4;
        gScreen.lcd.displayControl |= 0x2000;
        gScreen.controls.windowInsideControl = 0x1f;
        gScreen.controls.windowOutsideControl = 0xf;
        tmp2 = super->x.HALF.HI;
        tmp = gRoomControls.scroll_x;
        tmp2 = tmp2 - tmp;
        gScreen.controls.window0HorizontalDimensions = (((tmp2 - 0x18) & 0xff) << 8) | ((tmp2 + 0x18) & 0xff);
        tmp2 = super->y.HALF.HI;
        tmp = gRoomControls.scroll_y;
        tmp2 = tmp2 - tmp;
        gScreen.controls.window0VerticalDimensions = (((tmp2 - 0x18) & 0xff) << 8) | ((tmp2 + 0x18) & 0xff);
    }
}

void Object12_Action3(Object12Entity* this) {
    if (--super->timer == 0) {
        super->action = 4;
        super->timer = 0x60;
    }
}

void Object12_Action4(Object12Entity* this) {
    LinearMoveUpdate(super);
    if (--super->timer == 0) {
        gScreen.lcd.displayControl &= 0xdfff;
        DeleteEntity(super);
    }
}

void sub_080850FC(Object12Entity* this) {
    u32 position = COORD_TO_TILE(super);
    u32 layer = super->collisionLayer;
    SetTile(0x403d, position - 0x41, layer);
    SetTile(0x403d, position - 0x40, layer);
    SetTile(0x403d, position - 0x3f, layer);
    SetTile(0x403d, position - 1, layer);
    SetTile(0x403d, position, layer);
    SetTile(0x403d, position + 1, layer);
    SetTile(0x403d, position + 0x3f, layer);
    SetTile(0x403d, position + 0x40, layer);
    SetTile(0x403d, position + 0x41, layer);
}
