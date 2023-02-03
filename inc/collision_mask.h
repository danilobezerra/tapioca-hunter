#ifndef GGJ_2023_COLLISION_MASK_H
#define GGJ_2023_COLLISION_MASK_H

#include <genesis.h>

typedef struct {
    u8 mask;
} CollisionMask;

// directions of collision mask:
// 1 = 0001 -> right
// 2 = 0010 -> up
// 4 = 0100 -> left
// 8 = 1000 -> down
#define COLMASK_NONE (0)
#define COLMASK_RIGHT (1)
#define COLMASK_UP (2)
#define COLMASK_LEFT (4)
#define COLMASK_DOWN (8)
#define COLMASK_INIT(X) ((CollisionMask){ .mask = (X) })

#define COLMASK_CONTAINS(X, Y) ( X.mask & Y )

#endif //GGJ_2023_COLLISION_MASK_H
