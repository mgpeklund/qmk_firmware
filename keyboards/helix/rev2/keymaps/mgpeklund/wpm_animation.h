#pragma once
#include QMK_KEYBOARD_H
# ifndef OLED_DRIVER_ENABLE
#   error
# endif

//#include "oled_driver.h"
//#include <avr/pgmspace.h>

/* DEFINES */
#define IDLE_FRAMES     (2)
#define WALK_FRAMES     (4)
#define RUN_FRAMES      (3)
#define ANIM_SIZE       (168)
#define ANIM_FRAME_DUR  (100)

#define IDLE_SPEED      (40)
#define RUN_SPEED       (80)

enum anim_state {
  _IDLE = 5,
  _WALK,
  _RUN,
};

uint16_t anim_timer;
uint16_t anim_sleep         = 0;

enum anim_state a_state = 1;
uint8_t current_idle_frame  = 0;
uint8_t current_walk_frame  = 0;
uint8_t current_run_frame   = 0;

bool oled_active;

static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {
  { // 'shy_guy_idle_1', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xb0,
    0x30, 0x30, 0x30, 0x70, 0x60, 0x60, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0x0e, 0xe3, 0xf1, 0xf1, 0xe0, 0x00, 0xe0, 0xf0, 0xf0, 0xf1,
    0xe1, 0x03, 0x06, 0x1c, 0xf0, 0x60, 0x44, 0xd8, 0xf1, 0xe1, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x83, 0x07, 0x07, 0x03, 0xe0, 0x03, 0x07, 0x07, 0x07,
    0x03, 0x80, 0x40, 0x30, 0x1f, 0x02, 0x02, 0x0a, 0x17, 0x7f, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1e, 0x3f, 0xb3, 0xf1, 0xff, 0xb1, 0xa3, 0x22, 0x72, 0x72, 0x52, 0x52, 0x53,
    0x61, 0x20, 0x24, 0x2c, 0xac, 0xa8, 0xb8, 0xb8, 0xb0, 0x70, 0xf9, 0x9f, 0x0f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x08, 0x08, 0x08, 0x09, 0x09, 0x0b, 0x0e, 0x0c, 0x0c, 0x0c,
    0x0e, 0x06, 0x0f, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x0d, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00,
  },
  { // 'shy_guy_idle_2', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x40, 0x60, 0x70, 0x70, 0x78, 0xd8,
    0x98, 0x98, 0x38, 0x30, 0x30, 0x70, 0x60, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0x07, 0xf1, 0xf8, 0xf8, 0xf0, 0x00, 0xf0, 0xf8, 0xf8, 0xf8,
    0xf0, 0x01, 0x03, 0x0e, 0xf8, 0x30, 0x22, 0x6c, 0xf8, 0xf1, 0xe7, 0x7e, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x8f, 0xff, 0xf0, 0xc1, 0x83, 0x83, 0x01, 0x70, 0x01, 0x03, 0x03, 0x83,
    0x81, 0x40, 0x20, 0x18, 0x0f, 0x01, 0x01, 0x05, 0x0b, 0x3f, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0f, 0x1f, 0xd9, 0xf8, 0xff, 0xd8, 0xd1, 0x91, 0x39, 0x39, 0x29, 0x29, 0x29,
    0x30, 0x10, 0x12, 0x96, 0xd6, 0x54, 0x5c, 0x5c, 0x78, 0xf8, 0xfc, 0xcf, 0x87, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x08, 0x08, 0x08, 0x0c, 0x0d, 0x07, 0x07, 0x06, 0x06, 0x06,
    0x06, 0x03, 0x07, 0x06, 0x0c, 0x0c, 0x08, 0x08, 0x08, 0x0c, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00,
  }
};

