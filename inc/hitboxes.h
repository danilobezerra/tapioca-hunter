// generated with scripts/generate_hitboxes_code.lua script

#ifndef GGJ_2023_HITBOXES_H
#define GGJ_2023_HITBOXES_H

#include <genesis.h>
#include "game_math.h"
#include "collision_mask.h"

static const Box hitboxes[] = {
  { .x = 16, .y = 48, .w = 120, .h = 8 }, /* 1 */
  { .x = 128, .y = 120, .w = 64, .h = 8 }, /* 2 */
  { .x = 16, .y = 0, .w = 8, .h = 48 }, /* 3 */
  { .x = 128, .y = 56, .w = 8, .h = 64 }, /* 4 */
  { .x = 184, .y = 128, .w = 8, .h = 56 }, /* 5 */
};

#define HB_COUNT 5

CollisionMask HB_get_collision_mask(Box bb);

#endif // GGJ_2023_HITBOXES_H
