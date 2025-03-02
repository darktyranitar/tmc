/**
 * @file lightManager.c
 * @ingroup Managers
 *
 * @brief Manages the light in dark rooms.
 */
#include "manager/lightManager.h"
#include "area.h"
#include "common.h"
#include "functions.h"
#include "game.h"
#include "main.h"
#include "physics.h"
#include "player.h"
#include "room.h"
#include "screen.h"

extern void sub_0801E120(void);
extern void sub_0801E154(u32);
extern u32 CheckRectOnScreen(s32, s32, u32, u32);
extern void sub_0801E160(u32, u32, u32);

bool32 sub_0805BA78();
void sub_0805BAD4();

void LightManager_Main(LightManager* this) {
    s32 sVar1;
    u32 uVar3;

    if (gArea.lightType == 0) {
        sub_0801E104();
        gScreen.lcd.displayControl &= ~(DISPCNT_BG3_ON | DISPCNT_WIN0_ON);
        DeleteThisEntity();
    }
    if (super->action == 0) {
        super->action = 1;
        super->flags |= ENT_PERSIST;
        super->timer = 17;
        this->unk20 = 0;
        SetDefaultPriority((Entity*)this, 6);
        sub_0801E120();
        sub_0801E154(super->timer);
    }
    if (gMain.substate == GAMEMAIN_UPDATE) {
        gScreen.lcd.displayControl |= DISPCNT_BG3_ON;
        sub_0805BA78();
        sub_0805BAD4();
    }
    if (gArea.lightType == 2) {
        gScreen.lcd.displayControl &= ~DISPCNT_WIN0_ON;
    } else {
        if (CheckRectOnScreen(gPlayerEntity.x.HALF.HI - gRoomControls.origin_x,
                              gPlayerEntity.y.HALF.HI - gRoomControls.origin_y, 0, 0)) {
            gScreen.lcd.displayControl |= DISPCNT_WIN0_ON;
        } else {
            gScreen.lcd.displayControl &= ~DISPCNT_WIN0_ON;
        }
        uVar3 = super->timer;
        if (((gPlayerState.flags & PL_USE_LANTERN)) && (gArea.lightType)) {
            if (uVar3 < 0x48) {
                uVar3 += 4;
                sub_0801E154(uVar3);
                this->unk20 = 0;
            } else if ((gRoomTransition.frameCount & 3) == 0) {
                super->subtimer += 0x10;
                sVar1 = gSineTable[super->subtimer];
                this->unk20 = sVar1 >> 7;
                sub_0801E154(uVar3 + this->unk20);
            }
        } else {
            this->unk20 = 0;
            if (0x11 < uVar3) {
                uVar3 -= 4;
                if (uVar3 < 0x11) {
                    uVar3 = 0x11;
                }
                sub_0801E154(uVar3);
            }
        }

        super->timer = uVar3;
        sub_0801E160(gPlayerEntity.x.HALF.HI - gRoomControls.scroll_x,
                     gPlayerEntity.y.HALF.HI - gRoomControls.scroll_y - 9 + gPlayerEntity.z.HALF.HI,
                     uVar3 + this->unk20);
    }
}

#define ABS(x) ((unsigned)(x < 0 ? -(x) : x))

bool32 sub_0805BA78() {
    u32 uVar1;
    s32 iVar1;
    s32 iVar2;

    iVar2 = (short)gArea.lightLevel;
    iVar1 = gRoomVars.lightLevel;

    if (iVar1 < 0) {
        iVar1 = 0;
    }

    if (0x100 < iVar1) {
        iVar1 = 0x100;
    }

    if (iVar2 != iVar1) {
        if (ABS(iVar1 - iVar2) <= 4) {
            iVar2 = iVar1;
        } else {
            if (iVar1 < iVar2) {
                iVar2 = iVar2 - 4;
            } else {
                if (iVar1 > iVar2) {
                    iVar2 = iVar2 + 4;
                }
            }
        }
        gArea.lightLevel = iVar2;
    } else {
        return FALSE;
    }
    return TRUE;
}

extern u16 gUnk_08108CA8[];

void sub_0805BAD4() {
    static const u16 gUnk_08108CA8[] = { 0x10,  0x10f, 0x20e, 0x30d, 0x40c, 0x50b, 0x60a, 0x709,  0x808,
                                         0x907, 0xa06, 0xb05, 0xc04, 0xd03, 0xe02, 0xf01, 0x1000, 0x00 };
    if (gArea.lightType != 0) {
        gScreen.controls.alphaBlend = gUnk_08108CA8[(gArea.lightLevel << 0x10) >> 0x14];
    }
}

void sub_0805BB00(s32 lightLevel, s32 param_2) {
    if (gArea.lightType == 0) {
        Manager* pManager = GetEmptyManager();
        if (pManager != 0) {
            pManager->kind = MANAGER;
            pManager->id = LIGHT_MANAGER;
            AppendEntityToList((Entity*)pManager, 0);
        }
    }
    MemFill16(0xf, BG_SCREEN_ADDR(0x1E), BG_SCREEN_SIZE);
    gScreen.bg3.control = 0x1e0c;
    gScreen.controls.layerFXControl = 0x3e48;
    gRoomVars.lightLevel = lightLevel;
    if (param_2) {
        gArea.lightType = 1;
    } else {
        gArea.lightType = 2;
    }
}

void sub_0805BB74(s32 lightLevel) {
    LightManager* manager;

    if (lightLevel < 0) {
        lightLevel = gRoomVars.lightLevel;
    }
    gArea.lightLevel = lightLevel;
    gRoomVars.lightLevel = gArea.lightLevel;
    manager = (LightManager*)DeepFindEntityByID(MANAGER, LIGHT_MANAGER);
    if (manager) {
        LightManager_Main(manager);
        gScreen.lcd.displayControl |= DISPCNT_BG3_ON;
        sub_0805BA78();
        sub_0805BAD4();
    }
}

bool32 UpdateLightLevel() {
    bool32 iVar1;

    iVar1 = FALSE;
    if (gArea.lightType && gRoomVars.lightLevel < (s16)gArea.lightLevel) {
        gScreen.lcd.displayControl |= DISPCNT_BG3_ON;
        iVar1 = sub_0805BA78();
        if (iVar1) {
            sub_0805BAD4();
        }
    }
    return iVar1;
}

s32 sub_0805BC04(void) {
    s32 iVar1;

    iVar1 = 0;
    if (gArea.lightType && gRoomVars.lightLevel > (short)gArea.lightLevel) {
        gScreen.lcd.displayControl |= DISPCNT_BG3_ON;
        iVar1 = sub_0805BA78();
        if (iVar1) {
            sub_0805BAD4();
        }
    }
    return iVar1;
}

void sub_0805BC4C() {
    if (gArea.lightType != 0) {
        gArea.lightType = 0;
        gScreen.lcd.displayControl &= ~(DISPCNT_BG3_ON | DISPCNT_WIN0_ON);
    }
}
