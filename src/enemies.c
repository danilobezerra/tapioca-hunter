#include <genesis.h>
#include <maths.h>
#include <tools.h>

#include "enemies_init.h"
#include "enemies.h"
#include "player.h"
#include "resources.h"
#include "ggj_debug.h"
#include "camera.h"
#include "game_math.h"

Box GHOST_hitbox(Character* character) {
    return (Box){
        .x = (s16)( fix32ToInt(character->position.x) + 9 ),
        .y = (s16)( fix32ToInt(character->position.y) + 3 ),
        .w = 10,
        .h = 27,
    };
}

void GHOST_update(u16 idx, s32 x, s32 y, Character* player) {
    Character* ghost = &ghosts[idx];
    kprintf("Possibly Ghost update, %d", ghost->tag);
    
    // if (ghost->tag != ENTITY_TAG_GHOST) {
        // not processing a ghost, skip entity
       //  return;
    // }

    kprintf("indeed it's a ghost");

    Sprite* ghost_sprite = ghosts_sprites[idx];

    s32 px = fix32ToInt(ghost->position.x);
    s32 py = fix32ToInt(ghost->position.y);

    s32 dx = x - px;
    s32 dy = y - py;

    if (max(dx, dy) > 120) { // too far
        ghost->speed.x = FIX32(0);
        ghost->speed.y = FIX32(0);
    } else { // inside range    
        // follow player    
        ghost->speed.x = FIX32(clamp(dx, -1, 1));
        ghost->speed.y = FIX32(clamp(dy, -1, 1));

        // run "physics" system
        CHAR_movement(ghost);
        
        // update sprite position
        CAM_setSpritePosition(ghost_sprite, fix32ToInt(ghost->position.x), fix32ToInt(ghost->position.y));

        // verify if ghost intersected player
        Box hb = GHOST_hitbox(ghost);
        Box pl_hb = PLAYER_hitbox(player);
        
        // if so, then player lost the game
        if (GMATH_is_box_intersecting(hb, pl_hb)) {
            PLAYER_die(player);
        }
    }
}

void ENEMIES_update(Character* player) {
    s32 x = fix32ToInt(player->position.x);
    s32 y = fix32ToInt(player->position.y);

    for (u16 i = 0; i < GHOST_COUNT; ++i) {
        GHOST_update(i, x, y, player);
    }
}