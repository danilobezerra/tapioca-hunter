#include <genesis.h>
#include "resources.h"

bool isRunning = TRUE;

int main() {
    u16 idx = TILE_USER_INDEX;

    // map setup
    PAL_setPalette(PAL0, game_pal.data, DMA);
    VDP_loadTileSet(&game_tileset, idx, DMA);
    Map* bga = MAP_create(&gamemap, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx));

    // game loop
    while (isRunning) {
        // map drawing
        MAP_scrollTo(bga, 0, 0);

        // wait vblank
        SYS_doVBlankProcess();
    }

    // free map
    MEM_free(bga);

    return 0;
}

