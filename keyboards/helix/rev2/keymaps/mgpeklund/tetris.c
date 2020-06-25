#include "tetris.h"
/*
uint16_t index_ints[16] = {
  0x0001,
  0x0002,
  0x0004,
  0x0008,
  0x0010,
  0x0020,
  0x0040,
  0x0080,
  0x0100,
  0x0200,
  0x0400,
  0x0800,
  0x1000,
  0x2000,
  0x4000,
  0x8000
};

uint16_t tetromino[7] = { 
  0b0010001000100010, // I
  0b0100011000100000, // S
  0b0010011001000000, // Z
  0b0010011000100000, // T
  0b0000011001100000, // O
  0b0000010001000110, // L
  0b0000001000100110  // J
}; 
*/

uint8_t tetris_rotate_tetromino(int px, int py, int r) {
	switch(r % 4) {
		case 0: return py * 4 + px;			//   0 degrees
		case 1: return 12 + py - (px * 4);	//  90 degrees
		case 2: return 15 - (py * 4) - px;	// 180 degrees
		case 3: return 3 - py + (px * 4);	// 270 degrees
	}
	return 0;
}

void tetris_init() {
  // TODO implement me!
};

void tetris_render() {
  oled_write_raw_P(tetris_screen,BOARD_SIZE);
};


void tetris_reset() {
  // TODO implement me!
}


void tetris_update_well() {
  // TODO implement me!
}


