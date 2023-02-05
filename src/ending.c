#include "ending.h"

#include "tapiocas.h"

void SCENE_Ending(u16* mainPalette, u16 userIndex) {
    VDP_clearPlane(BG_A, TRUE);
    DMA_waitCompletion();

    VDP_clearPlane(BG_B, TRUE);
    DMA_waitCompletion();

    userIndex = TILE_USER_INDEX;

    if (TAPIOCAS_getCount() > 0) {
        VDP_drawImageEx(BG_B, &lose_screen, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, userIndex), 0, 0, FALSE, TRUE);
        memcpy(&mainPalette[0], lose_screen.palette->data, 32);
    } else {
        VDP_drawImageEx(BG_B, &win_screen, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, userIndex), 0, 0, FALSE, TRUE);
        memcpy(&mainPalette[0], win_screen.palette->data, 32);
    }

    PAL_fadeIn(0, 63, mainPalette, 60, FALSE);

    while (currentScene == ENDING) {
        /*u16 value = JOY_readJoypad(JOY_1);

        if (value & BUTTON_START) {
            SCENE_set(SPLASH);
        }*/

        SYS_doVBlankProcess();
    }

    PAL_fadeOutAll(30, FALSE);
    waitTick(TICKPERSECOND);
}
