#include <stdio.h>
#include <aos/kernel.h>
#include "aos/hal/gpio.h"
#include "aos/hal/adc.h"

gpio_dev_t Key1;
adc_dev_t adcchan1;
adc_dev_t adcchan2;
adc_dev_t adcchan3;


int application_start(int argc, char *argv[])
{
    uint32_t Key1Value;
    uint32_t Key2Value;
    uint32_t Key3Value;
    uint32_t Key4Value;
    printf("nano entry here!\r\n");
    //key setting
    Key1.port=0;
    Key1.config=INPUT_PULL_UP;
    hal_gpio_init(&Key1);
    //adc setting
    adcchan1.port=35;
    adcchan2.port=34;
    adcchan3.port=39;
    hal_adc_init(&adcchan1);
    hal_adc_init(&adcchan2);
    hal_adc_init(&adcchan3);

    while(1) {
        hal_gpio_input_get(&Key1, &Key1Value);
        hal_adc_value_get(&adcchan1, &Key2Value, HAL_WAIT_FOREVER);
        hal_adc_value_get(&adcchan2, &Key3Value, HAL_WAIT_FOREVER);
        hal_adc_value_get(&adcchan3, &Key4Value, HAL_WAIT_FOREVER);
        if(Key1Value==0)
            printf("zyy press key1!\r\n");
        if(Key2Value==0)
            printf("zyy press key2!\r\n");
        if(Key3Value==0)
            printf("zyy press key3!\r\n");
        if(Key4Value==0)
            printf("zyy press key4!\r\n");
        aos_msleep(300);
    };
}
