/**
 * @file hyruleTownBellManager.c
 * @ingroup Managers
 *
 * @brief Spawns the heart piece if the player jumps against the bell in Hyrule Town.
 */
#include "manager/hyruleTownBellManager.h"
#include "object.h"
#include "player.h"
#include "room.h"
#include "sound.h"

void HyruleTownBellManager_Main(HyruleTownBellManager* this) {
    RoomControls* roomControls = &gRoomControls;
    u32 a = roomControls->origin_x + 0x1f8;
    u32 x = (a - gPlayerEntity.x.HALF.HI) + 0x10;
    u32 b = roomControls->origin_y + 0x140;
    u32 y = (b - gPlayerEntity.y.HALF.HI) + 0x10;
    if (super->action == 0) {
        if (x < 0x20 && y < 0x20 && gPlayerEntity.z.HALF.HI < -0x18 && gPlayerState.framestate == PL_STATE_CAPE) {
            super->action++;
            super->timer = 0x5a;
            SoundReq(SFX_10A);
        }
    } else {
        if (--super->timer == 0) {
            Entity* object = CreateObject(OBJECT_96, 1, 0);
            if (object != NULL) {
                object->x.HALF.HI = roomControls->origin_x + 0x1f8;
                object->y.HALF.HI = roomControls->origin_y + 0x140;
                object->z.HALF.HI = 0xffe8;
            }
            DeleteThisEntity();
        }
    }
}
