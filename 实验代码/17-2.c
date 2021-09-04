#include <stdio.h>
#include <aos/kernel.h>
#include "aos/hal/gpio.h"
gpio_dev_t Led1;
gpio_dev_t Led2;
gpio_dev_t Key1;
volatile int keyflag=0;

void keyhandler(void* arg)
{
	keyflag=1;
}

int application_start(int argc, char *argv[])
{
	//uint32_t Key1Value;
	printf("nano entry here!\r\n");
	//led setting
	Led1.port=13;
	Led1.config=OUTPUT_PUSH_PULL;
	Led2.port=26;
	Led2.config=OUTPUT_PUSH_PULL;
	hal_gpio_init(&Led1);
	hal_gpio_init(&Led2);
	hal_gpio_output_high(&Led1);
	hal_gpio_output_low(&Led2);
	//key setting
	Key1.port=0;
	Key1.config=IRQ_MODE;
	hal_gpio_init(&Key1);
	hal_gpio_enable_irq(&Key1,IRQ_TRIGGER_RISING_EDGE,keyhandler,NULL);

    while(1) {
		if(keyflag)
		{
			keyflag=0;
			hal_gpio_output_toggle(&Led1);
		}
        aos_msleep(300);
    };
}
