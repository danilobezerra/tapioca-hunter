#include "splash.h"

#include "scene_manager.h"

void SCENE_Splash(u16* mainPalette, u16 userIndex) {
    VDP_clearPlane(BG_A, TRUE);
    DMA_waitCompletion();

    VDP_clearPlane(BG_B, TRUE);
    DMA_waitCompletion();

    VDP_drawImageEx(BG_B, &splash, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, userIndex), 0, 0, FALSE, TRUE);
    userIndex += splash.tileset->numTile;

    memcpy(&mainPalette[0], splash.palette->data, 32);

    PAL_fadeIn(0, 63, mainPalette, 20, FALSE);
    JOY_setEventHandler(NULL);
    waitTick(TICKPERSECOND * 3);

    PAL_fadeOutAll(20, FALSE);
    waitTick(TICKPERSECOND / 2);

    SCENE_set(MAIN_MENU);
}