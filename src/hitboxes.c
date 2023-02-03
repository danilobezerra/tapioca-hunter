#include <genesis.h>
#include <tools.h>

#include "game_math.h"
#include "collision_data.h"
#include "hitboxes.h"
#include "ggj_debug.h"

CollisionData HB_get_collision_data(Box bb) {
    CollisionData result = { .mask = 0 };

    s16 bb_center_x;
    s16 bb_center_y;
    GMATH_box_get_center(bb, &bb_center_x, &bb_center_y);

    for (int i = 0; i < HB_COUNT; ++i) {
        const Box hitbox = hitboxes[i];

        Box intersection;
        bool is_intersecting = GMATH_box_intersection(bb, hitbox, &intersection);
        GGJ_PRINTF("HB ix %d iy %d iw %u ih %u", intersection.x, intersection.y, intersection.w, intersection.h);

        if (!is_intersecting) {
            continue;
        }

        s16 hb_center_x;
        s16 hb_center_y;
        GMATH_box_get_center(hitbox, &hb_center_x, &hb_center_y);

        CollisionData collision = GMATH_get_collision_data_from_intersection(
            bb_center_x, bb_center_y, intersection
        );

        result.mask = result.mask | collision.mask;
    }

    return result;
}
