// generated with scripts/generate_hitboxes_code.lua script

#ifndef GGJ_2023_HITBOXES_H
#define GGJ_2023_HITBOXES_H

#include <genesis.h>
#include "game_math.h"
#include "collision_mask.h"

static const Box hitboxes[] = {
  { .x = 80, .y = 48, .w = 56, .h = 8 }, /* 1 */
  { .x = 128, .y = 120, .w = 64, .h = 8 }, /* 2 */
  { .x = 128, .y = 56, .w = 8, .h = 64 }, /* 3 */
};

#define HB_COUNT 3

CollisionMask HB_get_collision_mask(Box bb);

#endif // GGJ_2023_HITBOXES_H
