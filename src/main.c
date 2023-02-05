#include <genesis.h>
#include "scene_manager.h"

#define SFX_ENTER 64
#define SFX_ATTACK 65
#define SFX_JUMP 66
#define SFX_WALK 67
//#define SFX_DEATH 68
#define SFX_EAT 69

bool isRunning = TRUE;

u16 mainPalette[64];
u16 userIndex;

int main() {
    JOY_init();
    SPR_init();

    XGM_setPCM(SFX_ENTER, sfx_enter, sizeof(sfx_enter));
    XGM_setPCM(SFX_JUMP, sfx_jump, sizeof(sfx_jump));
    XGM_setPCM(SFX_WALK, sfx_walk, sizeof(sfx_walk));
    XGM_setPCM(SFX_ATTACK, sfx_attack, sizeof(sfx_attack));
    //XGM_setPCM(SFX_DEATH, sfx_death, sizeof(sfx_death));
    XGM_setPCM(SFX_EAT, sfx_attack, sizeof(sfx_attack));

    PAL_setColors(0, palette_black, 64, DMA);
    userIndex = TILE_USER_INDEX;

    SCENE_set(SPLASH);

    while (isRunning) {
        SCENE_loadCurrentScene(mainPalette, userIndex);
        SYS_doVBlankProcess();
    }

    return 0;
}

