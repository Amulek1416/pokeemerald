#ifndef GUARD_SAFARI_ZONE_H
#define GUARD_SAFARI_ZONE_H

extern u8 gNumSafariBalls;
extern u8 gNumDustyPokeballs;

bool32 GetSafariZoneFlag(void);
void SetSafariZoneFlag(void);
void ResetSafariZoneFlag(void);

void EnterSafariMode(void);
void ExitSafariMode(void);

bool8 SafariZoneTakeStep(void);
void SafariZoneRetirePrompt(void);

void CB2_EndSafariBattle(void);

struct Pokeblock *SafariZoneGetActivePokeblock(void);
void SafariZoneActivatePokeblockFeeder(u8 pokeblock_index);

// ADDED: Handle when user has no pokemon
void EnterNoPokeMode(void);
void ExitNoPokeMode(void);
void CB2_EndNoPokeBattle(void);
bool32 GetNoPokeModeFlag(void);

#endif // GUARD_SAFARI_ZONE_H
