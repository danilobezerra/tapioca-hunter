#include <genesis.h>
#include <resources.h>
#include "player.h"
#include "camera.h"
#include "input.h"

enum Scene { SPLASH, MAIN_MENU, GAMEPLAY, ENDING };
enum Scene currentScene;

bool isRunning = TRUE;
bool isPaused = FALSE;
bool showFPS = TRUE;
Character player;

Map* background;
Sprite* playerSprite;

u16 mainPalette[64];
u16 userIndex;

void SCENE_loadSplash() {
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

    currentScene = MAIN_MENU;
}

void SCENE_loadMainMenu() {
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
            currentScene = GAMEPLAY;
        }

        SYS_doVBlankProcess();
    }

    //VDP_clearTextArea(11, 16, 19, 1);

    PAL_fadeOutAll(20, FALSE);
    waitTick(TICKPERSECOND / 2);
}

void SCENE_loadGameplay() {
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
    CAM_setPosition(background, playerSprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));
    CAM_setPosition(background, playerSprite, fix32ToInt(player.position.x) - 1, fix32ToInt(player.position.y) - 1);

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

        CAM_setPosition(background, playerSprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));

        // wait vblank
        SYS_doVBlankProcess();
    }
}

void SCENE_loadEnding() {
    // TODO: The End?
}

int main() {
    currentScene = SPLASH;

    JOY_init();
    SPR_init();

    PAL_setColors(0, palette_black, 64, DMA);
    userIndex = TILE_USER_INDEX;

    // game loop
    while (isRunning) {

        switch (currentScene) {
            case SPLASH:
                SCENE_loadSplash();
                break;
            case MAIN_MENU:
                SCENE_loadMainMenu();
                break;
            case GAMEPLAY:
                SCENE_loadGameplay();
                break;
            case ENDING:
                SCENE_loadEnding();
                break;
            default:
                break;
        }
    }

    // free map
    //MEM_free(background);

    return 0;
}

