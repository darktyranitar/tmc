/**
 * @file weatherChangeManager.c
 * @ingroup Managers
 *
 * @brief Weather change on top of Mount Crenel.
 */
#include "manager/weatherChangeManager.h"
#include "area.h"
#include "asm.h"
#include "common.h"
#include "fileselect.h"
#include "functions.h"
#include "room.h"
#include "screen.h"
#include "sound.h"

void sub_080595E4(WeatherChangeManager*);
void sub_08059608(WeatherChangeManager*);
void sub_08059690(WeatherChangeManager*);
void sub_080596E0(WeatherChangeManager*);
u32 sub_08059844(void);
u32 sub_0805986C(void);
void sub_08059894(const u16*, const u16*, u32);
u32 sub_080598F8(u32, u32, u32);
void sub_08059960(const u16*, const u16*, u16*, u8);

const u8 gUnk_08108390[6] = {
    0x0F, 0x1E, 0x2D, 0x3C, 0x01, 0x01,
};

extern u16 gUnk_020176E0[];
extern u8 gUnk_02017700[];

extern const u16 gPalette_549[];

void WeatherChangeManager_Main(WeatherChangeManager* this) {
    if (super->action == 0) {
        super->action = 1;
        this->unk_21 = 0;
        this->unk_23 = 0;
        if (sub_0805986C()) {
            this->unk_20 = 1;
            this->unk_22 = 2;
            gMapTop.bgSettings = 0;
        } else {
            this->unk_20 = 0x1F;
            this->unk_22 = 5;
        }
        gRoomVars.unk_10[0] = 0xFF;
        RegisterTransitionManager(this, sub_080595E4, 0);
    }
    sub_08059608(this);
    sub_08059690(this);
    sub_080596E0(this);
}

void sub_080595E4(WeatherChangeManager* this) {
    gRoomVars.unk_10[0] = 0xFF;
    sub_08059690(this);
    sub_080596E0(this);
    sub_0805B4D0(0);
}

void sub_08059608(WeatherChangeManager* this) {
    if (this->unk_23) {
        if (!--this->unk_23) {
            gArea.bgm = gArea.queued_bgm;
            SoundReq(gArea.bgm);
        }
        return;
    }
    if (sub_0805986C()) {
        if (gArea.queued_bgm != 0x1E) {
            gArea.queued_bgm = 0x1E;
            this->unk_23 = 0x78;
            SoundReq(SONG_FADE_OUT_BGM);
        }
        return;
    }
    if (gArea.queued_bgm != 0x37) {
        gArea.queued_bgm = 0x37;
        this->unk_23 = 0x78;
        SoundReq(SONG_FADE_OUT_BGM);
    }
}

void sub_08059690(WeatherChangeManager* this) {
    if (sub_08059844()) {
        if (this->unk_20 == 0)
            return;
        sub_08059894(gPalette_549, gPalette_549 + 0xD0, this->unk_20);
        this->unk_20--;
    } else {
        if (this->unk_20 > 0x1F)
            return;
        sub_08059894(gPalette_549, gPalette_549 + 0xD0, this->unk_20);
        this->unk_20++;
    }
}

void sub_080596E0(WeatherChangeManager* this) {
    if ((gRoomTransition.frameCount & 7) == 0) {
        gScreen.bg1.xOffset += 8;
        gScreen.bg1.xOffset &= 0x1F;
    }
    if (sub_0805986C()) {
        if (this->unk_21 == 0 && this->unk_22 != 2) {
            this->unk_21 = 1;
            this->unk_22 = 3;
            super->timer = gUnk_08108390[3];
            gMapTop.bgSettings = 0;
        }
    } else {
        if (this->unk_21 == 0 && this->unk_22 != 5) {
            this->unk_21 = 2;
            super->timer = gUnk_08108390[this->unk_22];
        }
    }
    switch (this->unk_21) {
        case 1:
            if (--super->timer == 0) {
                super->timer = gUnk_08108390[--this->unk_22];
                if (this->unk_22 == 2) {
                    this->unk_21 = 0;
                }
            }
            break;
        case 2:
            if (--super->timer == 0) {
                super->timer = gUnk_08108390[++this->unk_22];
                if (this->unk_22 == 5) {
                    this->unk_21 = 0;
                }
            }
            break;
    }
    if (gRoomVars.unk_10[0] != this->unk_22) {
        gRoomVars.unk_10[0] = this->unk_22;
        switch (this->unk_22) {
            case 0 ... 3:
                LoadGfxGroup(this->unk_22 + 0x2B);
                break;
            case 4:
                MemClear(gBG3Buffer, 0x800);
                LoadResourceAsync(gBG3Buffer, 0x600e800, 0x800);
                break;
            case 5:
                gMapTop.bgSettings = &gScreen.bg1;
                gScreen.lcd.displayControl |= 0x200;
                break;
        }
    }
}

u32 sub_08059844(void) {
    return gPlayerEntity.x.HALF.HI - gRoomControls.origin_x > gRoomControls.width >> 1;
}

u32 sub_0805986C(void) {
    return gPlayerEntity.x.HALF.HI - gRoomControls.origin_x > 0x200;
}

void sub_08059894(const u16* unk1, const u16* unk2, u32 unk3) {
    const u16* tmp1;
    const u16* tmp2;
    u16* tmp3;
    u32 tmp4;
    u32 i;
    tmp1 = unk1;
    tmp2 = unk2;
    tmp3 = gUnk_020176E0;
    for (i = 0; i < 13; i++) {
        sub_08059960(tmp1, tmp2, tmp3, unk3);
        tmp1 += 0x10;
        tmp2 += 0x10;
        tmp3 += 0x10;
    }
    MemCopy(gUnk_02017700, gUnk_02017700 + 0x240, 0x20);
    gUsedPalettes |= 0x207ffc;
}

u32 sub_080598F8(u32 unk1, u32 unk2, u32 unk3) {
    u32 tmp1, tmp2, tmp3;
    u32 tmp4, tmp5, tmp6;

    tmp1 = (unk1 & 0x1F) << 8;
    tmp1 = (tmp1 * unk3) >> 5;
    tmp4 = (unk2 & 0x1F) << 8;
    tmp4 = (tmp4 * (0x20 - unk3)) >> 5;
    tmp1 = (tmp1 + tmp4) >> 8;

    tmp2 = (unk1 & 0x3E0) << 3;
    tmp2 = (tmp2 * unk3) >> 5;
    tmp5 = (unk2 & 0x3E0) << 3;
    tmp5 = (tmp5 * (0x20 - unk3)) >> 5;
    tmp2 = (tmp2 + tmp5) >> 8;

    tmp3 = (unk1 & 0x7C00) >> 2;
    tmp3 = (tmp3 * unk3) >> 5;
    tmp6 = (unk2 & 0x7C00) >> 2;
    tmp6 = (tmp6 * (0x20 - unk3)) >> 5;
    tmp3 = (tmp3 + tmp6) >> 8;

    return tmp1 | (tmp2 << 5) | (tmp3 << 10);
}

void sub_08059960(const u16* unk1, const u16* unk2, u16* unk3, u8 unk4) {
    u32 i;
    for (i = 0; i < 0x10; i++) {
        *unk3++ = sub_080598F8(*unk1++, *unk2++, unk4);
    }
}

void sub_08059994(void) {
    if (sub_0805986C()) {
        LoadPaletteGroup(0x5B);
        gArea.queued_bgm = 0x1E;
    }
}
