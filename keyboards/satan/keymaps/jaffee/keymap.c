#include "satan.h"


// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |   ~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space            |FN  |FN  |CAPS| ESC |
   * `-----------------------------------------------------------'
   */
[_BL] = KEYMAP_ANSI(
  KC_GRV,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS, \
  KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         KC_RSFT, \
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                                 MO(_FL),MO(_FL), KC_CAPS,KC_ESC),

  /* Keymap _FL: Function Layer
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |  RESET|
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |BL-|BL+|BL   |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |   |       |   |   |   |        |
   * |-----------------------------------------------------------|
   * |        | F1|F2 | F3|F4 | F5| F6| F7| F8|   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_FL] = KEYMAP_ANSI(
  #ifdef RGBLIGHT_ENABLE
  KC_GRV, _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RESET,  \
  _______,BL_DEC,BL_INC, BL_TOGG,_______,_______,_______,_______,_______,_______,_______,KC_UP,_______,_______,  \
  _______,RGB_TOG,RGB_MOD,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD,_______,KC_LEFT,KC_DOWN,        KC_RGHT, \
  _______,_______,_______,_______,_______,_______,_______,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______, \
  _______,_______,_______,                 _______,                       _______,_______,_______, _______),
  #else
  KC_GRV, _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RESET,  \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, BL_DEC, BL_INC,BL_TOGG, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
  _______,_______,_______,                _______,                        _______,_______,_______,_______),
  #endif
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}
