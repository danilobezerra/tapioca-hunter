#include "scene_manager.h"

#include "splash.h"
#include "main_menu.h"
#include "gameplay.h"
#include "ending.h"

void SCENE_set(enum Scene scene) {
    currentScene = scene;

    switch (currentScene) {
        case SPLASH:
            SCENE_loadCurrentScene = &SCENE_Splash;

            if (XGM_isPlaying()) {
                XGM_stopPlay();
            }

            break;
        case MAIN_MENU:
            SCENE_loadCurrentScene = &SCENE_MainMenu;
            XGM_startPlay(FAR_SAFE(&main_menu_bgm, sizeof(main_menu_bgm)));
            break;
        case GAMEPLAY:
            SCENE_loadCurrentScene = &SCENE_Gameplay;
            XGM_startPlay(FAR_SAFE(&gameplay_bgm, sizeof(gameplay_bgm)));
            break;
        case ENDING:
            SCENE_loadCurrentScene = &SCENE_Ending;
            XGM_startPlay(FAR_SAFE(&ending_bgm, sizeof(ending_bgm)));
            break;
        default:
            break;
    }
}
