#include "global.h"
#include "sound.h"
#include "entity.h"
#include "save.h"
#include "script.h"
#include "effects.h"
#include "functions.h"

void Windcrest(Entity* this) {
    if (this->action == 0) {
        this->action++;
        this->frameIndex = 0;
        sub_0807DD64(this);
    }
    ExecuteScriptForEntity(this, NULL);
    HandleEntity0x82Actions(this);
}

void sub_080A2124(Entity* this) {
    static const u8 gUnk_08125010[] = { 0, 0, 12, 12 };
    sub_08078850(this, 1, 0xe, gUnk_08125010);
}

void Windcrest_Unlock(Entity* this) {
    SoundReq(SFX_SECRET);
    gSave.windcrests = gSave.windcrests | 1 << (this->type2 + 0x18);
    CreateFx(this, FX_GIANT_EXPLOSION, 0);
}
