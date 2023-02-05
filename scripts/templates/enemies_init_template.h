#ifndef GGJ_2023_ENEMIES_INIT_H
#define GGJ_2023_ENEMIES_INIT_H

#include <genesis.h>
#include "player.h"

// GHOST_COUNT //

Character ghosts[GHOST_COUNT];
Sprite* ghosts_sprites[GHOST_COUNT];

void ENEMIES_clear();
void GHOST_init(Character* out_ghost, Sprite** out_ghost_sprite, s32 x, s32 y);
void ENEMIES_init();

#endif // GGJ_2023_ENEMIES_INIT_H
