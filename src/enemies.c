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

void GHOST_update_sprite(Character* ghost, Sprite* ghost_sprite) {
    CAM_setSpritePosition(ghost_sprite, fix32ToInt(ghost->position.x), fix32ToInt(ghost->position.y));
}

void GHOST_die(Character* ghost, Sprite* ghost_sprite) {
    ghost->isDead = TRUE;
    SPR_setVisibility(ghost_sprite, HIDDEN);
}

void GHOST_update(u16 idx, s32 x, s32 y, Character* player, Box atk) {
    Character* ghost = &ghosts[idx];
    
    if (ghost->tag != ENTITY_TAG_GHOST || ghost->isDead) {
       // not processing a ghost, skip entity
       return;
    }

    s32 px = fix32ToInt(ghost->position.x);
    s32 py = fix32ToInt(ghost->position.y);
    s32 dx = x - px;
    s32 dy = y - py;
    
    if (max(dx, dy) > 120) { // too far
        ghost->speed.x = FIX32(0);
        ghost->speed.y = FIX32(0);
        GHOST_update_sprite(ghost, ghosts_sprites[idx]);
        goto finish_fn; 
    }
    
    Box hb = GHOST_hitbox(ghost);

    if (player->isAttacking && GMATH_is_box_intersecting(hb, atk)) {
        GHOST_die(ghost, ghosts_sprites[idx]);
        GHOST_update_sprite(ghost, ghosts_sprites[idx]);
        goto finish_fn;
    }

    if (max(dx, dy) > 120) { // too far
        ghost->speed.x = FIX32(0);
        ghost->speed.y = FIX32(0);
    } else { // inside range    
        // follow player
        ghost->speed.x = FIX32(clamp(dx, -0.5, 0.5));
        ghost->speed.y = FIX32(clamp(dy, -0.5, 0.5));

        // run "physics" system
        CHAR_movement(ghost);

        // verify if ghost intersected player
        Box pl_hb = PLAYER_hitbox(player);
        
        // if so, then player lost the game
        if (GMATH_is_box_intersecting(hb, pl_hb)) {
            PLAYER_die(player);
        }
    }

    finish_fn:
    GHOST_update_sprite(ghost, ghosts_sprites[idx]);
}

void ENEMIES_update(Character* player) {
    s32 x = fix32ToInt(player->position.x);
    s32 y = fix32ToInt(player->position.y);

    Box atk = PLAYER_atk_hitbox(player);

    for (u16 i = 0; i < GHOST_COUNT; ++i) {
        GHOST_update(i, x, y, player, atk);
    }
}