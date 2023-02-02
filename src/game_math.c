#include <genesis.h>
#include "game_math.h"
#include "collision_mask.h"
#include <maths.h> // using min, mas, abs

// reference: https://github.com/Andre-LA/nene/blob/main/nene/math/rect.nelua

Box GMATH_empty_box() {
    const Box empty = {. x = 0, .y = 0, .w = 0, .h = 0 };
    return empty;
}

bool GMATH_is_box_intersecting(Box a, Box b) {
    return !(
        (a.x + a.w) < b.x ||
        (b.x + b.w) < a.x ||
        (a.y + a.h) < b.y ||
        (b.y + b.h) < a.y
    );
}

bool GMATH_box_intersection(Box a, Box b, Box* result) {
    if (!GMATH_is_box_intersecting(a, b)) {
        *result = GMATH_empty_box();
        return FALSE;
    }

    const s16 max_px = max(a.x, b.x);
    const s16 max_py = max(a.y, b.y);
    const s16 min_xw = min(a.x + a.w, b.x + b.w);
    const s16 min_yh = min(a.y + a.h, b.y + b.h);

    *result = (Box){
        .x = max_px,
        .y = max_py,
        .w = abs(min_xw - max_px),
        .h = abs(min_yh - max_py),
    };
    return TRUE;
}

CollisionMask GMATH_get_collision_mask_from_intersection(Box self, Box intersection) {
    // horizontal intersection, the intersected is above or below self's hitbox
    if (intersection.w > intersection.h) {
        if (self.y < intersection.y) { // self is below intersection
            return (CollisionMask){ .mask = COLMASK_UP };
        } else { // self is above intersection
            return (CollisionMask){ .mask = COLMASK_DOWN };
        }
    } else { // vertical intersection, the intersected is on the left or right of self's hitbox
        return (CollisionMask){ .mask = COLMASK_NONE };
    }
}