#define NENT_DEPRECATED
#include "entity.h"
#include "room.h"
#include "functions.h"
#include "object.h"

extern void sub_080001D0(u32, u32, u32);

enum {
    FURNITURE_INIT,
    FURNITURE_UPDATE,
};

typedef enum {
    TMP,
} FurnitureFlag;

typedef enum {
    BOOKSHELF,
    CRATE,
    BULLETIN_BOARD,
    CERAMIC_SHELF1,
    FLOUR_SACK,
    LOGS,
    WATER_BARREL,
    WEAPON_RACK,
    RED_CAULDRON,
    SMITH_FORGE,
    LARGE_CERAMIC_SHELF,
    LADDER,
    GLOWING_PLANT,
    GLOWING_SPORES,
    LOG_SHELF,
    KINSTONE_SHELF,
    BLUE_CAULDRON,
    HAY_BED,
    MILK_JUG,
    HAY_BALE,
    FLOWER_BED_SMALL,
    FLOWER_BED_VERT,
    FLOWER_BED_HORIZ,
    CARPENTER_MACHINE,
    SPROUT_CART,
    ENVELOPE_SHELF,
    BREAD_SHELF,
    MAYOR_DESK,
    SHOES,
    REPAIRED_SHOE,
    SHOE_DESK,
    STAIRCASE,
    DECORATED_STONE,
    BIRD_STATUE,
    CLOSET,
    DRAWERS,
    CERAMIC_SHELF2,
    LARGE_BOOKCASE,
    MINISH_BED,
    MINISH_BUTTONS,
    MINISH_CHEESE,
    MINISH_CHERRIES,
    MINISH_CHESSPIECE,
    MINISH_COOKIES,
    MINISH_MUG,
    DR_LEFT_DESK1,
    DR_LEFT_DESK2,
    MINISH_DIE,
    MINISH_GEAR,
    MINISH_PINCUSHION,
    MINISH_THREAD,
    MINISH_MALLET,
    MINISH_SCROLL_BOX,
    MINISH_APPLE,
    MINISH_CANDLE,
    MINISH_WOOD_PLANK,
    GBA_SCREEN,
    PHONOGRAPH,
    BAKERY_TABLE,
    WOODEN_TABLE,
    LOW_BOOKSHELF,
    FIGURINE_DEVICE_STATIC,
    FORGE_HELPER,
    MINISH_UNLIT_CANDLE,
    MINISH_GEARS,
    DOUBLE_BOOKSHELF_STATIC,
    MINISH_DECOR1,
    MINISH_DECOR2,
    MINISH_JAM,
    MINISH_BREAD,
    POSTER1,
    POSTER2,
    NOTE,
} FurnitureType;

typedef struct {
    Entity base;
    /* 0x68 */ u8 pad[0x10];
    /* 0x78 */ u16 tile;
    /* 0x7a */ u16 unk1;
    /* 0x7c */ u16 unk2;
    /* 0x7e */ u16 unk3;
    /* 0x80 */ u8 width;
    /* 0x81 */ u8 height;
    /* 0x82 */ u16 flags;
} FurnitureEntity;

typedef void(FurnitureAction)(FurnitureEntity*);

static FurnitureAction FurnitureInit;
static FurnitureAction FurnitureUpdate;

typedef struct {
    u8 width;
    u8 height;
    s8 x;
    s8 y;
    u8 rendering;
    u8 priority;
    u16 flags;
} FurnitureCfg;

