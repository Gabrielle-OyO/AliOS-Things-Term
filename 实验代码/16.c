#include <stdio.h>
#include <aos/kernel.h>
#include "aos/hal/gpio.h"
aos_task_t htask1;
aos_task_t htask2;
gpio_dev_t Led1;
gpio_dev_t Led2;

void func1(void * arg)
{
	while(1)
	{
		hal_gpio_output_toggle(&Led1);
		aos_msleep(300);
	}
}
void func2(void * arg)
{
	while(1)
	{
		hal_gpio_output_toggle(&Led2);
		aos_msleep(1000);
	}
}

int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	Led1.port=13;
	Led1.config=OUTPUT_PUSH_PULL;
	Led2.port=26;
	Led2.config=OUTPUT_PUSH_PULL;
	hal_gpio_init(&Led1);
	hal_gpio_init(&Led2);
	hal_gpio_output_high(&Led1);
	hal_gpio_output_low(&Led2);
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);
    while(1) {
        aos_msleep(1000);
    };
}
