#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_message.h"
#include "bg.h"
#include "data.h"
#include "item_menu.h"
#include "link.h"
#include "main.h"
#include "m4a.h"
#include "palette.h"
#include "pokeball.h"
#include "pokeblock.h"
#include "pokemon.h"
#include "reshow_battle_screen.h"
#include "sound.h"
#include "task.h"
#include "text.h"
#include "util.h"
#include "window.h"
#include "constants/battle_anim.h"
#include "constants/songs.h"
#include "constants/rgb.h"

// this file's functions
static void SafariHandleGetMonData(void);
static void SafariHandleGetRawMonData(void);
static void SafariHandleSetMonData(void);
static void SafariHandleSetRawMonData(void);
static void SafariHandleLoadMonSprite(void);
static void SafariHandleSwitchInAnim(void);
static void SafariHandleReturnMonToBall(void);
static void SafariHandleDrawTrainerPic(void);
static void SafariHandleTrainerSlide(void);
static void SafariHandleTrainerSlideBack(void);
static void SafariHandleFaintAnimation(void);
static void SafariHandlePaletteFade(void);
static void SafariHandleSuccessBallThrowAnim(void);
static void SafariHandleBallThrowAnim(void);
static void SafariHandlePause(void);
static void SafariHandleMoveAnimation(void);
static void SafariHandlePrintString(void);
static void SafariHandlePrintSelectionString(void);
static void SafariHandleChooseAction(void);
static void SafariHandleUnknownYesNoBox(void);
static void SafariHandleChooseMove(void);
static void SafariHandleChooseItem(void);
static void SafariHandleChoosePokemon(void);
static void SafariHandleCmd23(void);
static void SafariHandleHealthBarUpdate(void);
static void SafariHandleExpUpdate(void);
static void SafariHandleStatusIconUpdate(void);
static void SafariHandleStatusAnimation(void);
static void SafariHandleStatusXor(void);
static void SafariHandleDataTransfer(void);
static void SafariHandleDMA3Transfer(void);
static void SafariHandlePlayBGM(void);
static void SafariHandleCmd32(void);
static void SafariHandleTwoReturnValues(void);
static void SafariHandleChosenMonReturnValue(void);
static void SafariHandleOneReturnValue(void);
static void SafariHandleOneReturnValue_Duplicate(void);
static void SafariHandleCmd37(void);
static void SafariHandleCmd38(void);
static void SafariHandleCmd39(void);
static void SafariHandleCmd40(void);
static void SafariHandleHitAnimation(void);
static void SafariHandleCmd42(void);
static void SafariHandlePlaySE(void);
static void SafariHandlePlayFanfareOrBGM(void);
static void SafariHandleFaintingCry(void);
static void SafariHandleIntroSlide(void);
static void SafariHandleIntroTrainerBallThrow(void);
static void SafariHandleDrawPartyStatusSummary(void);
static void SafariHandleHidePartyStatusSummary(void);
static void SafariHandleEndBounceEffect(void);
static void SafariHandleSpriteInvisibility(void);
static void SafariHandleBattleAnimation(void);
static void SafariHandleLinkStandbyMsg(void);
static void SafariHandleResetActionMoveSelection(void);
static void SafariHandleCmd55(void);
static void SafariCmdEnd(void);
static void SafariBufferRunCommand(void);
static void SafariBufferExecCompleted(void);
static void CompleteWhenChosePokeblock(void);

