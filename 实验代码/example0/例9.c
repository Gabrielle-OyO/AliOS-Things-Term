#include <stdio.h>
#include <aos/kernel.h>
#include "aos/hal/gpio.h"

int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	gpio_dev_t Led1;
	gpio_dev_t Led2;
	Led1.port=13;
	Led1.config=OUTPUT_PUSH_PULL;
	Led2.port=26;
	Led2.config=OUTPUT_PUSH_PULL;
	hal_gpio_init(&Led1);
	hal_gpio_init(&Led2);
	hal_gpio_output_high(&Led1);
	hal_gpio_output_low(&Led2);
    while(1) {
		hal_gpio_output_toggle(&Led1);
		hal_gpio_output_toggle(&Led2);
        aos_msleep(1000);
    };
}
