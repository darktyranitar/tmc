#include "entity.h"
#include "definitions.h"

// TODO deduplicate using sprite indices enum
const NPCDefinition gNPCDefinition_3[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 48, 0, 0, 0, 31, 1, 0 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 48, 0, 0, 0, 31, 1, 0 } },
};
const NPCDefinition gNPCDefinition_6[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 2, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 57, 1, 1 } },
};
const NPCDefinition gNPCDefinition_7[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } }, { { 1, 0, 0, 1, 2, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 58, 0, 0, 0, 59, 1, 1 } },
};
const NPCDefinition gNPCDefinition_1B[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 71, 0, 1, 0, 48, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 74, 0, 1, 0, 48, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 73, 0, 1, 0, 48, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 72, 0, 1, 0, 48, 1, 0 } },
};
#ifdef EU
const NPCDefinition gNPCDefinition_27[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 80, 0, 1, 0, 327, 1, 0 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 283, 0, 1, 0, 32, 1, 0 } },
};
#else
const NPCDefinition gNPCDefinition_27[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 80, 0, 1, 0, 328, 1, 0 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 283, 0, 1, 0, 32, 1, 0 } },
};
#endif
const NPCDefinition gNPCDefinition_2B[] = {
    { { 1, 0, 0, 1, 200, 0, 0 }, { 5, 0, 1, 0, 160, 0, 1 } },
    { { 1, 0, 0, 1, 4, 1, 0 }, { 5, 0, 1, 0, 94, 0, 1 } },
};
const NPCDefinition gNPCDefinition_30[] = {
    { { 1, 0, 0, 1, 231, 0, 0 }, { 183, 0, 1, 0, 149, 1, 1 } },
    { { 1, 0, 0, 1, 232, 0, 0 }, { 184, 0, 1, 0, 150, 1, 1 } },
    { { 1, 0, 0, 1, 232, 0, 0 }, { 185, 0, 1, 0, 150, 1, 1 } },
    { { 1, 0, 0, 1, 232, 0, 0 }, { 186, 0, 1, 0, 150, 1, 1 } },
    { { 1, 0, 0, 1, 232, 0, 0 }, { 187, 0, 1, 0, 150, 1, 1 } },
    { { 1, 0, 0, 1, 232, 0, 0 }, { 188, 0, 1, 0, 150, 1, 1 } },
    { { 1, 0, 0, 1, 232, 0, 0 }, { 189, 0, 1, 0, 150, 1, 1 } },
    { { 1, 0, 0, 1, 232, 0, 0 }, { 190, 0, 1, 0, 150, 1, 1 } },
};
const NPCDefinition gNPCDefinition_33[] = {
    { { 1, 0, 0, 3, 2, 1, 0 }, { 192, 0, 2, 0, 91, 1, 1 } },
    { { 1, 0, 0, 3, 2, 1, 0 }, { 192, 0, 2, 0, 92, 1, 1 } },
};
const NPCDefinition gNPCDefinition_21[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 79, 0, 1, 0, 88, 1, 0 } },  { { 1, 0, 0, 1, 1, 1, 0 }, { 78, 0, 1, 0, 88, 1, 0 } },
    { { 1, 0, 0, 1, 38, 0, 0 }, { 0, 0, 0, 0, 173, 3, 0 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 71, 0, 1, 0, 48, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 79, 0, 1, 0, 88, 0, 0 } },  { { 1, 0, 0, 1, 1, 1, 0 }, { 78, 0, 1, 0, 88, 0, 0 } },
};
const NPCDefinition gNPCDefinition_5[] = {
    { { 1, 0, 0, 0, 1, 1, 0 }, { 54, 0, 1, 0, 42, 1, 1 } },
    { { 1, 0, 0, 0, 0, 0, 0 }, { 54, 0, 1, 0, 42, 0, 0 } },
    { { 1, 0, 0, 1, 0, 0, 0 }, { 0, 0, 1, 0, 42, 0, 0 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 54, 0, 1, 0, 42, 1, 1 } },
};
const NPCDefinition gNPCDefinition_35[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 82, 0, 1, 0, 67, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 64, 0, 1, 0, 69, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 4, 0, 1, 0, 68, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 83, 0, 1, 0, 69, 1, 1 } },
};
const NPCDefinition gNPCDefinition_2C[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 1, 0, 1, 0, 65, 1, 0 } },  { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 65, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 1, 0, 1, 0, 66, 1, 0 } },  { { 1, 0, 0, 1, 1, 1, 0 }, { 4, 0, 1, 0, 66, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 84, 0, 1, 0, 66, 1, 0 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 1, 0, 1, 0, 65, 1, 0 } },
};
const NPCDefinition gNPCDefinition_37[] = {
    { { 1, 0, 0, 1, 261, 0, 0 }, { 233, 0, 1, 0, 151, 0, 1 } },
    { { 1, 0, 0, 0, 261, 0, 0 }, { 233, 0, 1, 0, 151, 0, 1 } },
    { { 1, 0, 0, 0, 160, 0, 0 }, { 0, 0, 1, 0, 151, 0, 1 } },
    { { 1, 0, 0, 0, 161, 0, 0 }, { 1, 0, 1, 0, 151, 0, 1 } },
    { { 1, 0, 0, 0, 455, 0, 0 }, { 1, 0, 1, 0, 151, 0, 1 } },
    { { 1, 0, 0, 0, 0, 2, 0 }, { 4, 0, 1, 0, 151, 0, 1 } },
};
const NPCDefinition gNPCDefinition_38[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 234, 0, 1, 0, 29, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 234, 0, 1, 0, 29, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 235, 0, 1, 0, 29, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 236, 0, 1, 0, 29, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 237, 0, 1, 0, 29, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 238, 0, 1, 0, 29, 1, 1 } },
};
const NPCDefinition gNPCDefinition_3D[] = {
    { { 1, 0, 0, 5, 57, 0, 0 }, { 60, 0, 0, 0, 141, 0, 1 } },
    { { 1, 0, 0, 5, 58, 0, 0 }, { 61, 0, 0, 0, 142, 0, 1 } },
};
const NPCDefinition gNPCDefinition_3E[] = {
    { { 1, 0, 0, 1, 2, 1, 0 }, { 247, 0, 1, 0, 72, 1, 1 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 248, 0, 1, 0, 73, 1, 1 } },
};
const NPCDefinition gNPCDefinition_3F[] = {
    { { 1, 0, 0, 5, 288, 0, 0 }, { 249, 0, 0, 0, 152, 0, 1 } },
    { { 1, 0, 0, 5, 289, 0, 0 }, { 250, 0, 0, 0, 153, 0, 1 } },
};
const NPCDefinition gNPCDefinition_41[] = {
    { { 1, 0, 0, 1, 290, 0, 0 }, { 252, 0, 1, 0, 154, 0, 1 } },
    { { 1, 0, 0, 0, 291, 0, 0 }, { 252, 0, 0, 0, 155, 0, 1 } },
};
const NPCDefinition gNPCDefinition_48[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 259, 0, 1, 0, 79, 1, 1 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 0, 0, 1, 0, 80, 1, 1 } },
};
const NPCDefinition gNPCDefinition_49[] = {
    { { 1, 0, 0, 1, 1, 1, 0 }, { 260, 0, 1, 0, 81, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 260, 0, 1, 0, 82, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 260, 0, 1, 0, 83, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 260, 0, 1, 0, 84, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 260, 0, 1, 0, 85, 1, 1 } }, { { 1, 0, 0, 1, 1, 1, 0 }, { 260, 0, 1, 0, 86, 1, 1 } },
};
const NPCDefinition gNPCDefinition_4A[] = {
    { { 1, 0, 0, 4, 297, 0, 0 }, { 265, 0, 1, 0, 158, 0, 1 } },
    { { 1, 0, 0, 0, 297, 0, 0 }, { 273, 0, 1, 0, 158, 0, 1 } },
    { { 1, 0, 0, 0, 297, 0, 0 }, { 1, 0, 1, 0, 158, 0, 1 } },
    { { 1, 0, 0, 1, 297, 0, 0 }, { 272, 0, 1, 0, 158, 1, 1 } },
};
const NPCDefinition gNPCDefinition_4C[] = {
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 282, 0, 0, 0, 159, 0, 1 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 282, 0, 0, 0, 159, 0, 1 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 0, 0, 0, 0, 159, 0, 1 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 282, 0, 0, 0, 159, 0, 1 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 282, 0, 0, 0, 159, 0, 1 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 282, 0, 0, 0, 159, 0, 1 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 282, 0, 0, 0, 159, 0, 1 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 282, 0, 0, 0, 159, 0, 1 } },
    { { 1, 0, 0, 0, 398, 0, 0 }, { 282, 0, 0, 0, 159, 0, 1 } },
};
const NPCDefinition gNPCDefinition_4F[] = {
    { { 1, 0, 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 95, 0, 1 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 95, 0, 1 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 1, 0, 0, 0, 95, 0, 1 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 2, 0, 0, 0, 95, 0, 1 } },
};
#ifdef EU
const NPCDefinition gNPCDefinition_3B[] = {
    { { 1, 0, 0, 0, 2, 1, 0 }, { 312, 0, 0, 0, 112, 0, 1 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 312, 0, 0, 0, 114, 0, 1 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 312, 0, 0, 0, 115, 0, 1 } },
    { { 1, 0, 0, 0, 2, 1, 0 }, { 312, 0, 0, 0, 123, 0, 1 } },
    { { 1, 0, 0, 0, 460, 0, 0 }, { 319, 0, 0, 0, 303, 0, 1 } },
    { { 1, 0, 0, 0, 2, 1, 0 }, { 319, 0, 0, 0, 124, 0, 1 } },
};
const NPCDefinition gNPCDefinition_52[] = {
    { { 1, 0, 0, 0, 496, 0, 0 }, { 234, 0, 0, 0, 313, 0, 1 } },
    { { 1, 0, 0, 0, 496, 0, 0 }, { 236, 0, 0, 0, 313, 0, 1 } },
    { { 1, 0, 0, 0, 496, 0, 0 }, { 237, 0, 0, 0, 313, 0, 1 } },
    { { 1, 0, 0, 0, 496, 0, 0 }, { 238, 0, 0, 0, 313, 0, 1 } },
    { { 1, 0, 0, 0, 496, 0, 0 }, { 235, 0, 0, 0, 313, 0, 1 } },
};
#else
const NPCDefinition gNPCDefinition_3B[] = {
    { { 1, 0, 0, 0, 2, 1, 0 }, { 312, 0, 0, 0, 112, 0, 1 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 312, 0, 0, 0, 114, 0, 1 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 312, 0, 0, 0, 115, 0, 1 } },
    { { 1, 0, 0, 0, 2, 1, 0 }, { 312, 0, 0, 0, 123, 0, 1 } },
    { { 1, 0, 0, 0, 460, 0, 0 }, { 319, 0, 0, 0, 304, 0, 1 } },
    { { 1, 0, 0, 0, 2, 1, 0 }, { 319, 0, 0, 0, 124, 0, 1 } },
};
const NPCDefinition gNPCDefinition_52[] = {
    { { 1, 0, 0, 0, 496, 0, 0 }, { 234, 0, 0, 0, 314, 0, 1 } },
    { { 1, 0, 0, 0, 496, 0, 0 }, { 236, 0, 0, 0, 314, 0, 1 } },
    { { 1, 0, 0, 0, 496, 0, 0 }, { 237, 0, 0, 0, 314, 0, 1 } },
    { { 1, 0, 0, 0, 496, 0, 0 }, { 238, 0, 0, 0, 314, 0, 1 } },
    { { 1, 0, 0, 0, 496, 0, 0 }, { 235, 0, 0, 0, 314, 0, 1 } },
};
#endif