// START: Added Funciton Prototypes
static void NoPokeBufferRunCommand(void);
static void NoPokeHandleChooseAction(void);
static void HandleNoPokeInputChooseAction(void);
static void HandleNoPokeChooseActionAfterDma3(void);
static void CompleteOnBattlerSpriteCallbackDummy_NoPoke(void);
static void CompleteOnInactiveTextPrinter_NoPoke(void);
static void CompleteOnHealthboxSpriteCallbackDummy_NoPoke(void);
static void CompleteWhenChosePokeblock_NoPoke(void);
static void CompleteOnFinishedBattleAnimation(void);
static void NoPokeBufferExecCompleted(void);
static void CompleteOnFinishedStatusAnimation_NoPoke(void);
static void NoPokeHandleGetMonData(void);
static void NoPokeHandleGetRawMonData(void);
static void NoPokeHandleSetMonData(void);
static void NoPokeHandleSetRawMonData(void);
static void NoPokeHandleLoadMonSprite(void);
static void NoPokeHandleSwitchInAnim(void);
static void NoPokeHandleReturnMonToBall(void);
static void NoPokeHandleDrawTrainerPic(void);
static void NoPokeHandleTrainerSlide(void);
static void NoPokeHandleTrainerSlideBack(void);
static void NoPokeHandleFaintAnimation(void);
static void NoPokeHandlePaletteFade(void);
static void NoPokeHandleSuccessBallThrowAnim(void);
static void NoPokeHandleBallThrowAnim(void);
static void NoPokeHandlePause(void);
static void NoPokeHandleMoveAnimation(void);
static void NoPokeHandlePrintString(void);
static void NoPokeHandlePrintSelectionString(void);
static void CompleteOnSpecialAnimDone_NoPoke(void);
static void NoPokeHandleUnknownYesNoBox(void);
static void NoPokeHandleChooseMove(void);
static void NoPokeHandleChooseItem(void);
static void NoPokeHandleChoosePokemon(void);
static void NoPokeHandleCmd23(void);
static void NoPokeHandleHealthBarUpdate(void);
static void NoPokeHandleExpUpdate(void);
static void NoPokeHandleStatusIconUpdate(void);
static void NoPokeHandleStatusAnimation(void);
static void NoPokeHandleStatusXor(void);
static void NoPokeHandleDataTransfer(void);
static void NoPokeHandleDMA3Transfer(void);
static void NoPokeHandlePlayBGM(void);
static void NoPokeHandleCmd32(void);
static void NoPokeHandleTwoReturnValues(void);
static void NoPokeHandleChosenMonReturnValue(void);
static void NoPokeHandleOneReturnValue(void);
static void NoPokeHandleOneReturnValue_Duplicate(void);
static void NoPokeHandleCmd37(void);
static void NoPokeHandleCmd38(void);
static void NoPokeHandleCmd39(void);
static void NoPokeHandleCmd40(void);
static void NoPokeHandleHitAnimation(void);
static void NoPokeHandleCmd42(void);
static void NoPokeHandlePlaySE(void);
static void NoPokeHandlePlayFanfareOrBGM(void);
static void NoPokeHandleFaintingCry(void);
static void NoPokeHandleIntroSlide(void);
static void NoPokeHandleIntroTrainerBallThrow(void);
static void NoPokeHandleDrawPartyStatusSummary(void);
static void NoPokeHandleHidePartyStatusSummary(void);
static void NoPokeHandleEndBounceEffect(void);
static void NoPokeHandleSpriteInvisibility(void);
static void NoPokeHandleBattleAnimation(void);
static void NoPokeHandleLinkStandbyMsg(void);
static void NoPokeHandleResetActionMoveSelection(void);
static void NoPokeHandleCmd55(void);
static void NoPokeCmdEnd(void);
// END: Added Fuction Prototypes

static void (*const sSafariBufferCommands[CONTROLLER_CMDS_COUNT])(void) =
{
    SafariHandleGetMonData,
    SafariHandleGetRawMonData,
    SafariHandleSetMonData,
    SafariHandleSetRawMonData,
    SafariHandleLoadMonSprite,
    SafariHandleSwitchInAnim,
    SafariHandleReturnMonToBall,
    SafariHandleDrawTrainerPic,
    SafariHandleTrainerSlide,
    SafariHandleTrainerSlideBack,
    SafariHandleFaintAnimation,
    SafariHandlePaletteFade,
    SafariHandleSuccessBallThrowAnim,
    SafariHandleBallThrowAnim,
    SafariHandlePause,
    SafariHandleMoveAnimation,
    SafariHandlePrintString,
    SafariHandlePrintSelectionString,
    SafariHandleChooseAction,
    SafariHandleUnknownYesNoBox,
    SafariHandleChooseMove,
    SafariHandleChooseItem,
    SafariHandleChoosePokemon,
    SafariHandleCmd23,
    SafariHandleHealthBarUpdate,
    SafariHandleExpUpdate,
    SafariHandleStatusIconUpdate,
    SafariHandleStatusAnimation,
    SafariHandleStatusXor,
    SafariHandleDataTransfer,
    SafariHandleDMA3Transfer,
    SafariHandlePlayBGM,
    SafariHandleCmd32,
    SafariHandleTwoReturnValues,
    SafariHandleChosenMonReturnValue,
    SafariHandleOneReturnValue,
    SafariHandleOneReturnValue_Duplicate,
    SafariHandleCmd37,
    SafariHandleCmd38,
    SafariHandleCmd39,
    SafariHandleCmd40,
    SafariHandleHitAnimation,
    SafariHandleCmd42,
    SafariHandlePlaySE,
    SafariHandlePlayFanfareOrBGM,
    SafariHandleFaintingCry,
    SafariHandleIntroSlide,
    SafariHandleIntroTrainerBallThrow,
    SafariHandleDrawPartyStatusSummary,
    SafariHandleHidePartyStatusSummary,
    SafariHandleEndBounceEffect,
    SafariHandleSpriteInvisibility,
    SafariHandleBattleAnimation,
    SafariHandleLinkStandbyMsg,
    SafariHandleResetActionMoveSelection,
    SafariHandleCmd55,
    SafariCmdEnd,
    
};

