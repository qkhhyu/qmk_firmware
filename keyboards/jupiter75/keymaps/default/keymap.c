/*
Copyright 2018 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "app_ble_func.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    SEL_BLE,		  /* Select BLE HID Sending		  */
    SEL_USB,		  /* Select USB HID Sending		  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */

    RGBRST,
    RGBTOG,
};


extern keymap_config_t keymap_config;

enum {
  BASE=0,
  META,
  SYMB,
  CTRL,
  ABS_MOUSE,
  GAME
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//     {
// //    {KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I,
// //        KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, AD_WO_L, USB_EN, BATT_LV}
//     {KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I,
//         KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S}
//     }
// };


// const uint16_t keymaps[][6][15] = {

//       [0] = LAYOUT(KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_PSCR,KC_DEL,
// KC_GRV,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSPC,KC_HOME,
// KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSLS,KC_PGUP,
// KC_CAPS,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_ENT,KC_PSCR,KC_PGDN,
// KC_LSFT,KC_BSLS,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_UP,KC_END,
// KC_LCTL,KC_LGUI,KC_LALT,KC_NO,KC_NO,KC_NO,KC_SPC,KC_NO,KC_NO,KC_NO,MO(1),KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),
//       [1] = LAYOUT(SEL_BLE,ADV_ID0,ADV_ID1,ADV_ID2,ADV_ID3,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,BLE_EN,BLE_DIS,KC_NO,DELBNDS,
// SEL_USB,RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,RGBTOG,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
// KC_TAB,RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGBRST,KC_NO,USB_EN,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
// KC_TRNS,AD_WO_L,ENT_SLP,ENT_DFU,USB_DIS,BLE_DIS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
// KC_TRNS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,BLE_EN,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
// KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,MO(1),KC_NO,KC_NO,KC_NO,KC_NO),

// };
const uint16_t keymaps[][6][15] = {

      [0] = LAYOUT(RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_PSCR,KC_DEL,
RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGBRST,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSPC,KC_HOME,
KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSLS,KC_PGUP,
KC_CAPS,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_ENT,KC_PSCR,KC_PGDN,
KC_LSFT,KC_BSLS,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_UP,KC_END,
KC_LCTL,KC_LGUI,KC_LALT,KC_NO,KC_NO,KC_NO,KC_SPC,KC_NO,KC_NO,KC_NO,MO(1),KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),
      [1] = LAYOUT(SEL_BLE,ADV_ID0,ADV_ID1,ADV_ID2,ADV_ID3,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,BLE_EN,BLE_DIS,KC_NO,DELBNDS,
SEL_USB,RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,RGBTOG,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
KC_TAB,RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGBRST,KC_NO,USB_EN,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
KC_TRNS,AD_WO_L,ENT_SLP,ENT_DFU,USB_DIS,BLE_DIS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
KC_TRNS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,BLE_EN,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,MO(1),KC_NO,KC_NO,KC_NO,KC_NO),

};
#define DFU_MAGIC_UF2_RESET             0x57
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];
  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case SEL_BLE:
      if (keycode) {
        set_ble_enabled(true);
        set_usb_enabled(false);
      }
      break;
    case SEL_USB:
      if (keycode) {
        set_ble_enabled(false);
        set_usb_enabled(true);
      }
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      // sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
      // NVIC_SystemReset();

      return false;
      case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          // nrfmicro_power_enable(true);
          eeconfig_update_rgblight_default();
          rgblight_enable();
          // RGB_current_mode = rgblight_config.mode;
          // NRF_LOG_INFO("RGBRST, RGB_current_mode: %d\n", RGB_current_mode);
        }
      #endif
      break;
    case RGBTOG:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          // if(!rgblight_config.enable)
          {
            eeconfig_update_rgblight_default();
            rgblight_enable();
          }
          // else{
          //   rgblight_disable();
          // }
        }
      #endif
      break;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }

  }
  return true;
}
;