// 'shy_guy_walk_1', 32x34px
static const char PROGMEM walk[WALK_FRAMES][ANIM_SIZE] = {
  { // 'shy_guy_walk_1', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x40, 0x60, 0x70, 0x70, 0x78, 0xd8, 0x98,
    0x98, 0x18, 0x38, 0x30, 0x30, 0x70, 0x60, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf0, 0xfc, 0x07, 0xf1, 0xf8, 0xf8, 0xf0, 0x00, 0xf0, 0xf8, 0xf8, 0xf8, 0xf0,
    0x01, 0x03, 0x0e, 0xf8, 0x30, 0x22, 0x6c, 0xf8, 0xf8, 0x31, 0x33, 0x3e, 0x1c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x8f, 0xff, 0x70, 0xc1, 0x83, 0x83, 0x01, 0x70, 0x01, 0x03, 0x03, 0x83, 0x81,
    0x40, 0x20, 0x18, 0x0f, 0x01, 0x01, 0x05, 0x0b, 0x3f, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x0f, 0x18, 0x1c, 0xdf, 0xf8, 0x31, 0x11, 0x31, 0x39, 0x29, 0x29, 0x29, 0x30,
    0x30, 0x12, 0x16, 0x16, 0x1c, 0x1c, 0x9c, 0xf8, 0xe8, 0x0c, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0a, 0x0a,
    0x0a, 0x0a, 0x0a, 0x0f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  },
  { // 'shy_guy_walk_2', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x30, 0x38, 0x38, 0x3c, 0x6c,
    0x4c, 0xdc, 0x98, 0x18, 0x38, 0x30, 0x70, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xf8, 0xfe, 0x03, 0xf8, 0xfc, 0xfc, 0xf8, 0x00, 0xf8, 0xfc, 0xfc, 0xfc,
    0xf8, 0x00, 0x01, 0x07, 0xfc, 0x98, 0x91, 0xbe, 0xfc, 0xf1, 0x67, 0x7e, 0x38, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xc7, 0x7f, 0x38, 0xe0, 0x41, 0xc1, 0x80, 0xb8, 0x80, 0x81, 0x81, 0xc1,
    0x40, 0x20, 0x10, 0x0c, 0x07, 0x00, 0x00, 0x02, 0x05, 0x1f, 0x3c, 0xf0, 0xc0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x07, 0xc4, 0x66, 0x2f, 0x3c, 0x78, 0x48, 0x98, 0x9c, 0x14, 0x14, 0x1c,
    0x18, 0x18, 0x19, 0x8b, 0x8b, 0xce, 0xce, 0x7e, 0x3c, 0xe4, 0xe6, 0x07, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x03, 0x03,
    0x03, 0x03, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  },
  { // 'shy_guy_walk_3', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x30, 0x38, 0x38, 0x3c, 0x6c, 0x4c,
    0xcc, 0x8c, 0x0c, 0x0c, 0x1c, 0x98, 0x18, 0x18, 0x38, 0x30, 0x70, 0x60, 0xc0, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf8, 0xfe, 0x03, 0xf8, 0xfc, 0xfc, 0xf8, 0x00, 0xf8, 0xfc, 0xfc, 0xfc, 0xf8,
    0x00, 0x01, 0x07, 0xfc, 0x90, 0x90, 0xb3, 0xfe, 0xfc, 0x1c, 0x06, 0x07, 0x03, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xe7, 0x7f, 0x38, 0xe0, 0xc1, 0xc1, 0x80, 0xb8, 0x80, 0x81, 0x81, 0xc1, 0x40,
    0x20, 0x10, 0x0c, 0x07, 0x00, 0x00, 0x02, 0x07, 0x0f, 0x3e, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0x1f, 0x39, 0x71, 0x61, 0xc1, 0xc2, 0xcc, 0x7c, 0x34, 0x6c, 0x6c, 0xd4, 0xd4, 0x9c,
    0x98, 0x99, 0x9b, 0xcb, 0xce, 0x6e, 0xfe, 0xfc, 0x8c, 0x86, 0xc3, 0xe7, 0x7f, 0x1c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  },
  { // 'shy_guy_walk_4', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x30, 0x38, 0x38, 0x3c, 0x6c, 0x4c,
    0xcc, 0x9c, 0x18, 0x18, 0x38, 0x30, 0x30, 0x30, 0x38, 0x18, 0x18, 0x38, 0xf0, 0xe0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf8, 0xfe, 0x03, 0xf8, 0xfc, 0xfc, 0xf8, 0x00, 0xf8, 0xfc, 0xfc, 0xfc, 0xf8,
    0x00, 0x01, 0x07, 0xfc, 0x98, 0x90, 0xa7, 0xfe, 0xfc, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xc7, 0x7f, 0x38, 0xe0, 0x41, 0xc1, 0x80, 0xb8, 0x80, 0x81, 0x81, 0xc1, 0x40,
    0x20, 0x10, 0x0c, 0x07, 0x00, 0x00, 0x02, 0x07, 0x0f, 0x3c, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x06, 0xc4, 0x64, 0x3f, 0x3c, 0x30, 0x48, 0xdc, 0x9c, 0x94, 0x94, 0x14, 0x18,
    0x18, 0x99, 0x9b, 0x8b, 0x8e, 0xce, 0x5e, 0x7c, 0x74, 0xe6, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x06, 0x06, 0x06, 0x06, 0x07, 0x03, 0x01, 0x01, 0x01,
    0x01, 0x03, 0x07, 0x07, 0x06, 0x06, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  }
};

