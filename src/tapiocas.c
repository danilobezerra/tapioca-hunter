#include <genesis.h>
#include <tools.h>
#include "tapiocas.h"
#include "player.h"
#include "scene_manager.h"
#include "resources.h"
#include "game_math.h"
#include "camera.h"

u8 tapiocaCount = TAPIOCA_TOTAL;

void TAPIOCAS_init() {
    tapiocas[0] = (Tapioca){ .pos = { .x = 200, .y = 160 }, .collected = FALSE };
    tapiocas[1] = (Tapioca){ .pos = { .x = 288, .y = 160 }, .collected = FALSE };
    tapiocas[2] = (Tapioca){ .pos = { .x = 320, .y = 152 }, .collected = FALSE };
    tapiocas[3] = (Tapioca){ .pos = { .x = 360, .y = 152 }, .collected = FALSE };
    tapiocas[4] = (Tapioca){ .pos = { .x = 392, .y = 152 }, .collected = FALSE };

    for (int i = 0; i < TAPIOCA_TOTAL; ++i) {
        tapiocas[i].pos.x -= 8;
        tapiocas[i].pos.y -= 8;
        
        tapiocas_sprites[i] = SPR_addSprite(
            &tapioca_sprite,
            tapiocas[i].pos.x, tapiocas[i].pos.y,
            TILE_ATTR(PAL3, 0, FALSE, FALSE)      
        );
    }
}

Box TAPIOCAS_hitbox(Tapioca* tapioca) {
    return (Box){
        .x = tapioca->pos.x,
        .y = tapioca->pos.y,
        .w = 16,
        .h = 16
    };
}

void TAPIOCAS_collect(Tapioca* tapioca, Sprite* tapioca_sprite) {
    tapioca->collected = TRUE;
    SPR_setVisibility(tapioca_sprite, HIDDEN);
    TAPIOCAS_catch();
}

void TAPIOCAS_update(Character* player) {
    for (int i = 0; i < TAPIOCA_TOTAL; ++i) {
        Tapioca* tapioca = &tapiocas[i];
        Sprite* tap_sprite = tapiocas_sprites[i];

        CAM_setSpritePosition(tap_sprite, tapioca->pos.x, tapioca->pos.y);

        if (tapioca->collected) {
            continue;
        }

        Box tap_hb = TAPIOCAS_hitbox(tapioca);
        Box pl_hb = PLAYER_hitbox(player);

        if (GMATH_is_box_intersecting(tap_hb, pl_hb)) {
            TAPIOCAS_collect(tapioca, tap_sprite);
        }
    }
}

void TAPIOCAS_catch() {
    tapiocaCount--;
}

u8 TAPIOCAS_getCount() {
    return tapiocaCount;
}

void TAPIOCAS_clear() {
    for (int i = 0; i < TAPIOCAS_TOTAL; ++i) {
        SPR_releaseSprite(tapiocas_sprites[i]);
    }
}