static void (*const sNoPokeBufferCommands[CONTROLLER_CMDS_COUNT])(void) =
{
    NoPokeHandleGetMonData,
    NoPokeHandleGetRawMonData,
    NoPokeHandleSetMonData,
    NoPokeHandleSetRawMonData,
    NoPokeHandleLoadMonSprite,
    NoPokeHandleSwitchInAnim,
    NoPokeHandleReturnMonToBall,
    NoPokeHandleDrawTrainerPic,
    NoPokeHandleTrainerSlide,
    NoPokeHandleTrainerSlideBack,
    NoPokeHandleFaintAnimation,
    NoPokeHandlePaletteFade,
    NoPokeHandleSuccessBallThrowAnim,
    NoPokeHandleBallThrowAnim,
    NoPokeHandlePause,
    NoPokeHandleMoveAnimation,
    NoPokeHandlePrintString,
    NoPokeHandlePrintSelectionString,
    NoPokeHandleChooseAction,
    NoPokeHandleUnknownYesNoBox,
    NoPokeHandleChooseMove,
    NoPokeHandleChooseItem,
    NoPokeHandleChoosePokemon,
    NoPokeHandleCmd23,
    NoPokeHandleHealthBarUpdate,
    NoPokeHandleExpUpdate,
    NoPokeHandleStatusIconUpdate,
    NoPokeHandleStatusAnimation,
    NoPokeHandleStatusXor,
    NoPokeHandleDataTransfer,
    NoPokeHandleDMA3Transfer,
    NoPokeHandlePlayBGM,
    NoPokeHandleCmd32,
    NoPokeHandleTwoReturnValues,
    NoPokeHandleChosenMonReturnValue,
    NoPokeHandleOneReturnValue,
    NoPokeHandleOneReturnValue_Duplicate,
    NoPokeHandleCmd37,
    NoPokeHandleCmd38,
    NoPokeHandleCmd39,
    NoPokeHandleCmd40,
    NoPokeHandleHitAnimation,
    NoPokeHandleCmd42,
    NoPokeHandlePlaySE,
    NoPokeHandlePlayFanfareOrBGM,
    NoPokeHandleFaintingCry,
    NoPokeHandleIntroSlide,
    NoPokeHandleIntroTrainerBallThrow,
    NoPokeHandleDrawPartyStatusSummary,
    NoPokeHandleHidePartyStatusSummary,
    NoPokeHandleEndBounceEffect,
    NoPokeHandleSpriteInvisibility,
    NoPokeHandleBattleAnimation,
    NoPokeHandleLinkStandbyMsg,
    NoPokeHandleResetActionMoveSelection,
    NoPokeHandleCmd55,
    NoPokeCmdEnd,
};

static void SpriteCB_Null4(void)
{
}

void SetControllerToSafari(void)
{
    gBattlerControllerFuncs[gActiveBattler] = SafariBufferRunCommand;
}

void SetControllerToNoPoke(void)
{
    gBattlerControllerFuncs[gActiveBattler] = NoPokeBufferRunCommand;
}

static void SafariBufferRunCommand(void)
{
    if (gBattleControllerExecFlags & gBitTable[gActiveBattler])
    {
        if (gBattleBufferA[gActiveBattler][0] < ARRAY_COUNT(sSafariBufferCommands))
            sSafariBufferCommands[gBattleBufferA[gActiveBattler][0]]();
        else
            SafariBufferExecCompleted();
    }
}

