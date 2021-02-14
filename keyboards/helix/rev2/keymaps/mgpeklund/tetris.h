#pragma once

#include <stdio.h>
#include <stdint.h>
#include <timer.h>

#ifdef OLED_DRIVER_ENABLE
# include "oled_driver.h"
# include <avr/pgmspace.h>
#endif

#define screen_byte_index(x,y) ((32 * (y >> 3)) + x)
#define well_byte_index(x,y) ((10 * (y >> 3)) + x)

#define WELL_WIDTH  (10)
#define WELL_HEIGHT (24)
#define LOGO_SIZE   (32)
#define WELL_SIZE   (30)
#define SCREEN_BYTES (512)

enum tetris_input {
  left = 0,
  right,
  down,
  rotate
};

#define TETRIS_FLAG_LEFT    (1 << left)
#define TETRIS_FLAG_RIGHT   (1 << right)
#define TETRIS_FLAG_DOWN    (1 << down)
#define TETRIS_FLAG_ROTATE  (1 << rotate)


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
 *
 */
void draw_current_tetromino(void);

/**
 *
 */
void draw_current_well(void);

/**
 *
 */
void tetris_tick(void);

/**
 *
 */
bool tetris_does_tetromino_fit(int,int,uint8_t);

/**
 * controller code
 */
void tetris_player_input(enum tetris_input);

