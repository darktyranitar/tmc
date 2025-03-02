#ifndef SCRIPT_H
#define SCRIPT_H

#include "entity.h"

typedef struct ScriptExecutionContext {
    /*0x00*/ u16* scriptInstructionPointer;
    /*0x04*/ u32 intVariable;
    /*0x08*/ u32 postScriptActions;
    /*0x0C*/ u8 unk_0C[0x4]; // unused
    /*0x10*/ u16 wait;
    /*0x12*/ u16 unk_12;
    /*0x14*/ u32 condition;
    /*0x18*/ u8 unk_18;
    /*0x19*/ u8 unk_19;
    /*0x1A*/ u8 unk_1A;
    /*0x1B*/ u8 unk_1B; // unused
    /*0x1C*/ union SplitWord x;
    /*0x20*/ union SplitWord y;
} ScriptExecutionContext;

typedef struct {
    // Sync flags are used to synchronize scripts running on different entities
    /*0x0*/ u32 syncFlags;
    /*0x4*/ u16 commandIndex;
    /*0x6*/ u8 commandSize;
    /*0x7*/ u8 flags;
    /*0x8*/ u8 fadeSpeed;
} ActiveScriptInfo;
extern ActiveScriptInfo gActiveScriptInfo;

void ExecuteScript(Entity* entity, ScriptExecutionContext* context);

extern u32 GetNextScriptCommandHalfword(u16*);
extern u32 GetNextScriptCommandWord(u16*);
extern u32 GetNextScriptCommandWordAfterCommandMetadata(u16*);
extern u32 GetNextScriptCommandHalfwordAfterCommandMetadata(u16*);

void UnloadCutsceneData(Entity* entity);
void StartPlayerScript(u16*);

void sub_0807DD50(Entity* entity);
void sub_0807DD64(Entity* entity);
void sub_0807DD80(Entity* entity, u16* script);
void sub_0807DEDC(Entity*, ScriptExecutionContext*, u32, u32);

ScriptExecutionContext* StartCutscene(Entity* entity, u16* script);
void ExecuteScriptForEntity(Entity* entity, void (*postScriptCallback)(Entity*, ScriptExecutionContext*));
void HandlePostScriptActions(Entity* entity, ScriptExecutionContext* context);
void HandleEntity0x82Actions(Entity* entity);
void sub_0807DD94(Entity*, void (*function)(Entity*, ScriptExecutionContext*));

#endif // SCRIPT_H
