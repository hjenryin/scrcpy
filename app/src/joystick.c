#include "joystick.h"
#include "SDL2/SDL.h"
#include "input_events.h"
#include "screen.h"

void sc_joystick_key_simulation(struct sc_input_manager* im, enum jtype type,
                                const Uint8 which, bool state) {
    if (type == jbutton && which == JOYSTICK_BUTTON_SELECT) {
        if (state) {
            im->jsp->set_mode = !im->jsp->set_mode;
            im->jsp->button_to_set = NULL;
        }
        return;
    }
    struct js_button* button = &im->jsp->button[type][which];
    LOGI("Joystick: Testing whether set_mode.");
    if (im->jsp->set_mode) {
        im->jsp->button_to_set = button;
        LOGI("Joystick: set_mode, button ready.");
    } else {
        LOGI("Joystick: not set_mode.");
        if (button->enable) {
            LOGI("Joystick: Button enabled.");
            struct sc_mouse_click_event evt = {
                .position =
                    {
                        .screen_size = im->screen->frame_size,
                        .point = button->mapping,
                    },
                .action = state,
                .button = button->mouse,
                .buttons_state = button->buttons_state,
            };
            assert(im->mp->ops->process_mouse_click);
            im->mp->ops->process_mouse_click(im->mp, &evt);
        } else {
            LOGI("Joystick: button disabled.");
        }
    }

    return;
}
bool sc_joystick_processor_init(struct sc_joystick_processor* jsp) {
    // jsp = malloc(sizeof(struct sc_joystick_processor));
    jsp->set_mode = false;
    if (jsp) {
        return true;
    } else {
        return false;
    }
}
void sc_joystick_processor_destroy(struct sc_joystick_processor* jsp) {
    // free(jsp);
    return;
}