#include "tetris.h"

#ifdef CONSOLE_ENABLE
# include <print.h>
#endif

#include <string.h>


void draw_square(uint16_t, uint16_t, uint16_t);


int x_pos; 
int y_pos;

uint8_t flags;

uint8_t tetro_mem;
uint8_t next_tetromino;
uint8_t current_rotation = 0x00;

uint16_t drop_timer;
uint16_t drop_time;

uint8_t well[WELL_WIDTH * WELL_HEIGHT]; /* the tetris well where all peices fall */
char screen[SCREEN_BYTES] = {0x00, 0x82, 0xbe, 0xbe, 0x82, 0x80, 0xbe, 0xbe, 0xaa, 0xa2, 0x80, 0x82, 0xbe, 0xbe, 0x82, 0x80, 
  0xbe, 0xbe, 0x8a, 0xb4, 0x80, 0xa2, 0xbe, 0xbe, 0xa2, 0x80, 0xa4, 0xae, 0xba, 0x92, 0x80, 0x00
};
char tetris_logo[LOGO_SIZE] = {
  // 'tetris_logo', 32x8px (this is static and will allways be here. no need to add it later)
  0x00, 0x82, 0xbe, 0xbe, 0x82, 0x80, 0xbe, 0xbe, 0xaa, 0xa2, 0x80, 0x82, 0xbe, 0xbe, 0x82, 0x80, 
  0xbe, 0xbe, 0x8a, 0xb4, 0x80, 0xa2, 0xbe, 0xbe, 0xa2, 0x80, 0xa4, 0xae, 0xba, 0x92, 0x80, 0x00
};

char draw_bits[8] = {
  0x01,
  0x02,
  0x04,
  0x08,
  0x10,
  0x20,
  0x40,
  0x80
};

uint8_t rows_to_be_removed[3] = {0x00,0x00,0x00};

uint16_t tetrominos[7] = {
  0b0010001000100010, // __1_
                      // __1_
                      // __1_
                      // __1_ I

  0b0100011000100000, // _1__
                      // _11_
                      // __1_
                      // ____ S

  0b0010011001000000, // __1_
                      // _11_
                      // _1__
                      // ____ Z

  0b0010011000100000, // __1_
                      // _11_
                      // __1_
                      // ____ T

  0b0000011001100000, // ____
                      // _11_
                      // _11_
                      // ____ O

  0b0000010001000110, // ____
                      // _1__
                      // _1__
                      // _11_ L

  0b0000001000100110  // ____
                      // __1_
                      // __1_
                      // _11_ J
}; 

#define translate_to_screen_x_cord(x) (3 * (x) + 1)
#define translate_to_screen_y_cord(y) (3 * (y) + 55)
#define get_byte_bit(byte, k) ((byte & (0x80 >> k)) >> (7 - k))
#define current_tetromino (uint8_t)(tetro_mem & 0b00000111)
#define next_tetromino    (tetro_mem & 0b00111000)
#define get_tetromino_bit(k) ((tetrominos[current_tetromino] & (0x8000 >> k)) >> (15 - k) )


uint8_t tetris_rotate_tetromino(int px, int py, int r) {
  switch(r % 4) {
    case 0: return (py * 4) + px;			//   0 degrees
    case 1: return 12 + py - (px * 4);	//  90 degrees
    case 2: return 15 - (py * 4) - px;	// 180 degrees
    case 3: return 3 - py + (px * 4);	// 270 degrees
  }
  return 0;
}

void tetris_init() {
  x_pos = 3;
  y_pos = 0;

  tetro_mem = (uint8_t) (timer_read() % 7 ) << 3 | ((timer_read() % 7) & 0x07);

  memset(well, 0x00, sizeof(uint8_t) * (WELL_WIDTH * WELL_HEIGHT));
  
  drop_timer = timer_read();
  drop_time = 1000;
};

void tetris_render() {
  // clear screen after logo
  memset (screen + LOGO_SIZE , 0x00, sizeof(char) * (SCREEN_BYTES - LOGO_SIZE) );

  // draw well
  draw_current_well();

  // Draw current tetromino
  draw_current_tetromino();

  // render to screen
  oled_write_raw(screen,SCREEN_BYTES);
};

void draw_current_tetromino() {
  uint8_t k = 1,px,py;

  for (px = 0; px < 4; px++) {
    for (py = 0; py < 4; py++) {
      k = tetris_rotate_tetromino(px,py,current_rotation);
      int draw = get_tetromino_bit(k);
      if (draw)
        draw_square(translate_to_screen_x_cord(x_pos + px),
            translate_to_screen_y_cord(y_pos + py),3);
    }
  }
}

