#include QMK_KEYBOARD_H

enum dz60_layers {
  _BL, // base layer
  _FL, // function layer
  _ML, // media layer
};

enum custom_keycodes {
  M_FN = SAFE_RANGE,
  M_BSPC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_60_iso_5x1u_split_shifts(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  M_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    M_FN,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   M_FN,
    KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FL] = LAYOUT_60_iso_5x1u_split_shifts(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2   , KC_3,    _______,
    _______, _______, _______,                            _______,                   _______, KC_0,    _______, _______, _______
  ),

  [_ML] = LAYOUT_60_iso_5x1u_split_shifts(
    _______, KC_BRMD, KC_BRMU, _______, _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, RESET,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______
  ),
};

static bool lctl_held = false;
static bool lshift_held = false;
static bool fn_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCTL:
      lctl_held = record->event.pressed;
      return true;

    case KC_LSFT:
      lshift_held = record->event.pressed;
      if (fn_held) {
        layer_move(lshift_held ? _ML : _FL);

        return false;
      }

      return true;

    case M_FN:
      fn_held = record->event.pressed;
      if (record->event.pressed) {
        unregister_code(KC_LSFT);
        layer_move(lshift_held ? _ML : _FL);
      } else {
        layer_clear();
        if (lshift_held) {
          register_code(KC_LSFT);
        }
      }

      return false;

    case M_BSPC:
      if (record->event.pressed) {
        if (lshift_held) {
          unregister_code(KC_LSFT);
          register_code(KC_DEL);
        } else if (lctl_held) {
          unregister_code(KC_LCTL);
          register_code(KC_DEL);
        } else {
          register_code(KC_BSPC);
        }

        return false;
      } else {
        unregister_code(KC_DEL);
        unregister_code(KC_BSPC);
        if (lshift_held) {
          register_code(KC_LSFT);
        } else if (lctl_held) {
          register_code(KC_LCTL);
        }
      }

      return true;
  }

  return true;
}
