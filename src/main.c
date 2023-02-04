#include <genesis.h>
#include "scene_manager.h"

bool isRunning = TRUE;

u16 mainPalette[64];
u16 userIndex;

int main() {
    JOY_init();
    SPR_init();

    PAL_setColors(0, palette_black, 64, DMA);
    userIndex = TILE_USER_INDEX;

    SCENE_changeScenes(SPLASH);

    // game loop
    while (isRunning) {
        SCENE_loadCurrentScene(mainPalette, userIndex);
        SYS_doVBlankProcess();
    }

    // free map
    //MEM_free(background);

    return 0;
}

