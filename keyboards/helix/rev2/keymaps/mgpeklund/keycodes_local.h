#pragma once 

#include QMK_KEYBOARD_H

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST,
#ifdef TETRIS_ENABLE
  TETRIS,
  T_LEFT,
  T_RIGHT,
  T_DOWN,
  T_ROT,
#endif
#ifdef WPM_ENABLE
  WPM_TOG,
#else
# define WPM_TOG KC_TRANSPARENT
#endif
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


