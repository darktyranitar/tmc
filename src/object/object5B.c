/**
 * @file object5B.c
 * @ingroup Objects
 *
 * @brief Object5B object
 */

#define NENT_DEPRECATED
#include "global.h"
#include "object.h"
#include "functions.h"

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u8 unk_68[0x1a];
    /*0x82*/ u16 unk_82;
    /*0x84*/ ScriptExecutionContext* unk_84;
} Object5BEntity;

void sub_080928C8(Object5BEntity*);
void nullsub_119(Object5BEntity*);
void sub_08092930(Object5BEntity*);
void sub_08092940(Object5BEntity*);
void sub_08092958(Object5BEntity*, ScriptExecutionContext*);

void Object5B(Object5BEntity* this) {
    static void (*const gUnk_08122794[])(Object5BEntity*) = {
        sub_080928C8,
        nullsub_119,
    };
    static void (*const gUnk_0812279C[])(Object5BEntity*) = {
        sub_08092930,
        sub_08092940,
    };
    if ((super->flags & 2) != 0) {
        gUnk_0812279C[super->action](this);
    } else {
        gUnk_08122794[super->action](this);
    }
}

void sub_080928C8(Object5BEntity* this) {
    super->action = 1;
    super->spriteSettings.draw = 1;
    super->frameIndex = super->type;
    super->spriteRendering.b3 = 3;
    super->spritePriority.b0 = 6;
    super->spriteOrientation.flipY = 2;
    switch (super->type) {
        case 2:
            CreateObjectWithParent(super, OBJECT_5B, 4, 0);
            break;
        case 4:
            super->spritePriority.b0 = 7;
            break;
    }
}

void nullsub_119(Object5BEntity* this) {
}

void sub_08092930(Object5BEntity* this) {
    sub_080928C8(this);
    this->unk_82 = 0;
}

void sub_08092940(Object5BEntity* this) {
    ExecuteScript(super, this->unk_84);
    sub_08092958(this, this->unk_84);
}

void sub_08092958(Object5BEntity* this, ScriptExecutionContext* context) {
    u32 tmp;
    while (context->postScriptActions != 0) {
        tmp = (~context->postScriptActions + 1) & context->postScriptActions;
        context->postScriptActions = context->postScriptActions ^ tmp;
        switch (tmp) {
            case 1:
                super->frameIndex = 0;
                break;
            case 2:
                super->frameIndex = context->intVariable;
                break;
        }
    }
}
