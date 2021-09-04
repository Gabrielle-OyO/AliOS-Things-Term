#include <stdio.h>
#include <aos/kernel.h>
#include "aos/hal/gpio.h"
gpio_dev_t Led1;
gpio_dev_t Led2;

int application_start(int argc, char *argv[])
{
	int count = 0;
	printf("nano entry here!\r\n");
	//led setting
	Led1.port=13;
	Led1.config=OUTPUT_PUSH_PULL;
	hal_gpio_init(&Led1);
	hal_gpio_output_high(&Led1);
	hal_dac_start(0,2);
    while(1) {
		for(count=0;count<256;count++)
		{
			hal_dac_set_value(0, 2, count);
			printf("%d\r\n",count);
			aos_msleep(5);
		}
		for(count=255;count>=0;count--)
		{
			hal_dac_set_value(0, 2, count);
			printf("%d\r\n",count);
			aos_msleep(5);
		}
    };
}
