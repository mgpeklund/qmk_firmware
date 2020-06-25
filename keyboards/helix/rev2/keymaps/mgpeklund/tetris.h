#pragma once

#include <stdint.h>
#include <timer.h>

#ifdef OLED_DRIVER_ENABLE
# include "oled_driver.h"
# include <avr/pgmspace.h>
#endif

/*
#define WELL_X (10)
#define WELL_Y (24)
uint8_t well[WELL_X][WELL_Y];*/ /* the tetris well where all peices fall */

#define BOARD_SIZE (512)
static const char PROGMEM tetris_screen[BOARD_SIZE] = {
  // 'tetris_logo', 32x8px (this is static and will allways be here. no need to add it later)
  0x00, 0x82, 0xbe, 0xbe, 0x82, 0x80, 0xbe, 0xbe, 0xaa, 0xa2, 0x80, 0x82, 0xbe, 0xbe, 0x82, 0x80, 
  0xbe, 0xbe, 0x8a, 0xb4, 0x80, 0xa2, 0xbe, 0xbe, 0xa2, 0x80, 0xa4, 0xae, 0xba, 0x92, 0x80, 0x00
};

/**
 * Rotate function
 * takes a x and a y for the piece, and a rotation, and returns the index for the supplied rotation.
 */
uint8_t tetris_rotate_tetromino(int px, int py, int r);

/**
 * Sets keyboard in tetris mode, stops rendering layer info to display
 */
void tetris_init(void);

/**
 * Reset tetris board.
 */
void tetris_reset(void);

/**
 * renders the board as it currently is 
 */
void tetris_render(void);

/**
 * updates the state of the well.
 */
void tetris_update_well(void);


