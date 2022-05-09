#include "lando75.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrfx_pwm.h"
#include "nrf.h"
#include "app_ble_func.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// adafruit bootloader, send "dfu" to debug serial port
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}

bool has_usb(void)
{
  return ((nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_CONNECTED) || (nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_READY));
}

// static bool ble_flag = false;

void nrfmicro_power_enable(bool enable)
{
  if (has_usb())
      enable = true;

	if (enable)
	{
		/*
		nrf_gpio_cfg_output(POWER_PIN);	//disable power pin feature
		nrf_gpio_pin_set(POWER_PIN);
		*/
		nrf_gpio_cfg_output(POWER_PIN);
		nrf_gpio_pin_clear(POWER_PIN);
	}
	else
	{
		nrf_gpio_cfg_output(POWER_PIN);
		nrf_gpio_pin_set(POWER_PIN);
		/*
		nrf_gpio_cfg_output(POWER_PIN); //disable power pin feature
		nrf_gpio_pin_clear(POWER_PIN); // works
		*/
		//input with pull-up consumes less than without it when pin is open (Hasu)
		//nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_PULLUP); // doesn't seem to work
		//nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_NOPULL); // neither this
		//nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_PULLDOWN); // or this
	}
}



//switch to usb mode when usb cable connected
void check_usb_power(void)
{
	if(has_usb())
	{
		if(!get_usb_enabled() && get_ble_enabled())
		{
			set_usb_enabled(true);
			set_ble_enabled(false);
		}
  	}
	else
	{
  		if(get_usb_enabled() && !get_ble_enabled())
		{
			set_usb_enabled(false);
			set_ble_enabled(true);
		}
  	}
}

void nrfmicro_powerpin_switch(bool status)
{
  if(status)
  {
    nrf_gpio_pin_clear(POWER_PIN);
  }
  else
  {
    nrf_gpio_pin_set(POWER_PIN);
  }
}

void nrfmicro_init() {
  // configure pins
  nrf_gpio_cfg_output(POWER_PIN);
  nrf_gpio_cfg_output(CAPS_LED);
  // nrf_gpio_cfg_input(SWITCH_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrfmicro_power_enable(false);
  nrf_delay_ms(100);

  // nrfmicro_power_enable(false);
  // check_ble_switch(true);
}

void update_caps_led()
{
	if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))
  {
		nrf_gpio_pin_set(CAPS_LED);
	} else {
		nrf_gpio_pin_clear(CAPS_LED);
	}
  NRF_LOG_INFO("aaausb_led:%x",host_keyboard_leds());

}

void eeprom_update(void);

void nrfmicro_update()
{
	check_usb_power();
	eeprom_update();
  // update_caps_led();
}

void keyboard_post_init_kb()
{
	// nrfmicro_power_enable(false); //power pin
  // if(!rgblight_config.enable)
  // {
  // 	nrfmicro_power_enable(false); //power pin
  // }
  // if(rgblight_config.enable)
  // {
  // 	nrfmicro_power_enable(true); //power pin
  // }
  // {
  // 	nrfmicro_power_enable(true); //power pin
  // }
}