void draw_current_well() {
  int px,py;

  for (px = 0; px < WELL_WIDTH; px++){
    for (py = 0; py < 24; py++){
      int draw = get_byte_bit(well[well_byte_index(px,py)], (py%8));
      if (draw)
        draw_square(translate_to_screen_x_cord(px),
                    translate_to_screen_y_cord(py), 3);
    }
  }
}

bool tetris_does_tetromino_fit(int x, int y, uint8_t rot) {
  int px,py;
  for (px = 0; px < 4; px++) {
    for (py = 0; py < 4; py++) {
      uint8_t k = tetris_rotate_tetromino(px,py,rot);
      uint8_t tetro_part = get_tetromino_bit(k);

      int cx = px + x, cy = py + y;
      uint8_t well_square = ((cx >= 0 && cx < WELL_WIDTH ) && cy < 24) ?
        get_byte_bit(well[well_byte_index(cx, cy)], cy % 8) : 0;
      // check if x or y are within the playing field, otherwise we need to handle it.

      if((cx < 0 || cx >= WELL_WIDTH) && tetro_part) {
        return false;
      } 

      if((cy >= 24) && tetro_part) {
        return false;
      }

      if (cx >= 0 && cx < WELL_WIDTH) {
        if (cy >= 0 && cy < 24) {
          if(tetro_part && well_square)
            return false;
        } 
      }
    }
  }
  return true;
}

void tetris_force_down(void) {
  if (tetris_does_tetromino_fit(x_pos, y_pos + 1, current_rotation)) {
    y_pos++;
  } else {
    // could not move tetromino down. lock into place in well
    int px, py;
    for (px = 0; px < 4; px++) {
      for (py = 0; py < 4; py++) {
        uint8_t k = tetris_rotate_tetromino(px,py,current_rotation);
        uint8_t tetro_part = get_tetromino_bit(k);

        if(tetro_part) { /* if we get a piece, write it to the well */
          int cx = x_pos + px;
          int cy = y_pos + py;

          well[well_byte_index(cx,cy)] |= (0x80 >> (cy % 8));
        }
      }
    }

    // TODO clear lines
    // TODO Move down bits above.
    for (py = y_pos; py < (y_pos + 4); py++) {
      bool full_row = true;
      for (px = 0; px < WELL_WIDTH; px++) {
        if( !(well[well_byte_index(px,py)] & (0x80 >> (py % 8)))) {
          full_row = false;
          break;
        }
      }

      if (full_row) {

      }
    }

    tetro_mem = (uint8_t)(timer_read() % 7 << 3 ) | (tetro_mem >> 3);
    x_pos = 3;
    y_pos = 0;


  }
}


void tetris_tick() {
  if(((flags & (TETRIS_FLAG_LEFT)) | (flags & (TETRIS_FLAG_RIGHT))) != 0x03) {
    if (flags & TETRIS_FLAG_LEFT) {
      if(tetris_does_tetromino_fit(x_pos - 1, y_pos, current_rotation)) {
        x_pos = x_pos - 1;
        flags &= ~TETRIS_FLAG_LEFT;
      }
    } else if (flags & TETRIS_FLAG_RIGHT) {
      if(tetris_does_tetromino_fit(x_pos + 1, y_pos, current_rotation)) {
        x_pos = x_pos + 1;
        flags &= ~TETRIS_FLAG_RIGHT;
      }
    }
  }

  if(flags & (TETRIS_FLAG_DOWN)) {
    if(tetris_does_tetromino_fit(x_pos, y_pos + 1, current_rotation)) { y_pos++; }
  }

  if(flags & (TETRIS_FLAG_ROTATE)) {
    if(tetris_does_tetromino_fit(x_pos, y_pos, (current_rotation + 1 % 4))) {
      current_rotation = (current_rotation + 1) % 4;;
    }
  }

  flags = 0x00;

  if (timer_elapsed(drop_timer) > drop_time) {
    tetris_force_down();
    drop_timer = timer_read();
  }

  tetris_render();
}

void tetris_reset() {
  // TODO implement me!
  // 1 add keybinding for reset
  // 2 enable if gameover == true
}

void draw_square(uint16_t x, uint16_t y, uint16_t len) {
  uint16_t px, py; // to avoid to cast in screen byte definition
  for (px = x; px < x + len; px++) {
    for (py = y; py < y + len; py++) {
      if ((px != x  && px != x + len - 1) && (py != y && py != y + len - 1)) continue;
      screen[screen_byte_index(px,py)] |= draw_bits[py % 8];
    }
  }
}

void tetris_player_input(enum tetris_input input) {
  flags |= (1 << input);
}


