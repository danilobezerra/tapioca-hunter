#ifndef GGJ_2023_ENEMIES_H
#define GGJ_2023_ENEMIES_H

#include <genesis.h>
#include "player.h"
#include "game_math.h"

Box GHOST_hitbox(Character* character);
void GHOST_update(u16 idx, s32 x, s32 y, Character* player);
void ENEMIES_update(Character* player);

#endif // GGJ_2023_ENEMIES_H

