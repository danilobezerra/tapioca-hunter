#include "input.h"
#include "tapiocas.h"

void INPUT_joystickHandler(Character* character, bool isPaused) {
    character->isJumping = FALSE;

    if (!isPaused) {
        u16 value = JOY_readJoypad(JOY_1);
        
        character->speed.x = 0;

        if (value & BUTTON_RIGHT) {
            character->speed.x = FIX32(3);
        } else if (value & BUTTON_LEFT) {
            character->speed.x = FIX32(-3);
        }

        character->isAttacking = (value & BUTTON_B) != 0 ? TRUE : FALSE;

        if (value & BUTTON_C) {
            TAPIOCAS_catch();
        }

        if (value & BUTTON_A) {
            character->isJumping = TRUE;
        }
    }
}
