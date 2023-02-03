// generated with scripts/generate_hitboxes_code.lua script

#ifndef GGJ_2023_HITBOXES_H
#define GGJ_2023_HITBOXES_H

#include <genesis.h>
#include "game_math.h"
#include "collision_mask.h"

static const Box hitboxes[] = {
  { .x = 0, .y = 4, .w = 23, .h = 1 }, /* 1 */
  { .x = 38, .y = 17, .w = 2, .h = 1 }, /* 2 */
  { .x = 38, .y = 18, .w = 4, .h = 1 }, /* 3 */
  { .x = 38, .y = 19, .w = 4, .h = 1 }, /* 4 */
  { .x = 38, .y = 20, .w = 4, .h = 1 }, /* 5 */
  { .x = 38, .y = 21, .w = 4, .h = 1 }, /* 6 */
  { .x = 38, .y = 22, .w = 4, .h = 1 }, /* 7 */
  { .x = 24, .y = 23, .w = 2, .h = 1 }, /* 8 */
  { .x = 38, .y = 23, .w = 4, .h = 1 }, /* 9 */
  { .x = 24, .y = 24, .w = 2, .h = 1 }, /* 10 */
  { .x = 38, .y = 24, .w = 11, .h = 1 }, /* 11 */
  { .x = 23, .y = 25, .w = 3, .h = 1 }, /* 12 */
  { .x = 37, .y = 25, .w = 12, .h = 1 }, /* 13 */
  { .x = 20, .y = 26, .w = 6, .h = 1 }, /* 14 */
  { .x = 34, .y = 26, .w = 15, .h = 1 }, /* 15 */
  { .x = 20, .y = 27, .w = 6, .h = 1 }, /* 16 */
  { .x = 34, .y = 27, .w = 86, .h = 1 }, /* 17 */
};

#define HB_COUNT 17

CollisionMask HB_get_collision_mask(Box bb);

#endif // GGJ_2023_HITBOXES_H
