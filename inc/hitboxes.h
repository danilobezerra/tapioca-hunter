// generated with scripts/generate_hitboxes_code.lua script

#ifndef GGJ_2023_HITBOXES_H
#define GGJ_2023_HITBOXES_H

#include <genesis.h>
#include "game_math.h"
#include "collision_data.h"

static const Box hitboxes[] = {
  { .x = 0, .y = 112, .w = 16, .h = 8 }, /* 1 */
  { .x = 0, .y = 120, .w = 16, .h = 8 }, /* 2 */
  { .x = 0, .y = 128, .w = 16, .h = 8 }, /* 3 */
  { .x = 0, .y = 136, .w = 16, .h = 8 }, /* 4 */
  { .x = 0, .y = 144, .w = 16, .h = 8 }, /* 5 */
  { .x = 0, .y = 152, .w = 16, .h = 8 }, /* 6 */
  { .x = 0, .y = 160, .w = 72, .h = 8 }, /* 7 */
  { .x = 296, .y = 160, .w = 144, .h = 8 }, /* 8 */
  { .x = 0, .y = 168, .w = 72, .h = 8 }, /* 9 */
  { .x = 160, .y = 168, .w = 48, .h = 8 }, /* 10 */
  { .x = 272, .y = 168, .w = 168, .h = 8 }, /* 11 */
  { .x = 0, .y = 176, .w = 72, .h = 8 }, /* 12 */
  { .x = 160, .y = 176, .w = 48, .h = 8 }, /* 13 */
  { .x = 272, .y = 176, .w = 168, .h = 8 }, /* 14 */
  { .x = 0, .y = 184, .w = 440, .h = 8 }, /* 15 */
  { .x = 0, .y = 192, .w = 440, .h = 8 }, /* 16 */
  { .x = 0, .y = 200, .w = 440, .h = 8 }, /* 17 */
  { .x = 0, .y = 208, .w = 440, .h = 8 }, /* 18 */
  { .x = 0, .y = 216, .w = 440, .h = 8 }, /* 19 */
  { .x = 0, .y = 224, .w = 440, .h = 8 }, /* 20 */
  { .x = 0, .y = 232, .w = 440, .h = 8 }, /* 21 */
  { .x = 0, .y = 240, .w = 440, .h = 8 }, /* 22 */
  { .x = 0, .y = 248, .w = 440, .h = 8 }, /* 23 */
  { .x = 0, .y = 256, .w = 440, .h = 8 }, /* 24 */
};

#define HB_COUNT 24

CollisionData HB_get_collision_data(Box bb);

#endif // GGJ_2023_HITBOXES_H
