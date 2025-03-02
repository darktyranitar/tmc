#include "global.h"
#include "entity.h"
#include "room.h"
#include "npc.h"

//clang-format off
void (*const gNPCFunctions[][3])(Entity* ent) = {
    [NPC_NONE_0] = { DeleteEntity, NULL, NULL },
    [GENTARI] = { Gentari, NULL, Gentari_Fusion },
    [FESTARI] = { Festari, NULL, Festari_Fusion },
    [FOREST_MINISH] = { ForestMinish, ForestMinish_Head, ForestMinish_Fusion },
    [POSTMAN] = { Postman, NULL, Postman_Fusion },
    [NPC_UNK_5] = { NPC5, NULL, NULL },
    [TPWNSPERSON] = { Townsperson, Townsperson_Head, Townsperson_Fusion },
    [KID] = { Kid, Kid_Head, Kid_Fusion },
    [GUARD] = { Guard, Guard_Head, NULL },
    [NPC_UNK_9] = { NPC9, NULL, NULL },
    [STAMP] = { Stamp, NULL, NULL },
    [MAID] = { Maid, Maid_Head, NULL },
    [MARCY] = { Marcy, NULL, NULL },
    [WHEATON] = { Wheaton, NULL, NULL },
    [PITA] = { Pita, NULL, NULL },
    [MINISH_EZLO] = { MinishEzlo, MinishEzlo_Head, NULL },
    [MAILBOX] = { Mailbox, NULL, NULL },
    [BEEDLE] = { Beedle, Beedle_Head, NULL },
    [BROCCO] = { Brocco, NULL, Brocco_Fusion },
    [SITTING_PERSON] = { SittingPerson, SittingPerson_Head, SittingPerson_Fusion },
    [PINA] = { Pina, NULL, Pina_Fusion },
    [GUARD_1] = { Guard, Guard_Head, NULL },
    [MAID_1] = { Maid, Maid_Head, NULL },
    [DIN] = { Din, NULL, Din_Fusion },
    [NAYRU] = { Nayru, NULL, Nayru_Fusion },
    [FARORE] = { Farore, NULL, Farore_Fusion },
    [STURGEON] = { Sturgeon, Sturgeon_Head, Sturgeon_Fusion },
    [TINGLE_SIBLINGS] = { TingleSiblings, NULL, TingleSiblings_Fusion },
    [STOCKWELL] = { Stockwell, NULL, NULL },
    [TALON] = { Talon, Talon_Head, Talon_Fusion },
    [MALON] = { Malon, NULL, Malon_Fusion },
    [EPONA] = { Epona, NULL, Epona_Fusion },
    [MILK_CART] = { MilkCart, NULL, NULL },
    [GHOST_BROTHERS] = { GhostBrothers, NULL, GhostBrothers_Fusion },
    [SMITH] = { Smith, Smith_Head, Smith_Fusion },
    [NPC_UNK_23] = { NPC23, NULL, NULL },
    [KING_DALTUS] = { KingDaltus, NULL, KingDaltus_Fusion },
    [MINISTER_POTHO] = { MinisterPotho, NULL, MinisterPotho_Fusion },
    [NPC_UNK_26] = { NPC26, NULL, NULL },
    [VAATI] = { Vaati, NULL, NULL },
    [ZELDA] = { Zelda, NULL, NULL },
    [MUTOH] = { Mutoh, Mutoh_Head, Mutoh_Fusion },
    [CARPENTER] = { Carpenter, Carpenter_Head, Carpenter_Fusion },
    [CASTOR_WILDS_STATUE] = { CastorWildsStatue, NULL, CastorWildsStatue_Fusion },
    [CAT] = { Cat, NULL, Cat_Fusion },
    [MOUNTAIN_MINISH] = { MountainMinish, MountainMinish_Head, MountainMinish_Fusion },
    [ZELDA_FOLLOWER] = { ZeldaFollower, NULL, NULL },
    [MELARI] = { Melari, Melari_Head, Melari_Fusion },
    [BLADE_BROTHERS] = { BladeBrothers, NULL, BladeBrothers_Fusion },
    [COW] = { Cow, NULL, Cow_Fusion },
    [GORON] = { Goron, NULL, Goron_Fusion },
    [GORON_MERCHANT] = { GoronMerchant, NULL, NULL },
    [GORMAN] = { Gorman, Gorman_Head, NULL },
    [DOG] = { Dog, Dog_Head, Dog_Fusion },
    [SYRUP] = { Syrup, Syrup_Head, NULL },
    [REM] = { Rem, NULL, NULL },
    [TOWN_MINISH] = { TownMinish, TownMinish_Head, TownMinish_Fusion },
    [LIBRARI] = { Librari, NULL, Librari_Fusion },
    [PERCY] = { Percy, Percy_Head, Percy_Fusion },
    [VAATI_REBORN] = { VaatiReborn, NULL, NULL },
    [MOBLIN_LADY] = { MoblinLady, NULL, NULL },
    [LIBRARIANS] = { Librarians, NULL, NULL },
    [FARMERS] = { Farmers, Farmers_Head, Farmers_Fusion },
    [CARLOV] = { Carlov, NULL, NULL },
    [DAMPE] = { Dampe, NULL, Dampe_Fusion },
    [DR_LEFT] = { DrLeft, NULL, NULL },
    [KING_GUSTAF] = { KingGustaf, NULL, NULL },
    [GINA] = { Gina, NULL, Gina_Fusion },
    [SIMON] = { Simon, NULL, NULL },
    [ANJU] = { Anju, NULL, Anju_Fusion },
    [MAMA] = { Mama, Mama_Head, Mama_Fusion },
    [EMMA] = { Emma, NULL, NULL },
    [TEACHERS] = { Teachers, Teachers_Head, Teachers_Fusion },
    [WIND_TRIBESPEOPLE] = { WindTribespeople, WindTribespeople_Head, WindTribespeople_Fusion },
    [GREGAL] = { Gregal, NULL, Gregal_Fusion },
    [MAYOR_HAGEN] = { MayorHagen, NULL, MayorHagen_Fusion },
    [BIG_GORON] = { BigGoron, NULL, NULL },
    [EZLO] = { Ezlo, NULL, NULL },
    [NPC_UNK_4E] = { NPC4E, NULL, NPC4E_Fusion },
    [NPC_UNK_4F] = { NPC4F, NULL, NULL },
    [CLOTHES_RACK] = { ClothesRack, NULL, NULL },
    [PICOLYTE_BOTTLE] = { PicolyteBottle, NULL, NULL },
    [SMALL_TOWN_MINISH] = { SmallTownMinish, NULL, NULL },
    [HURDY_GURDY_MAN] = { HurdyGurdyMan, HurdyGurdyMan_Head, HurdyGurdyMan_Fusion },
    [CUCCO] = { Cucco, NULL, Cucco_Fusion },
    [CUCCO_CHICK] = { CuccoChick, NULL, CuccoChick_Fusion },
    [FUSION_MENU_NPC] = { FusionMenuNPC, FusionMenuNPC_Head, NULL },
    [PHONOGRAPH] = { Phonograph, NULL, NULL },
    [NPC_UNK_58] = { NPC58, NPC58_Head, NULL },
    [NPC_NONE_1] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_2] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_3] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_4] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_5] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_6] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_7] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_8] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_9] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_10] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_11] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_12] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_13] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_14] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_15] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_16] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_17] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_18] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_19] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_20] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_21] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_22] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_23] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_24] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_25] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_26] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_27] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_28] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_29] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_30] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_31] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_32] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_33] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_34] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_35] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_36] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_37] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_38] = { DeleteEntity, NULL, NULL },
    [NPC_NONE_39] = { DeleteEntity, NULL, NULL }
};
//clang-format on
const u8 npc_unk[] = { 0x04, 0x05, 0x06, 0x06 };

extern u32 gUnk_020342F8;
typedef struct {
    u16 unk0;
    u16 unk1;
    u16 x;
    u16 y;
} NPCStruct;
extern NPCStruct gUnk_02031EC0[100];

void InitNPC(Entity*);

// regalloc
NONMATCH("asm/non_matching/arm_proxy/NPCUpdate.inc", void NPCUpdate(Entity* this)) {
    if ((this->health & 0x7f) && !ReadBit(&gUnk_020342F8, this->health - 1))
        DeleteThisEntity();
    if (this->action == 0 && (this->flags & ENT_DID_INIT) == 0)
        InitNPC(this);
    if (!EntityIsDeleted(this))
        gNPCFunctions[this->id][0](this);
    if (this->next != NULL) {
        if (gNPCFunctions[this->id][1] != NULL)
            gNPCFunctions[this->id][1](this);
        if ((this->health & 0x7f) != 0) {
            u32 temp = this->health & 0x7f;
            gUnk_02031EC0[temp * 2 - 2].x = this->x.HALF.HI - gRoomControls.origin_x;
            gUnk_02031EC0[temp * 2 - 2].y = this->y.HALF.HI - gRoomControls.origin_y;
        }
        DrawEntity(this);
    }
}
END_NONMATCH
