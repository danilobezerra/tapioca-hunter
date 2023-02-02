#ifndef GGJ_2023_GAME_MATH_H
#define GGJ_2023_GAME_MATH_H

#include <genesis.h>
#include "collision_mask.h"

Box GMATH_empty_box();
bool GMATH_is_box_intersecting(Box a, Box b);
bool GMATH_box_intersection(Box a, Box b, Box* result);
CollisionMask GMATH_get_collision_mask_from_intersection(Box self, Box intersection);

#endif //GGJ_2023_GAME_MATH_H