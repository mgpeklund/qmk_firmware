#pragma once

#include QMK_KEYBOARD_H


#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif

#include "layers.h"



//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(void) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  oled_write_P(helix_logo, false);
  //oled_write_P(&PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      oled_write(buf,false);
  }
#endif
}

static void render_layer_status(void) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
          oled_write_P(PSTR("Default"), false);
          break;
        case L_RAISE:
           oled_write_P(PSTR("Raise"), false);
           break;
        case L_LOWER:
           oled_write_P(PSTR("Lower"), false);
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           oled_write_P(PSTR("Adjust"), false);
           break;
        default:
           oled_write_P(PSTR("Undef-"), false);
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           oled_write(buf, sizeof(buf));
    }
}

static void render_status(void) {

  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    oled_write_P(os_logo[0][0], false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(os_logo[0][1], false);
  }else{
    oled_write_P(os_logo[1][0], false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(os_logo[1][1], false);
  }

  oled_write_P(PSTR(" "), false);
  render_layer_status();
  oled_write_P(PSTR("\n"), false);

  // Host Keyboard LED Status
  oled_write_P((host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "), false);
  oled_write_P((host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "), false);
  oled_write_P((host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "), false);
  oled_write_P(PSTR("\n"), false);
  render_rgbled_status(true);
}


static void (*master_screen_renderer)(void) = NULL;
static void (*slave_screen_renderer)(void)  = NULL;

void set_master_screen_renderer(void (*f)(void))  {
#ifdef CONSOLE_ENABLE
  print("setting master renderer\n");
#endif
  master_screen_renderer = f;
}
void set_slave_screen_renderer(void (*f)(void))   {
#ifdef CONSOLE_ENABLE
  print("setting slave renderer\n");
#endif
  slave_screen_renderer = f;
}

void set_default_renderers(void) {
  set_master_screen_renderer(&render_status);
  set_slave_screen_renderer(&render_logo);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (master_screen_renderer == NULL || slave_screen_renderer == NULL)
   set_default_renderers(); 
  if (!is_keyboard_master()) {
      return OLED_ROTATION_180;
  }
  return rotation;
}

void oled_task_user() {

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  if(is_keyboard_master()){
    master_screen_renderer();
  } else {
    slave_screen_renderer();
  }
}