static const char PROGMEM run[RUN_FRAMES][ANIM_SIZE] = {
  { // 'shy_guy_run_1', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x20, 0x30, 0x10, 0x18, 0x1c, 0x1c, 0x1e, 0x36, 0x26,
    0x66, 0xc6, 0x8e, 0x0c, 0x0c, 0x9c, 0x18, 0x38, 0x30, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xfc, 0xff, 0x01, 0x7c, 0xfe, 0xfe, 0x7c, 0x00, 0x7c, 0xfe, 0xfe, 0xfe, 0x7c,
    0x00, 0x00, 0x03, 0xfe, 0xcc, 0xc8, 0xdb, 0xfe, 0xfc, 0xcc, 0xce, 0xc7, 0x83, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0x3f, 0x79, 0xe7, 0xcc, 0x50, 0x20, 0x20, 0x40, 0x5c, 0x40, 0x40, 0x40, 0x20, 0x20,
    0x10, 0x08, 0x06, 0x03, 0x80, 0x80, 0xc0, 0xe0, 0x60, 0x30, 0x38, 0x1c, 0x0f, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x78, 0xfc, 0x9e, 0x37, 0x26, 0x6c, 0x4c, 0xc0, 0x8c, 0x8c, 0x8c, 0x80, 0x8c, 0x8c,
    0x8c, 0x8e, 0xc6, 0xc7, 0x47, 0x67, 0x36, 0x3c, 0x1c, 0x0c, 0x0e, 0x86, 0xc6, 0xfe, 0x3c, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x06, 0x06, 0x04, 0x0c, 0x0c, 0x08, 0x09, 0x09, 0x09, 0x09,
    0x09, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00
  },
  { // 'shy_guy_run_2', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x30, 0x10, 0x18, 0x0c, 0x0c, 0x0e, 0x0e, 0x0f, 0x1b, 0x13,
    0x37, 0x66, 0xc6, 0x0e, 0x0c, 0x8c, 0x1c, 0x18, 0x38, 0x30, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00,
    0x00, 0x80, 0xc0, 0xfe, 0xff, 0x00, 0x3e, 0x7f, 0x7f, 0x3e, 0x00, 0x3e, 0x7f, 0x7f, 0x7f, 0x3e,
    0x00, 0x00, 0x01, 0xff, 0x66, 0x64, 0x6f, 0x7e, 0x7c, 0x66, 0x66, 0x63, 0xc1, 0x80, 0x00, 0x00,
    0x00, 0x07, 0x1f, 0x3c, 0x73, 0xe6, 0x28, 0x10, 0x10, 0x20, 0x2e, 0x20, 0x20, 0x20, 0x10, 0x10,
    0x08, 0x04, 0x03, 0x81, 0xc0, 0xc0, 0x60, 0x70, 0x30, 0x18, 0x9c, 0x8e, 0x87, 0x83, 0x00, 0x00,
    0x00, 0x3c, 0x7e, 0xc6, 0x8f, 0x9f, 0x3b, 0xb6, 0xe6, 0xe0, 0x46, 0xc6, 0xc6, 0xc0, 0xc6, 0xc6,
    0xc6, 0x47, 0x63, 0xe3, 0xe3, 0xf3, 0xfb, 0xff, 0xfe, 0x8f, 0x83, 0xc1, 0xe1, 0x7b, 0x1f, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x07, 0x0f, 0x0d, 0x08, 0x08, 0x0d,
    0x0f, 0x07, 0x00, 0x07, 0x0f, 0x0c, 0x0c, 0x0f, 0x07, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00
  },
  { // 'shy_guy_run_3', 32x36px
    0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x30, 0x10, 0x18, 0x08, 0x0c, 0x0c, 0x0e, 0x0f, 0x1b, 0x13,
    0x37, 0x66, 0xc6, 0x0e, 0x0c, 0x8c, 0x1c, 0x18, 0x38, 0x30, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00,
    0x00, 0x80, 0xc0, 0xfe, 0xff, 0x00, 0x3e, 0x7f, 0x7f, 0x3e, 0x00, 0x3e, 0x7f, 0x7f, 0x7f, 0x3e,
    0x00, 0x00, 0x01, 0xff, 0x66, 0x64, 0x6f, 0x7e, 0x7c, 0x66, 0x66, 0x63, 0xc1, 0x80, 0x00, 0x00,
    0x00, 0x07, 0x1f, 0x3c, 0x73, 0xe6, 0x28, 0x10, 0x10, 0x20, 0x2e, 0x20, 0x20, 0x20, 0x10, 0x10,
    0x08, 0x04, 0x03, 0x81, 0xc0, 0xc0, 0x60, 0x70, 0x30, 0x18, 0x1c, 0x0e, 0x07, 0x03, 0x00, 0x00,
    0x00, 0x3e, 0xff, 0xc3, 0x8f, 0x9f, 0xfb, 0xf6, 0xe6, 0xe0, 0xc6, 0xc6, 0xc6, 0xc0, 0xc6, 0xc6,
    0xc6, 0xc7, 0xe7, 0x63, 0x63, 0xf3, 0xfb, 0xbf, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x07, 0x0f, 0x0c, 0x0c, 0x0f, 0x07, 0x07, 0x0f, 0x0d,
    0x08, 0x08, 0x08, 0x0c, 0x0c, 0x06, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  }
};

