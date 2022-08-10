#ifndef SC_JOYSTICK_H
#define SC_JOYSTICK_H
#include "common.h"
#include <stdbool.h>
#include "input_manager.h"
#include "coords.h"
#include "util/log.h"

#define MAX_POSSIBLE_JOYSTICK_AXES 12
#define MAX_POSSIBLE_JOYSTICK_HATS_BUTTONS 8
#define MAX_POSSIBLE_JOYSTICK_BUTTONS 20
#define JOYSTICK_BUTTON_SELECT 6

enum jtype { jaxis, jhat, jbutton };

struct js_button {
    struct sc_point mapping;
    enum sc_mouse_button mouse;
    uint8_t buttons_state;
    bool enable;
};

struct sc_joystick_processor {
    bool set_mode;
    struct js_button button[3][MAX_POSSIBLE_JOYSTICK_BUTTONS];
    struct js_button *button_to_set;
};

struct sc_input_manager;
void sc_joystick_key_simulation(struct sc_input_manager *im, enum jtype type,
                                const Uint8 which, bool state);

bool sc_joystick_processor_init(struct sc_joystick_processor *jsp);
void sc_joystick_processor_destroy(struct sc_joystick_processor *jsp);
#endif