#define MULTI_FORM(definition_ptr)         \
    {                                      \
        { 2, 0, 0, 0, 0, 0, 0 }, {         \
            .definition = (definition_ptr) \
        }                                  \
    }

const NPCDefinition gNPCDefinitions[] = {
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 49, 0, 0, 0, 24, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 50, 0, 0, 0, 25, 1, 0 } },
    MULTI_FORM(gNPCDefinition_3),
    { { 1, 0, 0, 1, 1, 1, 0 }, { 0, 0, 1, 0, 52, 1, 1 } },
    MULTI_FORM(gNPCDefinition_5),
    MULTI_FORM(gNPCDefinition_6),
    MULTI_FORM(gNPCDefinition_7),
    { { 1, 0, 0, 1, 2, 1, 0 }, { 0, 0, 1, 0, 43, 1, 1 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 1, 0, 0, 5, 59, 0, 0 }, { 65, 0, 0, 0, 143, 0, 0 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 0, 0, 1, 0, 47, 1, 1 } },
    { { 1, 0, 0, 5, 60, 0, 0 }, { 66, 0, 0, 0, 144, 0, 0 } },
    { { 1, 0, 0, 5, 61, 0, 0 }, { 57, 0, 0, 0, 146, 0, 1 } },
    { { 1, 0, 0, 1, 64, 0, 0 }, { 56, 0, 0, 0, 147, 0, 1 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 284, 0, 1, 0, 37, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 0, 0, 1, 0, 60, 1, 1 } },
    { { 1, 0, 0, 3, 1, 1, 0 }, { 62, 0, 1, 0, 49, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 63, 0, 1, 0, 50, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 63, 0, 1, 0, 61, 0, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 51, 1, 1 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 55, 0, 1, 0, 43, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 70, 0, 1, 0, 47, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 67, 0, 1, 0, 39, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 68, 0, 1, 0, 40, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 69, 0, 1, 0, 41, 1, 1 } },
    { { 1, 0, 0, 1, 56, 0, 0 }, { 59, 0, 1, 0, 140, 1, 0 } },
    MULTI_FORM(gNPCDefinition_1B),
    { { 1, 0, 0, 5, 66, 0, 0 }, { 53, 0, 0, 0, 145, 0, 0 } },
    { { 1, 0, 0, 1, 68, 0, 0 }, { 75, 0, 1, 0, 139, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 76, 0, 1, 0, 53, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 1, 0, 1, 0, 54, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 1, 0, 2, 0, 55, 1, 0 } },
    MULTI_FORM(gNPCDefinition_21),
    { { 1, 0, 0, 1, 2, 1, 0 }, { 77, 0, 1, 0, 56, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 48, 0, 0, 0, 31, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 55, 0, 0, 0, 44, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 55, 0, 0, 0, 45, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 55, 0, 0, 0, 46, 1, 0 } },
    MULTI_FORM(gNPCDefinition_27),
    { { 1, 0, 0, 1, 1, 1, 0 }, { 54, 0, 1, 0, 42, 1, 0 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 81, 0, 1, 0, 62, 1, 1 } },
    { { 1, 0, 0, 1, 2, 1, 0 }, { 81, 0, 1, 0, 63, 1, 1 } },
    MULTI_FORM(gNPCDefinition_2B),
    MULTI_FORM(gNPCDefinition_2C),
    { { 1, 0, 0, 1, 2, 1, 0 }, { 180, 0, 1, 0, 27, 1, 1 } },
    { { 1, 0, 0, 0, 1, 1, 0 }, { 54, 0, 1, 0, 42, 1, 1 } },
    { { 1, 0, 0, 3, 2, 1, 0 }, { 181, 0, 1, 0, 26, 1, 1 } },
    MULTI_FORM(gNPCDefinition_30),
    { { 1, 0, 0, 3, 1, 1, 0 }, { 191, 0, 0, 0, 90, 0, 1 } },
    { { 1, 0, 0, 3, 1, 1, 0 }, { 192, 0, 2, 0, 93, 1, 1 } },
    MULTI_FORM(gNPCDefinition_33),
    { { 1, 0, 0, 3, 1, 1, 0 }, { 193, 0, 1, 0, 64, 1, 1 } },
    MULTI_FORM(gNPCDefinition_35),
    { { 1, 0, 0, 3, 2, 1, 0 }, { 0, 0, 1, 0, 70, 0, 1 } },
    MULTI_FORM(gNPCDefinition_37),
    MULTI_FORM(gNPCDefinition_38),
    { { 1, 0, 0, 1, 2, 1, 0 }, { 281, 0, 1, 0, 30, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 246, 0, 1, 0, 71, 1, 1 } },
    MULTI_FORM(gNPCDefinition_3B),
    { { 1, 0, 0, 1, 72, 0, 0 }, { 111, 0, 1, 0, 207, 1, 1 } },
    MULTI_FORM(gNPCDefinition_3D),
    MULTI_FORM(gNPCDefinition_3E),
    MULTI_FORM(gNPCDefinition_3F),
    { { 1, 0, 0, 3, 1, 1, 0 }, { 251, 0, 1, 0, 74, 1, 1 } },
    MULTI_FORM(gNPCDefinition_41),
    { { 1, 0, 0, 0, 1, 1, 0 }, { 253, 0, 1, 0, 75, 0, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 254, 0, 1, 0, 76, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 255, 0, 1, 0, 77, 1, 1 } },
    { { 1, 0, 0, 1, 292, 0, 0 }, { 256, 0, 1, 0, 156, 1, 1 } },
    { { 1, 0, 0, 1, 1, 1, 0 }, { 257, 0, 1, 0, 78, 1, 1 } },
    { { 1, 0, 0, 5, 293, 0, 0 }, { 258, 0, 0, 0, 157, 0, 1 } },
    MULTI_FORM(gNPCDefinition_48),
    MULTI_FORM(gNPCDefinition_49),
    MULTI_FORM(gNPCDefinition_4A),
    { { 1, 0, 0, 1, 1, 1, 0 }, { 62, 0, 1, 0, 87, 1, 1 } },
    MULTI_FORM(gNPCDefinition_4C),
    { { 1, 0, 0, 1, 1, 1, 0 }, { 22, 0, 1, 0, 11, 1, 1 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    MULTI_FORM(gNPCDefinition_4F),
#ifdef EU
    { { 1, 0, 0, 0, 464, 0, 0 }, { 0, 0, 1, 0, 306, 0, 1 } },
#else
    { { 1, 0, 0, 0, 464, 0, 0 }, { 0, 0, 1, 0, 307, 0, 1 } },
#endif
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    MULTI_FORM(gNPCDefinition_52),
    { { 1, 0, 0, 1, 2, 1, 0 }, { 355, 0, 1, 0, 89, 1, 1 } },
    { { 1, 0, 0, 1, 67, 0, 0 }, { 0, 0, 1, 0, 148, 1, 1 } },
#ifdef EU
    { { 1, 0, 0, 1, 463, 0, 0 }, { 0, 0, 0, 0, 494, 1, 1 } },
#else
    { { 1, 0, 0, 1, 463, 0, 0 }, { 0, 0, 0, 0, 495, 1, 1 } },
#endif
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
#ifdef EU
    { { 1, 0, 0, 3, 348, 0, 0 }, { 88, 0, 0, 0, 393, 0, 1 } },
#else
    { { 1, 0, 0, 3, 348, 0, 0 }, { 88, 0, 0, 0, 394, 0, 1 } },
#endif
    { { 1, 0, 0, 0, 1, 1, 0 }, { 0, 0, 1, 0, 97, 0, 1 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 } },
};
