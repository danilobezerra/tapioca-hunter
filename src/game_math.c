#include <genesis.h>
#include "game_math.h"
#include "collision_mask.h"
#include "tools.h"
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
    
    kprintf("ax %d ay %d aw %u ah %u bx %d by %d bw %u bh %u ix %d iy %d iw %u ih %u", a.x, a.y, a.w, a.h, b.x, b.y, b.w, b.h, result->x, result->y, result->w, result->h);
    return TRUE;
}

void GMATH_box_get_center(Box v, s16* out_x, s16* out_y) {
    *out_x = v.x + v.w / 2;
    *out_y = v.y + v.h / 2;
}

CollisionMask GMATH_get_collision_mask_from_intersection(s16 self_center_x, s16 self_center_y, Box intersection) {
    s16 intersection_center_x;
    s16 intersection_center_y;
    GMATH_box_get_center(intersection, &intersection_center_x, &intersection_center_y);

    u16 iw = intersection.w;
    u16 ih = intersection.h;
    
    // horizontal intersection, the intersected is above or below self's hitbox
    kprintf("ix %d iy %d iw %u ih %u", intersection.x, intersection.y, iw, ih);
    if (iw > ih) {
        kprintf("intersection w > h");
    } else {
        kprintf("intersection w <= h");
    }

    if (iw > ih) {  
        if (ih < 2) {
            kprintf("COLMASK_NONE");
            return COLMASK_INIT(COLMASK_NONE);
        } else if (self_center_y < intersection_center_y) { // self is above intersection
            kprintf("mask down: %u", iw);
            return COLMASK_INIT(COLMASK_DOWN);
        } else { // self is below intersection
            kprintf("mask up: %u", iw);
            return COLMASK_INIT(COLMASK_UP);
        }
    } else { // vertical intersection, the intersected is on the left or right of self's hitbox
        if (iw < 2) {
            kprintf("COLMASK_NONE");
            return COLMASK_INIT(COLMASK_NONE);
        } else if (self_center_x < intersection_center_x) { // self is on the left of intersection
            kprintf("mask right: %u", ih);
            return COLMASK_INIT(COLMASK_RIGHT);
        } else { // self is on the right of intersection
            kprintf("mask left: %u", ih);
            return COLMASK_INIT(COLMASK_LEFT);
        }
    }
}
