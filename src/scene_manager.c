#include "scene_manager.h"

#include "splash.h"
#include "main_menu.h"
#include "gameplay.h"
#include "ending.h"

void SCENE_changeScenes(enum Scene scene) {
    currentScene = scene;

    switch (currentScene) {
        case SPLASH:
            SCENE_loadCurrentScene = &SCENE_Splash;
            break;
        case MAIN_MENU:
            SCENE_loadCurrentScene = &SCENE_MainMenu;
            break;
        case GAMEPLAY:
            SCENE_loadCurrentScene = &SCENE_Gameplay;
            break;
        case ENDING:
            SCENE_loadCurrentScene = &SCENE_Ending;
            break;
        default:
            break;
    }
}
