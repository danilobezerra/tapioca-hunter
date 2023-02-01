#include <genesis.h>
#include "resources.h"

bool isRunning = TRUE;

int main() {
    u16 idx = TILE_USER_INDEX;

    PAL_setPalette(PAL0, game_pal.data, DMA);
    VDP_loadTileSet(&game_tileset, idx, DMA);
    Map* bga = MAP_create(&gamemap, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx));

    while (isRunning) {
        MAP_scrollTo(bga, 0, 0);
        SYS_doVBlankProcess();
    }

    MEM_free(bga);

    return 0;
}

