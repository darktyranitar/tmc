#ifndef ROOM_H
#define ROOM_H

#include "global.h"
#include "entity.h"
#include "droptables.h"

enum RoomTransition {
    TRANSITION_DEFAULT,
    TRANSITION_CUT,
    TRANSITION_FADE_WHITE_SLOW,
    TRANSITION_3,
    TRANSITION_FADE_BLACK_SLOW,
    TRANSITION_FADE_BLACK,
    TRANSITION_FADE_BLACK_FAST,
    TRANSITION_7,
    TRANSITION_FADE_WHITE_FAST,
    TRANSITION_CUT_FAST,
};

enum RoomReloadType {
    RELOAD_ALL = 1,
    RELOAD_ENTITIES = 2,
};

typedef struct {
    /*0x00*/ u16 reload_flags;
    /*0x02*/ u8 unk3;
    /*0x03*/ u8 unk4;
    /*0x04*/ u8 area;
    /*0x05*/ u8 room;
    /*0x06*/ u16 origin_x;
    /*0x08*/ u16 origin_y;
    /*0x0A*/ s16 scroll_x;
    /*0x0C*/ s16 scroll_y;
    /*0x0E*/ u8 unk5;
    /*0x0F*/ u8 scroll_flags; // 0x2 = ??, 0x4 = camera scrolling
    /*0x10*/ u8 scroll_direction;
    /*0x11*/ s8 oam_offset_x;
    /*0x12*/ s8 oam_offset_y;
    /*0x13*/ u8 unk13;
    /*0x14*/ u8 shake_magnitude;
    /*0x15*/ u8 unk7;
    /*0x16*/ u16 shake_duration;
    /*0x18*/ u16 filler2[3];
    /*0x1E*/ u16 width;
    /*0x20*/ u16 height;
    /*0x22*/ u16 filler3;
    /*0x24*/ s8 aff_x;
    /*0x25*/ s8 aff_y;
    /*0x26*/ u8 filler26[2];
    /*0x28*/ union SplitWord bg3OffsetX;
    /*0x2C*/ union SplitWord bg3OffsetY;
    /*0x30*/ Entity* camera_target;
    /*0x34*/ u32 unk_34;
} RoomControls;
extern RoomControls gRoomControls;

typedef struct {
    /* 0x00 */ u8 field_0x0;
    /* 0x01 */ u8 filler_0x1;
    /* 0x02 */ u8 field_0x2;
    /* 0x03 */ u8 field_0x3;
    /* 0x04 */ u8 field_0x4;
    /* 0x05 */ u8 filler1[1];
    /* 0x06 */ u8 shopItemType;
    /* 0x07 */ u8 shopItemType2;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0a */ u8 unk2;
    /* 0x0b */ u8 filler2;
    /* 0x0c */ s16 lightLevel;
    /* 0x0e */ u16 unk_0e;
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ u32 flags;
    /* 0x18 */ u32 unk3;
    /* 0x1c */ u8 filler4[44];
    /* 0x48 */ Droptable currentAreaDroptable;
    /* 0x68 */ u32 animFlags;
    /* 0x6c */ void* field_0x6c[8];
    /* 0x8c */ void* field_0x8c[8];
    /* 0xac */ Entity* entities[8];
} RoomVars;
static_assert(sizeof(RoomVars) == 0xCC);
extern RoomVars gRoomVars;

typedef struct {
    u8 area;
    u8 room;
    u16 unk_02;
    u32 unk_04;
} RoomMemory;

extern RoomMemory* gUnk_020354B0;
extern RoomMemory gRoomMemory[];

// Packets used to store which entities to load in a room
typedef struct {
    u8 kind;
    u8 flags;
    u8 id;
    u8 type;
    u32 type2;
    u16 xPos;
    u16 yPos;
    u32 spritePtr;
} EntityData;

typedef struct {
    u16 tilePos;
    u16 field_0x2;
    u8 room;
    u8 animationState;
    u8 field_0x6;
    u8 field_0x7;
} struct_030010EC;

typedef struct {
    u16 data[32];
    u16 field_0xac;
    u16 field_0xae;
} struct_0300110C;

