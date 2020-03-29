#ifndef GUARD_SCRIPT_POKEMON_UTIL_80F87D8_H
#define GUARD_SCRIPT_POKEMON_UTIL_80F87D8_H

u16 GetContestRand(void);
void ReducePlayerPartyToSelectedMons(void);
u8 CountPlayerContestPaintings(void);

/**
 * START OF CODE MODIFIED FROM ORIGINAL
 */

// ORIGINAL
// void HealPlayerParty(void);

// MODIFIED
u8 HealPlayerParty(bool8 atCenter);

/**
 * END OF MODIFIED CODE
 */

/**
 * START OF FUNCTION PROTOTYPES ADDED TO ORIGINAL CODE
 */
u8 HealAtPokeCenter(void);
u8 HealOutsidePokeCenter(void);
/**
 * END OF ADDED FUNCTION PROTOTYPES
 */ 

#endif // GUARD_SCRIPT_POKEMON_UTIL_80F87D8_H
