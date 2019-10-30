#include QMK_KEYBOARD_H

enum dz60_layers {
  _BL, // base layer
  _FL, // function layer
  _ML, // media layer
};

enum custom_keycodes {
  _KC_FN = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_60_iso_5x1u_split_shifts(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    MO(_FL), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   MO(_FL),
    KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FL] = LAYOUT_60_iso_5x1u_split_shifts(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_TRNS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______
  ),

  [_ML] = LAYOUT_60_iso_5x1u_split_shifts(
    _______, KC_BRMD, KC_BRMU, _______, RGB_TOG, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_TRNS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _KC_FN:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
          layer_on(_ML);
        } else {
          layer_on(_FL);
        }
      } else {
        layer_on(_BL);
      }

      return false;
  }

  return true;
};
