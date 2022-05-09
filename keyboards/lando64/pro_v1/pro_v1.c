
#include "app_ble_func.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif
#include "matrix.h"

#include "app_ble_func.h"

#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrfx_pwm.h"
#include "nrf.h"
#include "lando64.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

void matrix_init_user() {
  #ifdef RGBLIGHT_ENABLE
  // rgblight_mode_noeeprom(35);

  // eeconfig_update_rgblight_default();
  // rgblight_enable();
  // rgblight_mode(15);
	#endif
  nrfmicro_init();
  // set_usb_enabled(true);

}

void matrix_scan_user(void)
{
  nrfmicro_update();
}