static const FurnitureCfg gUnk_08121EF8[] = {
    { 0x30, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x10, 0x10, 0x0, 0x0, 0x2, 0x5, 0x0 },
    { 0x40, 0x10, 0x0, 0x0, 0x2, 0x4, 0x1 },   { 0x18, 0x10, 0x0, 0x0, 0x2, 0x5, 0x0 },
    { 0x18, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x0, 0x0, 0x0, 0x0, 0x2, 0x7, 0x8000 },
    { 0x20, 0x10, 0x0, -0x4, 0x2, 0x4, 0x0 },  { 0x40, 0x10, 0x0, 0x0, 0x3, 0x7, 0x0 },
    { 0x30, 0x10, 0x0, 0x0, 0x2, 0x5, 0x2 },   { 0x0, 0x0, 0x0, 0x3, 0x3, 0x7, 0x8000 },
    { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x8 },   { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x8 },
    { 0x18, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x30, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x20, 0x10, 0x0, -0x4, 0x2, 0x4, 0x0 },  { 0x18, 0x10, 0x0, 0x4, 0x2, 0x4, 0x0 },
    { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x20, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x0, 0x0, 0x0, 0x1, 0x2, 0x4, 0x8000 },  { 0x10, 0x30, 0x0, -0x8, 0x2, 0x4, 0x4 },
    { 0x40, 0x10, 0x0, -0x8, 0x2, 0x4, 0x4 },  { 0x60, 0x20, 0x0, 0x0, 0x3, 0x7, 0x10 },
    { 0x28, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x20, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x18, 0x10, 0x0, 0x0, 0x3, 0x7, 0x2 },   { 0x0, 0x0, 0x0, 0x2, 0x2, 0x4, 0x8000 },
    { 0x10, 0x10, 0x0, 0x0, 0x2, 0x3, 0x20 },  { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x20 },
    { 0x30, 0x20, 0x0, 0x0, 0x3, 0x4, 0x0 },   { 0x20, 0x10, 0x0, 0x0, 0x3, 0x7, 0x20 },
    { 0x20, 0x10, 0x0, 0x0, 0x2, 0x4, 0x100 }, { 0x0, 0x0, 0x0, 0x4, 0x2, 0x4, 0x8000 },
    { 0x18, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x18, 0x10, 0x0, 0x0, 0x2, 0x5, 0x0 },
    { 0x18, 0x10, 0x0, 0x0, 0x2, 0x5, 0x0 },   { 0x0, 0x0, 0x0, 0x5, 0x2, 0x4, 0x8000 },
    { 0x20, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x30, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x50, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x20, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x0, 0x0, 0x0, 0x7, 0x2, 0x4, 0x8000 },  { 0x30, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x38, 0x20, 0x0, 0x0, 0x2, 0x4, 0x20 },  { 0x30, 0x20, 0x0, 0x0, 0x2, 0x5, 0x0 },
    { 0x28, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x0, 0x0, 0x0, 0x6, 0x2, 0x4, 0x8000 },  { 0x30, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x20, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x30, 0x30, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x20, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x30, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x28, 0x20, 0x0, 0x0, 0x2, 0x4, 0x400 }, { 0x20, 0x10, 0x0, 0x0, 0x2, 0x6, 0x200 },
    { 0x0, 0x0, 0x0, 0x0, 0x2, 0x4, 0x20 },    { 0x0, 0x0, 0x0, 0x0, 0x2, 0x4, 0x20 },
    { 0x30, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x30, 0x10, 0x0, 0x0, 0x2, 0x6, 0x0 },
    { 0x40, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x30, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x0, 0x0, 0x0, 0x0, 0x3, 0x6, 0x10 },    { 0x30, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x30, 0x10, 0x0, 0x0, 0x2, 0x5, 0x0 },   { 0x40, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
    { 0x50, 0x10, 0x0, 0x0, 0x2, 0x5, 0x0 },   { 0x40, 0x10, 0x0, 0x0, 0x2, 0x5, 0x0 },
    { 0x30, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },   { 0x0, 0x0, 0x0, 0x8, 0x2, 0x4, 0x8000 }
};
static const FurnitureCfg gUnk_08122128[] = {
    { 0x28, 0x10, 0x0, -0x8, 0x2, 0x7, 0x20 }, { 0x28, 0x10, 0x0, -0x8, 0x2, 0x7, 0x20 },
    { 0x28, 0x10, 0x0, -0x8, 0x2, 0x7, 0x20 }, { 0x28, 0x10, 0x0, -0x8, 0x2, 0x7, 0x20 },
    { 0x20, 0x20, 0x0, 0x0, 0x2, 0x7, 0x20 },  { 0x20, 0x20, 0x0, 0x0, 0x2, 0x7, 0x20 },
    { 0x20, 0x20, 0x0, 0x0, 0x2, 0x7, 0x20 },  { 0x20, 0x20, 0x0, 0x0, 0x2, 0x7, 0x20 },
    { 0x10, 0x10, 0x0, -0x4, 0x2, 0x7, 0x20 }, { 0x10, 0x10, 0x0, -0x4, 0x2, 0x7, 0x20 },
    { 0x10, 0x10, 0x0, 0x0, 0x2, 0x7, 0x20 },  { 0x10, 0x10, 0x0, 0x0, 0x2, 0x7, 0x20 },
    { 0x10, 0x10, 0x0, 0x0, 0x2, 0x7, 0x20 },  { 0x10, 0x10, 0x0, 0x0, 0x2, 0x7, 0x20 }
};
static const FurnitureCfg gUnk_08122198[] = { { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
                                              { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x4 } };
static const FurnitureCfg gUnk_081221A8[] = { { 0x30, 0x20, 0x0, 0x8, 0x2, 0x4, 0x0 },
                                              { 0x10, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 } };
static const FurnitureCfg gUnk_081221B8[] = { { 0x20, 0x10, 0x0, 0x0, 0x3, 0x7, 0x40 },
                                              { 0x20, 0x10, 0x0, 0x2, 0x2, 0x4, 0x80 } };
static const FurnitureCfg gUnk_081221C8[] = { { 0x18, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
                                              { 0x18, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 } };
static const FurnitureCfg gUnk_081221D8[] = { { 0x30, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 },
                                              { 0x30, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 } };
static const FurnitureCfg gUnk_081221E8[] = { { 0x28, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },
                                              { 0x20, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 } };
static const FurnitureCfg gUnk_081221F8[] = { { 0x20, 0x10, -0x2, 0x8, 0x2, 0x4, 0x0 },
                                              { 0x20, 0x10, 0x0, 0x0, 0x2, 0x4, 0x0 } };
static const FurnitureCfg gUnk_08122208[] = { { 0x30, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 },
                                              { 0x30, 0x20, 0x0, 0x0, 0x2, 0x4, 0x0 } };

static void sub_08090DC4(FurnitureEntity*);
static void sub_08090E64(FurnitureEntity*);
static void sub_08090B6C(FurnitureEntity*);
static void sub_08090E4C(FurnitureEntity*);
static void sub_08090CDC(u32, u32, u32);

void Furniture(Entity* this) {
    static FurnitureAction* const sFurnitureActions[] = {
        FurnitureInit,
        FurnitureUpdate,
    };

    sFurnitureActions[this->action]((FurnitureEntity*)this);
}

static void FurnitureInit(FurnitureEntity* this) {
    u32 i, tile, cnt;
    Entity* e;

    super->action = FURNITURE_UPDATE;
    this->tile = COORD_TO_TILE(super);
    sub_08090DC4(this);
    switch (this->flags & 0x7fff) {
        case 0x100:
            super->collisionLayer = 2;
            UpdateSpriteForCollisionLayer(super);
            break;
        case 0x20:
            break;
        case 0x40:
            super->y.HALF.HI = (super->y.HALF.HI & ~0xF) | 4;
            SetTile(0x4017, this->tile - 128, 1);
            SetTile(0x4017, this->tile - 64, 1);
            break;
        case 0x80:
            super->frameIndex = 0;
            super->y.HALF.HI = (super->y.HALF.HI & ~0xF) | 6;
            this->tile = COORD_TO_TILE(super);
            SetTile(0x4026, this->tile, super->collisionLayer);
            break;
        case 0x200:
            break;
        case 0x400:
            sub_08090E64(this);
            if (super->type2 != 0) {
                super->spriteOffsetX = 1;
                this->width = 48;
            }
        default:
            sub_08090B6C(this);
            break;
    }

    if (this->height != 16) {
        switch (this->height & 0x70) {
            case 0x30:
                this->tile -= 64;
                sub_08090B6C(this);
                this->tile = COORD_TO_TILE(super);
            case 0x20:
                this->tile += 64;
                sub_08090B6C(this);
        }
        this->tile = COORD_TO_TILE(super);
    }

    switch (this->flags & 0x7fff) {
        case 0x4:
            ChangeObjPalette(super, 0x7E);
            break;
        case 0x2:
            tile = this->tile - 129;
            cnt = super->type != 26 ? 3 : 2;
            for (i = 0; i < cnt; ++i, ++tile) {
                SetTile(0x4026, tile, 2);
                SetTile(0x4026, tile, 1);
                sub_080001D0(0, tile + 64, 1);
            }
            break;
    }

    switch (super->type) {
        case CRATE:
            if (super->type2 != 0) {
                super->spritePriority.b0 = 4;
            }
            break;
        case SMITH_FORGE:
            e = CreateObject(FURNITURE, FORGE_HELPER, 0);
            if (e != NULL) {
                PositionRelative(super, e, Q_16_16(16.0), Q_16_16(16.0));
                e->frameIndex = 1;
                e->updatePriority = PRIO_MESSAGE;
            }
            break;
        case SHOE_DESK:
            sub_0807B7D8(774, this->tile + 65, 2);
            break;
        case STAIRCASE:
            super->collisionLayer = 1;
            super->spriteOrientation.flipY = 2;
            SetTile(0x4074, this->tile - 64, super->collisionLayer);
            sub_080001D0(63, this->tile - 64, super->collisionLayer);
            SetTile(0x4017, this->tile, super->collisionLayer);
            SetTile(0x4017, this->tile + 64, super->collisionLayer);
            break;
        case MINISH_CHEESE:
            if (super->type2 != 0)
                super->spriteOffsetX = -4;
            break;
        case WOODEN_TABLE:
            SetTile(0x4023, this->tile - 65, super->collisionLayer);
            SetTile(0x4023, this->tile - 64, super->collisionLayer);
            SetTile(0x4023, this->tile - 63, super->collisionLayer);
            break;
        case LOW_BOOKSHELF:
            SetTile(0x4022, this->tile + 65, super->collisionLayer);
    }
}

static void FurnitureUpdate(FurnitureEntity* this) {
    switch (this->flags & 0x7FFF) {
        case 0x1:
            if (gPlayerEntity.y.HALF.HI < super->y.HALF.HI || gPlayerEntity.y.HALF.HI > super->y.HALF.HI + 24) {
                super->spriteRendering.b3 = 2;
            } else {
                super->spriteRendering.b3 = 3;
            }
            break;
        case 0x8:
            if (++super->timer == 16) {
                super->timer = 0;
                super->subtimer = (super->subtimer + 1) & 3;
                sub_08090E4C(this);
            }
            break;
        case 0x10:
            if (super->type != FORGE_HELPER) {
                if (++super->timer == 20) {
                    super->frameIndex = (super->frameIndex + 1) & 3;
                    super->timer = 0;
                }
            } else {
                if (++super->timer == 14) {
                    super->timer = 0;
                    super->subtimer = (super->subtimer + 1) % 3;
                    super->frameIndex = super->subtimer + 1;
                }
            }
            break;
        case 0x80:
            if (gPlayerEntity.y.HALF.HI < super->y.HALF.HI + 8) {
                if (gPlayerState.floor_type != SURFACE_LADDER && GetTileTypeByEntity(super) == 0x4017) {
                    SetTile(0x4026, this->tile, super->collisionLayer);
                    SetTile(0x403D, this->tile - 64, super->collisionLayer);
                    SetTile(0x403D, this->tile - 128, super->collisionLayer);
                }
            } else {
                if (gPlayerEntity.collisionLayer & 2) {
                    gPlayerEntity.collisionLayer = 1;
                    UpdateSpriteForCollisionLayer(&gPlayerEntity);
                }
                if (GetTileTypeByEntity(super) != 0x4017) {
                    SetTile(0x4017, this->tile, super->collisionLayer);
                    SetTile(0x4017, this->tile - 64, super->collisionLayer);
                    SetTile(0x4014, this->tile - 128, super->collisionLayer);
                }
            }
            break;
    }
}

static void sub_08090B6C(FurnitureEntity* this) {
    s32 num;

    u32 width = (u32)(this->width << 0x18) >> 0x18;
    if (width != 0) {
        u8 w2 = width / 8;
        u32 px = super->x.HALF.HI & 0xF;
        u32 tile = this->tile;
        u32 cl = super->collisionLayer;
        int i;

        switch ((u32)w2 & 3) {
            case 0:
                num = w2 / 8;
                if (w2 == 0xc) {
                    num = 2;
                }
                for (i = -num; i <= num; ++i) {
                    SetTile(0x4022, tile + i, cl);
                }
                if (px & 8) {
                    sub_08090CDC(0x4024, tile - i, cl);
                    sub_08090CDC(0x4025, tile + i, cl);
                } else {
                    SetTile(0x4022, tile - i, cl);
                }
                break;
            case 1:
                num = w2 / 8;
                for (i = -num; i <= num; i++) {
                    SetTile(0x4022, tile + i, cl);
                }
                if (px & 8) {
                    sub_08090CDC(0x4024, tile - i, cl);
                    if (i != 0) {
                        SetTile(0x4022, tile + i, cl);
                    }
                } else {
                    if (i != 0) {
                        SetTile(0x4022, tile - i, cl);
                    }
                    sub_08090CDC(0x4025, tile + i, cl);
                }
                break;
            case 2:
                num = w2 / 4;
                for (i = -num; i < num; ++i) {
                    SetTile(0x4022, tile + i, cl);
                }
                if (px & 8) {
                    SetTile(0x4022, tile + i, cl);
                } else {
                    sub_08090CDC(0x4024, tile - i - 1, cl);
                    sub_08090CDC(0x4025, tile + i, cl);
                }
                break;
            case 3:
                num = w2 / 4;
                for (i = -num; i <= num; ++i) {
                    SetTile(0x4022, tile + i, cl);
                }
                if (px & 8) {
                    sub_08090CDC(0x4025, tile + i, cl);
                } else {
                    sub_08090CDC(0x4024, tile - i, cl);
                }
                break;
        }
    }
}

static void sub_08090CDC(u32 id, u32 pos, u32 layer) {
    u16 cur = GetTileIndex(pos, layer);
    u32 next = cur;
    u32 id2;

    if ((cur & 0x4000) == 0) {
        SetTile(id, pos, layer);
    } else {
        switch (cur) {
            case 0x4025:
                if (id == 0x4024)
                    next = 0x4022;
                if (id == 0x402c)
                    next = 0x4022;
                break;
            case 0x402D:
                if (id == 0x402c)
                    next = 0x402b;
                if (id == 0x4024)
                    next = 0x4022;
                break;
            case 0x4024:
                if (id == 0x4025)
                    next = 0x4022;
                if (id == 0x402d)
                    next = 0x4022;
                break;
            case 0x402C:
                if (id == 0x402d)
                    next = 0x402b;
                if (id == 0x4025)
                    next = 0x4022;
                break;
            case 0x4022:
            case 0x4023:
            case 0x4026:
            case 0x4027:
            case 0x4028:
            case 0x4029:
            case 0x402a:
            case 0x402b:
            default:
                return;
        }
        SetTile(next, pos, layer);
    }
}

static void sub_08090DC4(FurnitureEntity* this) {
    static const FurnitureCfg* const sCfgTable[] = {
        gUnk_08122128, gUnk_08122198, gUnk_081221A8, gUnk_081221B8, gUnk_081221C8,
        gUnk_081221D8, gUnk_081221E8, gUnk_081221F8, gUnk_08122208,
    };

    const FurnitureCfg* cfg = &gUnk_08121EF8[super->type];
    if (cfg->flags & 0x8000) {
        cfg = sCfgTable[cfg->y];
        cfg += super->type2;
        super->frameIndex = super->type2;
    }
    this->width = cfg->width;
    this->height = cfg->height;
    super->spriteOffsetX = cfg->x;
    super->spriteOffsetY = cfg->y;
    super->spriteRendering.b3 = cfg->rendering;
    super->spritePriority.b0 = cfg->priority;
    this->flags = cfg->flags;
}

static void sub_08090E4C(FurnitureEntity* this) {
    static const u32 sPalettes[] = { 0x5f, 0x60, 0x61, 0x62 };

    ChangeObjPalette(super, sPalettes[super->subtimer]);
}

void sub_08090E64(FurnitureEntity* this) {
    Entity* e = CreateObject(OBJECT_2A, 0, 0);
    if (e != NULL) {
        PositionRelative(super, e, Q_16_16((s16)((u16)-2 + super->type2)), 0);
        e->z.HALF.HI -= 16;
        e->collisionLayer = 2;
        UpdateSpriteForCollisionLayer(e);
    }
}
