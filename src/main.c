#include <genesis.h>
#include <resources.h>
#include "player.h"
#include "camera.h"

bool isRunning = TRUE;
bool showFPS = TRUE;
Character player;

Map* background;
Sprite* playerSprite;

int main() {
    u16 idx = TILE_USER_INDEX;

    // map setup
    PAL_setPalette(PAL0, game_pal.data, DMA);
    VDP_loadTileSet(&game_tileset, idx, DMA);
    background = MAP_create(&gamemap, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx));

    player.isMoving = FALSE;
    player.position.x = FIX32(160);
    player.position.y = FIX32(950);
    player.speed.x = 0;
    player.speed.y = 0;

    SPR_init();
    PAL_setPalette(PAL3, player_sprite.palette->data, DMA);
    CAM_setPosition(background, playerSprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));
    CAM_setPosition(background, playerSprite, fix32ToInt(player.position.x) - 1, fix32ToInt(player.position.y) - 1);

    playerSprite = SPR_addSprite(&player_sprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y),
                                 TILE_ATTR(PAL3, 0, FALSE, FALSE));

    SPR_update();
    SYS_doVBlankProcess();

    // game loop
    while (isRunning) {
        // map drawing
        // MAP_scrollTo(background, 0, 0);

        SPR_update();

        if (showFPS) {
            VDP_showFPS(FALSE);
        }

        CAM_setPosition(background, playerSprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));

        // wait vblank
        SYS_doVBlankProcess();
    }

    // free map
    //MEM_free(background);

    return 0;
}

