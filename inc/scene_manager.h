#ifndef GGJ_2023_SCENE_MANAGER_H
#define GGJ_2023_SCENE_MANAGER_H

#include <genesis.h>
#include "resources.h"

typedef void (*SceneLoaderCallback) (u16*, u16);
enum Scene { SPLASH, MAIN_MENU, GAMEPLAY, ENDING };

enum Scene currentScene;
SceneLoaderCallback SCENE_loadCurrentScene;

void SCENE_changeScenes(enum Scene scene);

#endif //GGJ_2023_SCENE_MANAGER_H
