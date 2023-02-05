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
    *out_ghost_sprite = SPR_addSprite(&player_sprite, x, y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
}

void ENEMIES_init() {
    GHOST_init(&ghosts[0], &ghosts_sprites[0], 160, 152);
    GHOST_init(&ghosts[1], &ghosts_sprites[1], 336, 128);
    GHOST_init(&ghosts[2], &ghosts_sprites[2], 272, 152);
    GHOST_init(&ghosts[3], &ghosts_sprites[3], 368, 128);
    GHOST_init(&ghosts[4], &ghosts_sprites[4], 400, 128);
    GHOST_init(&ghosts[5], &ghosts_sprites[5], 240, 96);
}
