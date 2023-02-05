#include "gameplay.h"

#include "scene_manager.h"
#include "player.h"
#include "camera.h"
#include "input.h"

bool isPaused = FALSE;
bool showFPS = TRUE;
Character player;

Map* background;
Sprite* playerSprite;

void SCENE_Gameplay(u16* mainPalette, u16 userIndex) {
    VDP_clearPlane(BG_A, TRUE);
    DMA_waitCompletion();

    VDP_clearPlane(BG_B, TRUE);
    DMA_waitCompletion();

    // map setup
    PAL_setPalette(PAL0, game_pal.data, DMA);
    VDP_loadTileSet(&game_tileset, userIndex, DMA);
    background = MAP_create(&gamemap, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, userIndex));

    player = CHAR_init();

    SPR_init();
    PAL_setPalette(PAL3, player_sprite.palette->data, DMA);

    CAM_update(background, fix32ToInt(player.position.x), fix32ToInt(player.position.y));
    CAM_setSpritePosition(playerSprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));

    CAM_update(background, fix32ToInt(player.position.x) - 1, fix32ToInt(player.position.y) - 1);
    CAM_setSpritePosition(playerSprite, fix32ToInt(player.position.x) - 1, fix32ToInt(player.position.y) - 1);

    playerSprite = SPR_addSprite(&player_sprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y),
                                 TILE_ATTR(PAL3, 0, FALSE, FALSE));

    SPR_update();
    SYS_doVBlankProcess();

    while (currentScene == GAMEPLAY) {
        // map drawing
        // MAP_scrollTo(background, 0, 0);

        SPR_update();
        INPUT_joystickHandler(&player, isPaused);
        CHAR_movement(&player);

        if (showFPS) {
            VDP_showFPS(FALSE);
        }

        CAM_update(background, fix32ToInt(player.position.x), fix32ToInt(player.position.y));
        CAM_setSpritePosition(playerSprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));

        // wait vblank
        SYS_doVBlankProcess();
    }
}