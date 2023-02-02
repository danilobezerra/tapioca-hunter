#ifndef GGJ_2023_GAME_MATH_H
#define GGJ_2023_GAME_MATH_H

#include <genesis.h>
#include "collision_mask.h"

Box GMATH_empty_box();
bool GMATH_is_box_intersecting(Box a, Box b);
bool GMATH_box_intersection(Box a, Box b, Box* result);
void GMATH_box_get_center(Box bb, s16* out_x, s16* out_y);
CollisionMask GMATH_get_collision_mask_from_intersection(s16 self_center_x, s16 self_center_y, Box intersection);

#endif //GGJ_2023_GAME_MATH_H