/* END SHY GUY ANIMATION FRAMES */

void animation_phase(uint8_t wpm) {
  // idle animation 
  if(wpm < IDLE_SPEED) {
    if (a_state != _IDLE) {
      current_idle_frame = 1;
      a_state = _IDLE;
    }
    oled_write_raw_P(idle[current_idle_frame++], ANIM_SIZE);
    current_idle_frame = current_idle_frame % IDLE_FRAMES;
  }
  // walk animation
  else if (wpm < RUN_SPEED) {
    if (a_state != _WALK) {
      current_walk_frame = 0;
      a_state = _WALK;
    }
    oled_write_raw_P(walk[current_walk_frame++], ANIM_SIZE);
    current_walk_frame = current_walk_frame % WALK_FRAMES;
  } 
  // run animation
  else {
    if (a_state != _RUN) {
      current_run_frame = 0;
      a_state = _RUN;
    }
    oled_write_raw_P(run[current_run_frame++], ANIM_SIZE);
    current_run_frame = current_run_frame % RUN_FRAMES;
  }
};

uint16_t frame_duration(void) {
  switch (a_state){
    case _IDLE: return 500;
    default: return 100;
  };
  return 100;
}

uint8_t m_wpn = 0;

void render_shy_guy(void) {
  uint8_t c_wpm = get_current_wpm();
  m_wpn = (c_wpm > m_wpn) ? c_wpm : m_wpn;

  if(c_wpm > 000 ) {
    oled_active = oled_on();
    if(timer_elapsed(anim_timer) > frame_duration()) {
      anim_timer = timer_read();
      animation_phase(c_wpm);
    }
    anim_sleep = timer_read();
  } else {
    if(timer_elapsed(anim_sleep) > OLED_TIMEOUT) {
      oled_active = !oled_off();

    } else {
      if(oled_active && timer_elapsed(anim_timer) > frame_duration()) {
        anim_timer = timer_read();
        animation_phase(c_wpm);
      }
    }
  }

  char buf[5];
  sprintf(buf, "  %03d", c_wpm);
  oled_set_cursor(0,6);
  oled_write_P(PSTR("WPM: "),false);
  oled_write(buf, false);
  oled_write_P(PSTR("MWPN:"), false);
  sprintf(buf, "  %03d", m_wpn);
  oled_write(buf, false); 

}


