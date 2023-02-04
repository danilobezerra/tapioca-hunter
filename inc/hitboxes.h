// generated with scripts/generate_hitboxes_code.lua script

#ifndef GGJ_2023_HITBOXES_H
#define GGJ_2023_HITBOXES_H

#include <genesis.h>
#include "game_math.h"
#include "collision_data.h"

static const Box hitboxes[] = {
  { .x = 0, .y = 32, .w = 184, .h = 8 }, /* 1 */
  { .x = 304, .y = 136, .w = 16, .h = 8 }, /* 2 */
  { .x = 304, .y = 144, .w = 32, .h = 8 }, /* 3 */
  { .x = 304, .y = 152, .w = 32, .h = 8 }, /* 4 */
  { .x = 304, .y = 160, .w = 32, .h = 8 }, /* 5 */
  { .x = 304, .y = 168, .w = 32, .h = 8 }, /* 6 */
  { .x = 304, .y = 176, .w = 32, .h = 8 }, /* 7 */
  { .x = 192, .y = 184, .w = 16, .h = 8 }, /* 8 */
  { .x = 304, .y = 184, .w = 32, .h = 8 }, /* 9 */
  { .x = 192, .y = 192, .w = 16, .h = 8 }, /* 10 */
  { .x = 304, .y = 192, .w = 88, .h = 8 }, /* 11 */
  { .x = 184, .y = 200, .w = 24, .h = 8 }, /* 12 */
  { .x = 296, .y = 200, .w = 96, .h = 8 }, /* 13 */
  { .x = 160, .y = 208, .w = 48, .h = 8 }, /* 14 */
  { .x = 272, .y = 208, .w = 120, .h = 8 }, /* 15 */
  { .x = 160, .y = 216, .w = 48, .h = 8 }, /* 16 */
  { .x = 272, .y = 216, .w = 1008, .h = 8 }, /* 17 */
};

#define HB_COUNT 17

CollisionData HB_get_collision_data(Box bb);

#endif // GGJ_2023_HITBOXES_H