static void HandleInputChooseAction(void)
{
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);

        switch (gActionSelectionCursor[gActiveBattler])
        {
        case 0:
            BtlController_EmitTwoReturnValues(1, B_ACTION_SAFARI_BALL, 0);
            break;
        case 1:
            BtlController_EmitTwoReturnValues(1, B_ACTION_SAFARI_POKEBLOCK, 0);
            break;
        case 2:
            BtlController_EmitTwoReturnValues(1, B_ACTION_SAFARI_GO_NEAR, 0);
            break;
        case 3:
            BtlController_EmitTwoReturnValues(1, B_ACTION_SAFARI_RUN, 0);
            break;
        }
        SafariBufferExecCompleted();
    }
    else if (gMain.newKeys & DPAD_LEFT)
    {
        if (gActionSelectionCursor[gActiveBattler] & 1)
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[gActiveBattler]);
            gActionSelectionCursor[gActiveBattler] ^= 1;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
        }
    }
    else if (gMain.newKeys & DPAD_RIGHT)
    {
        if (!(gActionSelectionCursor[gActiveBattler] & 1))
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[gActiveBattler]);
            gActionSelectionCursor[gActiveBattler] ^= 1;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
        }
    }
    else if (gMain.newKeys & DPAD_UP)
    {
        if (gActionSelectionCursor[gActiveBattler] & 2)
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[gActiveBattler]);
            gActionSelectionCursor[gActiveBattler] ^= 2;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
        }
    }
    else if (gMain.newKeys & DPAD_DOWN)
    {
        if (!(gActionSelectionCursor[gActiveBattler] & 2))
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[gActiveBattler]);
            gActionSelectionCursor[gActiveBattler] ^= 2;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
        }
    }
}

static void CompleteOnBattlerSpriteCallbackDummy(void)
{
    if (gSprites[gBattlerSpriteIds[gActiveBattler]].callback == SpriteCallbackDummy)
        SafariBufferExecCompleted();
}

static void CompleteOnInactiveTextPrinter(void)
{
    if (!IsTextPrinterActive(0))
        SafariBufferExecCompleted();
}

static void CompleteOnHealthboxSpriteCallbackDummy(void)
{
    if (gSprites[gHealthboxSpriteIds[gActiveBattler]].callback == SpriteCallbackDummy)
        SafariBufferExecCompleted();
}

static void sub_81595E4(void)
{
    if (!gPaletteFade.active)
    {
        gMain.inBattle = FALSE;
        gMain.callback1 = gPreBattleCallback1;
        SetMainCallback2(gMain.savedCallback);
    }
}

static void CompleteOnSpecialAnimDone(void)
{
    if (!gDoingBattleAnim || !gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].specialAnimActive)
        SafariBufferExecCompleted();
}

static void SafariOpenPokeblockCase(void)
{
    if (!gPaletteFade.active)
    {
        gBattlerControllerFuncs[gActiveBattler] = CompleteWhenChosePokeblock;
        FreeAllWindowBuffers();
        OpenPokeblockCaseInBattle();
    }
}

static void CompleteWhenChosePokeblock(void)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        BtlController_EmitOneReturnValue(1, gSpecialVar_ItemId);
        SafariBufferExecCompleted();
    }
}

static void CompleteOnFinishedBattleAnimation(void)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].animFromTableActive)
        SafariBufferExecCompleted();
}

static void SafariBufferExecCompleted(void)
{
    gBattlerControllerFuncs[gActiveBattler] = SafariBufferRunCommand;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        u8 playerId = GetMultiplayerId();

        PrepareBufferDataTransferLink(2, 4, &playerId);
        gBattleBufferA[gActiveBattler][0] = CONTROLLER_TERMINATOR_NOP;
    }
    else
    {
        gBattleControllerExecFlags &= ~gBitTable[gActiveBattler];
    }
}

static void CompleteOnFinishedStatusAnimation(void)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].statusAnimActive)
        SafariBufferExecCompleted();
}

