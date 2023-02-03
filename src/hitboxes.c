#include <genesis.h>
#include "game_math.h"
#include "collision_mask.h"
#include "tools.h"
#include "hitboxes.h"

CollisionMask HB_get_collision_mask(Box bb) {
    CollisionMask result = { .mask = 0 };

    s16 bb_center_x;
    s16 bb_center_y;
    GMATH_box_get_center(bb, &bb_center_x, &bb_center_y);

    for (int i = 0; i < HB_COUNT; ++i) {
        const Box hitbox = hitboxes[i];

        Box intersection;
        bool is_intersecting = GMATH_box_intersection(bb, hitbox, &intersection);
        kprintf("HB ix %d iy %d iw %u ih %u", intersection.x, intersection.y, intersection.w, intersection.h);

        if (!is_intersecting) {
            continue;
        }

        s16 hb_center_x;
        s16 hb_center_y;
        GMATH_box_get_center(hitbox, &hb_center_x, &hb_center_y);

        CollisionMask colmask = GMATH_get_collision_mask_from_intersection(
            bb_center_x, bb_center_y, intersection
        );

        result.mask = result.mask | colmask.mask;
    }

    return result;
}
