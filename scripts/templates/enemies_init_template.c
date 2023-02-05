#include <genesis.h>
#include <maths.h>
#include <tools.h>

#include "enemies_init.h"
#include "player.h"
#include "resources.h"
#include "ggj_debug.h"
#include "camera.h"

void GHOST_init(Character* out_ghost, Sprite** out_ghost_sprite, s32 x, s32 y) {
    Character ghost = CHAR_init();
    ghost.tag = ENTITY_TAG_GHOST;
    ghost.position.x = FIX32(x);
    ghost.position.y = FIX32(y);
    *out_ghost = ghost;
    *out_ghost_sprite = SPR_addSprite(&ghost_sprite, x, y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
}

void ENEMIES_clear() {
    for (int i = 0; i < GHOST_COUNT; ++i) {
        SPR_releaseSprite(ghosts_sprites[i]);
    }
}

void ENEMIES_init() {
// GHOSTS INIT //
}