static void SafariHandleGetMonData(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleGetRawMonData(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleSetMonData(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleSetRawMonData(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleLoadMonSprite(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleSwitchInAnim(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleReturnMonToBall(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleDrawTrainerPic(void)
{
    DecompressTrainerBackPic(gSaveBlock2Ptr->playerGender, gActiveBattler);
    SetMultiuseSpriteTemplateToTrainerBack(gSaveBlock2Ptr->playerGender, GetBattlerPosition(gActiveBattler));
    gBattlerSpriteIds[gActiveBattler] = CreateSprite(
      &gMultiuseSpriteTemplate,
      80,
      (8 - gTrainerBackPicCoords[gSaveBlock2Ptr->playerGender].size) * 4 + 80,
      30);
    gSprites[gBattlerSpriteIds[gActiveBattler]].oam.paletteNum = gActiveBattler;
    gSprites[gBattlerSpriteIds[gActiveBattler]].pos2.x = 240;
    gSprites[gBattlerSpriteIds[gActiveBattler]].data[0] = -2;
    gSprites[gBattlerSpriteIds[gActiveBattler]].callback = sub_805D7AC;
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnBattlerSpriteCallbackDummy;
}

static void SafariHandleTrainerSlide(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleTrainerSlideBack(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleFaintAnimation(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandlePaletteFade(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleSuccessBallThrowAnim(void)
{
    gBattleSpritesDataPtr->animationData->ballThrowCaseId = BALL_3_SHAKES_SUCCESS;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(gActiveBattler, gActiveBattler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_SAFARI_BALL_THROW);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnSpecialAnimDone;
}

static void SafariHandleBallThrowAnim(void)
{
    u8 ballThrowCaseId = gBattleBufferA[gActiveBattler][1];

    gBattleSpritesDataPtr->animationData->ballThrowCaseId = ballThrowCaseId;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(gActiveBattler, gActiveBattler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_SAFARI_BALL_THROW);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnSpecialAnimDone;
}

static void SafariHandlePause(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleMoveAnimation(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandlePrintString(void)
{
    u16 *stringId;

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    stringId = (u16*)(&gBattleBufferA[gActiveBattler][2]);
    BufferStringBattle(*stringId);
    BattlePutTextOnWindow(gDisplayedStringBattle, 0);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnInactiveTextPrinter;
}

static void SafariHandlePrintSelectionString(void)
{
    if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        SafariHandlePrintString();
    else
        SafariBufferExecCompleted();
}

static void HandleChooseActionAfterDma3(void)
{
    if (!IsDma3ManagerBusyWithBgCopy())
    {
        gBattle_BG0_X = 0;
        gBattle_BG0_Y = 160;
        gBattlerControllerFuncs[gActiveBattler] = HandleInputChooseAction;
    }
}

static void SafariHandleChooseAction(void)
{
    s32 i;

    gBattlerControllerFuncs[gActiveBattler] = HandleChooseActionAfterDma3;
    BattlePutTextOnWindow(gText_SafariZoneMenu, 2);

    for (i = 0; i < 4; i++)
        ActionSelectionDestroyCursorAt(i);

    ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
    BattleStringExpandPlaceholdersToDisplayedString(gText_WhatWillPkmnDo2);
    BattlePutTextOnWindow(gDisplayedStringBattle, 1);
}

static void SafariHandleUnknownYesNoBox(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleChooseMove(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleChooseItem(void)
{
    s32 i;

    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
    gBattlerControllerFuncs[gActiveBattler] = SafariOpenPokeblockCase;
    gBattlerInMenuId = gActiveBattler;
}

static void SafariHandleChoosePokemon(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleCmd23(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleHealthBarUpdate(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleExpUpdate(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleStatusIconUpdate(void)
{
    UpdateHealthboxAttribute(gHealthboxSpriteIds[gActiveBattler], &gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], HEALTHBOX_SAFARI_BALLS_TEXT);
    SafariBufferExecCompleted();
}

static void SafariHandleStatusAnimation(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleStatusXor(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleDataTransfer(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleDMA3Transfer(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandlePlayBGM(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleCmd32(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleTwoReturnValues(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleChosenMonReturnValue(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleOneReturnValue(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleOneReturnValue_Duplicate(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleCmd37(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleCmd38(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleCmd39(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleCmd40(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleHitAnimation(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleCmd42(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandlePlaySE(void)
{
    s8 pan;

    if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        pan = SOUND_PAN_ATTACKER;
    else
        pan = SOUND_PAN_TARGET;

    PlaySE12WithPanning(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8), pan);
    SafariBufferExecCompleted();
}

static void SafariHandlePlayFanfareOrBGM(void)
{
    if (gBattleBufferA[gActiveBattler][3])
    {
        BattleStopLowHpSound();
        PlayBGM(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8));
    }
    else
    {
        PlayFanfare(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8));
    }

    SafariBufferExecCompleted();
}

static void SafariHandleFaintingCry(void)
{
    u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], MON_DATA_SPECIES);

    PlayCry1(species, 25);
    SafariBufferExecCompleted();
}

static void SafariHandleIntroSlide(void)
{
    HandleIntroSlide(gBattleBufferA[gActiveBattler][1]);
    gIntroSlideFlags |= 1;
    SafariBufferExecCompleted();
}

static void SafariHandleIntroTrainerBallThrow(void)
{
    UpdateHealthboxAttribute(gHealthboxSpriteIds[gActiveBattler], &gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], HEALTHBOX_SAFARI_ALL_TEXT);
    sub_8076918(gActiveBattler);
    SetHealthboxSpriteVisible(gHealthboxSpriteIds[gActiveBattler]);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnHealthboxSpriteCallbackDummy;
}

static void SafariHandleDrawPartyStatusSummary(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleHidePartyStatusSummary(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleEndBounceEffect(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleSpriteInvisibility(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleBattleAnimation(void)
{
    u8 animationId = gBattleBufferA[gActiveBattler][1];
    u16 argument = gBattleBufferA[gActiveBattler][2] | (gBattleBufferA[gActiveBattler][3] << 8);

    if (TryHandleLaunchBattleTableAnimation(gActiveBattler, gActiveBattler, gActiveBattler, animationId, argument))
        SafariBufferExecCompleted();
    else
        gBattlerControllerFuncs[gActiveBattler] = CompleteOnFinishedBattleAnimation;
}

static void SafariHandleLinkStandbyMsg(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleResetActionMoveSelection(void)
{
    SafariBufferExecCompleted();
}

static void SafariHandleCmd55(void)
{
    gBattleOutcome = gBattleBufferA[gActiveBattler][1];
    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    SafariBufferExecCompleted();
    if ((gBattleTypeFlags & BATTLE_TYPE_LINK) && !(gBattleTypeFlags & BATTLE_TYPE_IS_MASTER))
        gBattlerControllerFuncs[gActiveBattler] = sub_81595E4;
}

static void SafariCmdEnd(void)
{
}

// ADDED: Start of functions for when user doesn't have a pokemon
static void NoPokeHandleChooseAction(void)
{
    s32 i;

    gBattlerControllerFuncs[gActiveBattler] = HandleNoPokeChooseActionAfterDma3;
    BattlePutTextOnWindow(gText_NoPokemonMenu, 2);

    for (i = 0; i < 4; i++)
        ActionSelectionDestroyCursorAt(i);

    ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
    BattleStringExpandPlaceholdersToDisplayedString(gText_WhatWillPkmnDo2);
    BattlePutTextOnWindow(gDisplayedStringBattle, 1);
}

static void HandleNoPokeInputChooseAction(void)
{
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);

        switch (gActionSelectionCursor[gActiveBattler])
        {
        case 0:
            BtlController_EmitTwoReturnValues(1, B_ACTION_SAFARI_BALL, 0);
            break;
        case 1:
            BtlController_EmitTwoReturnValues(1, B_ACTION_SAFARI_RUN, 0);
            break;
        case 2:
            BtlController_EmitTwoReturnValues(1, B_ACTION_SAFARI_RUN, 0);
            break;
        case 3:
            BtlController_EmitTwoReturnValues(1, B_ACTION_SAFARI_RUN, 0);
            break;
        }
        NoPokeBufferExecCompleted();
    }
    else if (gMain.newKeys & DPAD_LEFT)
    {
        if (gActionSelectionCursor[gActiveBattler] & 1)
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[gActiveBattler]);
            gActionSelectionCursor[gActiveBattler] ^= 1;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
        }
    }
    else if (gMain.newKeys & DPAD_RIGHT)
    {
        if (!(gActionSelectionCursor[gActiveBattler] & 1))
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[gActiveBattler]);
            gActionSelectionCursor[gActiveBattler] ^= 1;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
        }
    }
    else if (gMain.newKeys & DPAD_UP)
    {
        if (gActionSelectionCursor[gActiveBattler] & 2)
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[gActiveBattler]);
            gActionSelectionCursor[gActiveBattler] ^= 2;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
        }
    }
    else if (gMain.newKeys & DPAD_DOWN)
    {
        if (!(gActionSelectionCursor[gActiveBattler] & 2))
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[gActiveBattler]);
            gActionSelectionCursor[gActiveBattler] ^= 2;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
        }
    }
}

static void HandleNoPokeChooseActionAfterDma3(void)
{
    if (!IsDma3ManagerBusyWithBgCopy())
    {
        gBattle_BG0_X = 0;
        gBattle_BG0_Y = 160;
        gBattlerControllerFuncs[gActiveBattler] = HandleNoPokeInputChooseAction;
    }
}

static void NoPokeBufferRunCommand(void)
{
    if (gBattleControllerExecFlags & gBitTable[gActiveBattler])
    {
        if (gBattleBufferA[gActiveBattler][0] < ARRAY_COUNT(sNoPokeBufferCommands))
            sNoPokeBufferCommands[gBattleBufferA[gActiveBattler][0]]();
        else
            NoPokeBufferExecCompleted();
    }
}

static void CompleteOnBattlerSpriteCallbackDummy_NoPoke(void)
{
    if (gSprites[gBattlerSpriteIds[gActiveBattler]].callback == SpriteCallbackDummy)
        NoPokeBufferExecCompleted();
}

static void CompleteOnInactiveTextPrinter_NoPoke(void)
{
    if (!IsTextPrinterActive(0))
        NoPokeBufferExecCompleted();
}

static void CompleteOnHealthboxSpriteCallbackDummy_NoPoke(void)
{
    if (gSprites[gHealthboxSpriteIds[gActiveBattler]].callback == SpriteCallbackDummy)
        NoPokeBufferExecCompleted();
}

static void CompleteWhenChosePokeblock_NoPoke(void)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        BtlController_EmitOneReturnValue(1, gSpecialVar_ItemId);
        NoPokeBufferExecCompleted();
    }
}

static void CompleteOnFinishedBattleAnimation_NoPoke(void)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].animFromTableActive)
        NoPokeBufferExecCompleted();
}

static void NoPokeBufferExecCompleted(void)
{
    gBattlerControllerFuncs[gActiveBattler] = NoPokeBufferRunCommand;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        u8 playerId = GetMultiplayerId();

        PrepareBufferDataTransferLink(2, 4, &playerId);
        gBattleBufferA[gActiveBattler][0] = CONTROLLER_TERMINATOR_NOP;
    }
    else
    {
        gBattleControllerExecFlags &= ~gBitTable[gActiveBattler];
    }
}

static void CompleteOnFinishedStatusAnimation_NoPoke(void)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].statusAnimActive)
        NoPokeBufferExecCompleted();
}

static void NoPokeHandleGetMonData(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleGetRawMonData(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleSetMonData(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleSetRawMonData(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleLoadMonSprite(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleSwitchInAnim(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleReturnMonToBall(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleDrawTrainerPic(void)
{
    DecompressTrainerBackPic(gSaveBlock2Ptr->playerGender, gActiveBattler);
    SetMultiuseSpriteTemplateToTrainerBack(gSaveBlock2Ptr->playerGender, GetBattlerPosition(gActiveBattler));
    gBattlerSpriteIds[gActiveBattler] = CreateSprite(
      &gMultiuseSpriteTemplate,
      80,
      (8 - gTrainerBackPicCoords[gSaveBlock2Ptr->playerGender].size) * 4 + 80,
      30);
    gSprites[gBattlerSpriteIds[gActiveBattler]].oam.paletteNum = gActiveBattler;
    gSprites[gBattlerSpriteIds[gActiveBattler]].pos2.x = 240;
    gSprites[gBattlerSpriteIds[gActiveBattler]].data[0] = -2;
    gSprites[gBattlerSpriteIds[gActiveBattler]].callback = sub_805D7AC;
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnBattlerSpriteCallbackDummy_NoPoke;
}

static void NoPokeHandleTrainerSlide(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleTrainerSlideBack(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleFaintAnimation(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandlePaletteFade(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleSuccessBallThrowAnim(void)
{
    gBattleSpritesDataPtr->animationData->ballThrowCaseId = BALL_3_SHAKES_SUCCESS;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(gActiveBattler, gActiveBattler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_SAFARI_BALL_THROW);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnSpecialAnimDone_NoPoke;
}

static void NoPokeHandleBallThrowAnim(void)
{
    u8 ballThrowCaseId = gBattleBufferA[gActiveBattler][1];

    gBattleSpritesDataPtr->animationData->ballThrowCaseId = ballThrowCaseId;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(gActiveBattler, gActiveBattler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_SAFARI_BALL_THROW);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnSpecialAnimDone_NoPoke;
}

static void NoPokeHandlePause(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleMoveAnimation(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandlePrintString(void)
{
    u16 *stringId;

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    stringId = (u16*)(&gBattleBufferA[gActiveBattler][2]);
    BufferStringBattle(*stringId);
    BattlePutTextOnWindow(gDisplayedStringBattle, 0);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnInactiveTextPrinter_NoPoke;
}

static void NoPokeHandlePrintSelectionString(void)
{
    if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        NoPokeHandlePrintString();
    else
        NoPokeBufferExecCompleted();
}

static void CompleteOnSpecialAnimDone_NoPoke(void)
{
    if (!gDoingBattleAnim || !gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].specialAnimActive)
        NoPokeBufferExecCompleted();
}

static void NoPokeHandleUnknownYesNoBox(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleChooseMove(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleChooseItem(void)
{
    s32 i;

    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
    gBattlerControllerFuncs[gActiveBattler] = NoPokeHandleChoosePokemon;
    gBattlerInMenuId = gActiveBattler;
}

static void NoPokeHandleChoosePokemon(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleCmd23(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleHealthBarUpdate(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleExpUpdate(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleStatusIconUpdate(void)
{
    UpdateHealthboxAttribute(gHealthboxSpriteIds[gActiveBattler], &gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], HEALTHBOX_NOPOKE_ALL);
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleStatusAnimation(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleStatusXor(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleDataTransfer(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleDMA3Transfer(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandlePlayBGM(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleCmd32(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleTwoReturnValues(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleChosenMonReturnValue(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleOneReturnValue(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleOneReturnValue_Duplicate(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleCmd37(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleCmd38(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleCmd39(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleCmd40(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleHitAnimation(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleCmd42(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandlePlaySE(void)
{
    s8 pan;

    if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        pan = SOUND_PAN_ATTACKER;
    else
        pan = SOUND_PAN_TARGET;

    PlaySE12WithPanning(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8), pan);
    NoPokeBufferExecCompleted();
}

static void NoPokeHandlePlayFanfareOrBGM(void)
{
    if (gBattleBufferA[gActiveBattler][3])
    {
        BattleStopLowHpSound();
        PlayBGM(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8));
    }
    else
    {
        PlayFanfare(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8));
    }

    NoPokeBufferExecCompleted();
}

static void NoPokeHandleFaintingCry(void)
{
    u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], MON_DATA_SPECIES);

    PlayCry1(species, 25);
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleIntroSlide(void)
{
    HandleIntroSlide(gBattleBufferA[gActiveBattler][1]);
    gIntroSlideFlags |= 1;
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleIntroTrainerBallThrow(void)
{
    UpdateHealthboxAttribute(gHealthboxSpriteIds[gActiveBattler], &gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], HEALTHBOX_NOPOKE_ALL);
    sub_8076918(gActiveBattler);
    SetHealthboxSpriteVisible(gHealthboxSpriteIds[gActiveBattler]);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnHealthboxSpriteCallbackDummy_NoPoke;
}

static void NoPokeHandleDrawPartyStatusSummary(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleHidePartyStatusSummary(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleEndBounceEffect(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleSpriteInvisibility(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleBattleAnimation(void)
{
    u8 animationId = gBattleBufferA[gActiveBattler][1];
    u16 argument = gBattleBufferA[gActiveBattler][2] | (gBattleBufferA[gActiveBattler][3] << 8);

    if (TryHandleLaunchBattleTableAnimation(gActiveBattler, gActiveBattler, gActiveBattler, animationId, argument))
        NoPokeBufferExecCompleted();
    else
        gBattlerControllerFuncs[gActiveBattler] = CompleteOnFinishedBattleAnimation_NoPoke;
}

static void NoPokeHandleLinkStandbyMsg(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleResetActionMoveSelection(void)
{
    NoPokeBufferExecCompleted();
}

static void NoPokeHandleCmd55(void)
{
    gBattleOutcome = gBattleBufferA[gActiveBattler][1];
    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    NoPokeBufferExecCompleted();
    if ((gBattleTypeFlags & BATTLE_TYPE_LINK) && !(gBattleTypeFlags & BATTLE_TYPE_IS_MASTER))
        gBattlerControllerFuncs[gActiveBattler] = sub_81595E4;
}

static void NoPokeCmdEnd(void)
{
}

// END of functions for when user doesn't have any pokemon

