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
    kprintf("ginit 1>  %d", ghost.tag);
    ghost.position.x = FIX32(x);
    ghost.position.y = FIX32(y);
    *out_ghost = ghost;
    *out_ghost_sprite = SPR_addSprite(&player_sprite, x, y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
    kprintf("ginit 2> %d", out_ghost->tag);
}

void ENEMIES_init() {
    GHOST_init(&ghosts[0], &ghosts_sprites[0], 48, 48);
    kprintf("ginit 3> %d", ghosts[0].tag);
}
