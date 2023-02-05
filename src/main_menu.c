#include "main_menu.h"

#include "scene_manager.h"

#define SFX_ENTER 64

u8 tickCount = 0;

void blinkText() {
    tickCount++;

    if (tickCount >= 60) {
        tickCount = 0;
    }

    VDP_setTextPalette(tickCount < 30 ? PAL2 : PAL0);
    VDP_drawText("Press START button", 11, 20);
}

void SCENE_MainMenu(u16* mainPalette, u16 userIndex) {
    VDP_clearPlane(BG_A, TRUE);
    DMA_waitCompletion();

    VDP_clearPlane(BG_B, TRUE);
    DMA_waitCompletion();

    userIndex = TILE_USER_INDEX;

    VDP_drawImageEx(BG_B, &title, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, userIndex), 0, 0, FALSE, TRUE);
    memcpy(&mainPalette[0], title.palette->data, 31);

    VDP_drawText(" GGJ 2023 - Baixada Santista ", 5, 23);
    VDP_drawText("Programming by Danilo & Andre", 5, 25);
    VDP_drawText("   Graphic/Music by Marcio   ", 5, 26);

    PAL_fadeIn(0, 63, mainPalette, 60, FALSE);

    while (currentScene == MAIN_MENU) {
        u16 value = JOY_readJoypad(JOY_1);

        if (value & BUTTON_START) {
            XGM_startPlayPCM(SFX_ENTER,1,SOUND_PCM_CH2);
            SCENE_set(GAMEPLAY);
        }

        blinkText();
        SYS_doVBlankProcess();
    }

    PAL_fadeOutAll(30, FALSE);
    waitTick(TICKPERSECOND);
}