// Status of the player's positioning within the scene.
typedef struct {
    /* 0x00 */ u8 area_next;
    /* 0x01 */ u8 room_next;
    /* 0x02 */ u8 start_anim;
    /* 0x03 */ u8 spawn_type;
    /* 0x04 */ s16 start_pos_x;
    /* 0x06 */ s16 start_pos_y;
    /* 0x08 */ u8 layer;
    /* 0x09 */ u8 field_0x15;
    /* 0x0a */ u8 dungeon_area;
    /* 0x0b */ u8 dungeon_room;
    /* 0x0c */ s16 dungeon_x;
    /* 0x0e */ s16 dungeon_y;
    /* 0x10 */ u16 dungeon_map_x;
    /* 0x12 */ u16 dungeon_map_y;
    /* 0x14 */ u16 overworld_map_x;
    /* 0x16 */ u16 overworld_map_y;
    /* 0x18 */ u8 field_0x24[8];
} PlayerRoomStatus;
static_assert(sizeof(PlayerRoomStatus) == 0x20);

typedef struct {
    /* 0x00 */ s32 frameCount; // regular frame count? does anything reset it?
    /* 0x04 */ u8 field_0x4[0x2];
    /* 0x06 */ u16 field_0x6;
    /* 0x08 */ bool8 transitioningOut;
    /* 0x09 */ u8 type;        // transition when changing areas
    /* 0x0a */ u16 stairs_idx; // seems to be a tile type
    /* 0x0c */ PlayerRoomStatus player_status;
    /* 0x2c */ u8 entity_update_type; // differentiates entity priority on kinstone menu?
    /* 0x2d */ u8 field_0x2c[0x8];
    /* 0x35 */ u8 hint_height;
    /* 0x36 */ u16 hint_idx;
    /* 0x38 */ u8 field_0x38;
    /* 0x39 */ u8 field_0x39;
    /* 0x3a */ u8 field_0x3a;
    /* 0x3b */ u8 field_0x3b;
    /* 0x3c */ u8 field_0x3c;
    /* 0x3d */ u8 field_0x3d;
    /* 0x3e */ u16 field_0x3e;
    /* 0x40 */ u16 hurtType;
    /* 0x42 */ u16 field_0x42;
    /* 0x44 */ u16 field_0x44;
    /* 0x46 */ u16 field_0x46;
    /* 0x48 */ u16 field_0x48;
    /* 0x4a */ u16 field_0x4a;
    /* 0x4c */ struct_030010EC minecart_data[4];
    /* 0x6c */ struct_0300110C armos_data;
} RoomTransition;
static_assert(sizeof(RoomTransition) == 0xB0);
extern RoomTransition gRoomTransition;

typedef struct {
    u16 type;
    u8 field_0x2[4];
    s16 playerXPos;
    s16 playerYPos;
    u8 field_0xa;
    u8 area;
    u8 room;
    u8 playerLayer;
    u8 field_0xe;
    u8 playerState;
    u16 transitionSFX;
} ScreenTransitionData;

typedef struct {
    u8 type;
    u8 localFlag;
    u8 _2;
    u8 _3;
    u16 tilePos;
    u8 _6;
    u8 _7;
} TileEntity;
extern TileEntity gSmallChests[8];

extern TileEntity gUnk_080FEAC8[];

typedef enum {
    NONE,
    ROOM_VISIT_MARKER,
    SMALL_CHEST,
    BIG_CHEST,
    BOMBABLE_WALL,
    SIGN,
    TILE_EZLO_HINT,
    MUSIC_SETTER,
    TILE_ENTITY_8,
    DARKNESS,
    DESTRUCTIBLE_TILE,
    GRASS_DROP_CHANGER,
    LOCATION_CHANGER,
    TILE_ENTITY_D,
} TileEntityType;

extern void** gCurrentRoomProperties;

void SetTileType(u32, u32, u32);
void InitScreenShake(u32 time, u32 magnitude);

void CallRoomProp5And7(void);
void LoadRoom(void);
void SetCurrentRoomPropertyList(u32 area, u32 room);
void* GetCurrentRoomProperty(u32);
void LoadRoomTileEntities();
Entity* LoadRoomEntity(const EntityData*);
void LoadRoomEntityList(const EntityData* listPtr);

bool32 LoadFixedGFX(Entity*, u32);
void UnloadGFXSlots(Entity*);
void sub_0804B3C4(TileEntity*);
void sub_0804B0B0(u32 arg0, u32 arg1);

void DoExitTransition(const ScreenTransitionData* data);

#endif // ROOM_H
