#include <genesis.h>
#include "game_math.h"
#include "collision_mask.h"
#include "hitboxes.h"

CollisionMask HB_get_collision_mask(Box bb) {
    CollisionMask result = { .mask = 0 };
    Box intersection;
    bool is_intersecting;

    for (int i = 0; i < HB_COUNT; ++i) {
        is_intersecting = GMATH_box_intersection(bb, hitboxes[i], &intersection);
        if (!is_intersecting) {
            continue;
        }

        
    }
}
