#include "gameplay.h"

#include "scene_manager.h"
#include "player.h"
#include "camera.h"
#include "input.h"
#include "enemies_init.h"
#include "enemies.h"
#include "tapiocas.h"

bool isPaused = FALSE;
bool showFPS = TRUE;
Character player;

Map* background;
Map* foreground;
Sprite* playerSprite;

void SCENE_Gameplay(u16* mainPalette, u16 userIndex) {
    VDP_clearPlane(BG_A, TRUE);
    DMA_waitCompletion();

    VDP_clearPlane(BG_B, TRUE);
    DMA_waitCompletion();

    // map setup
    PAL_setPalette(PAL0, game_pal.data, DMA);
    VDP_loadTileSet(&game_tileset, userIndex, DMA);
    background = MAP_create(&gamemap, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, userIndex));
    foreground = MAP_create(&foremap, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, userIndex));

    player = CHAR_init();

    SPR_init();
    PAL_setPalette(PAL3, player_sprite.palette->data, DMA);

    CAM_update(foreground, background, fix32ToInt(player.position.x), fix32ToInt(player.position.y));
    CAM_setSpritePosition(playerSprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));

    CAM_update(foreground, background, fix32ToInt(player.position.x) - 1, fix32ToInt(player.position.y) - 1);
    CAM_setSpritePosition(playerSprite, fix32ToInt(player.position.x) - 1, fix32ToInt(player.position.y) - 1);

    playerSprite = SPR_addSprite(&player_sprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y),
                                 TILE_ATTR(PAL3, 0, FALSE, FALSE));

    ENEMIES_init();
    TAPIOCAS_init();
        
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

        SPR_setHFlip(playerSprite, player.direction < 0);
        
        CAM_update(foreground, background, fix32ToInt(player.position.x), fix32ToInt(player.position.y));
        CAM_setSpritePosition(playerSprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));

        TAPIOCAS_update(&player);
        ENEMIES_update(&player);
        
        if (player.isDead || TAPIOCAS_getCount() == 0 ) {
            SCENE_set(ENDING);
        }
        
        // wait vblank
        SYS_doVBlankProcess();
    }

    PAL_fadeOutAll(15, FALSE);
    CAM_update(foreground, background, 0, 0);
    ENEMIES_clear();
    TAPIOCAS_clear();
    SPR_releaseSprite(playerSprite);
    SPR_update();
    waitTick(TICKPERSECOND / 2);
}