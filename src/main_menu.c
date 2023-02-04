#include "main_menu.h"

#include "scene_manager.h"

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
    PAL_waitFadeCompletion();
    VDP_drawText("Press START button", 11, 20);

    while (currentScene == MAIN_MENU) {
        u16 value = JOY_readJoypad(JOY_1);

        if (value & BUTTON_START) {
            SCENE_changeScenes(GAMEPLAY);
        }

        SYS_doVBlankProcess();
    }

    //VDP_clearTextArea(11, 16, 19, 1);

    PAL_fadeOutAll(20, FALSE);
    waitTick(TICKPERSECOND / 2);
}