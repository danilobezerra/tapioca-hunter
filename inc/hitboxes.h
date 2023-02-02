// generated with scripts/generate_hitboxes_code.lua script

#ifndef GGJ_2023_HITBOXES_H
#define GGJ_2023_HITBOXES_H

#include <genesis.h>
#include "game_math.h"
#include "collision_mask.h"

static const Box hitboxes[] = {
  { .x = 4, .y = 1, .w = 4, .h = 1 }, /* 1 */
  { .x = 2, .y = 3, .w = 6, .h = 1 }, /* 2 */
  { .x = 10, .y = 1, .w = 1, .h = 3 }, /* 3 */
  { .x = 1, .y = 1, .w = 1, .h = 1 }, /* 4 */
  { .x = 2, .y = 5, .w = 1, .h = 1 }, /* 5 */
};

#define HB_COUNT 5

CollisionMask HB_get_collision_mask(Box bb);

#endif // GGJ_2023_HITBOXES_H
