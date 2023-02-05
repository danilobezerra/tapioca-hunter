#ifndef GGJ_2023_ENEMIES_H
#define GGJ_2023_ENEMIES_H

#include <genesis.h>
#include "player.h"
#include "game_math.h"

Box GHOST_hitbox(Character* character);
void GHOST_update_sprite(Character* ghost, Sprite* sprite);
void GHOST_die(Character* ghost, Sprite* sprite);
void GHOST_update(u16 idx, s32 x, s32 y, Character* player, Box atk);
void ENEMIES_update(Character* player);

#endif // GGJ_2023_ENEMIES_H

