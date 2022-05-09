
#include "app_ble_func.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif
void matrix_init_user() {

  set_usb_enabled(true);
  eeconfig_update_rgblight_default();
  rgblight_enable();
}


