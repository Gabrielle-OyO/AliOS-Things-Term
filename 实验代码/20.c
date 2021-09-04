#include <stdio.h>
#include <aos/kernel.h>
#include "aos/hal/gpio.h"
#include "aos/hal/pwm.h"

gpio_dev_t Led1;
gpio_dev_t Led2;
pwm_dev_t LedPwm;

int application_start(int argc, char *argv[])
{
    int count = 0;
    pwm_config_t pwmparam;
    printf("nano entry here!\r\n");
    //led setting
    Led1.port=13;
    Led1.config=OUTPUT_PUSH_PULL;
    hal_gpio_init(&Led1);
    hal_gpio_output_high(&Led1);
    //LedPwm setting
    LedPwm.port=26;
    LedPwm.config.duty_cycle=0.001;
    LedPwm.config.freq=2000;
    hal_pwm_init(&LedPwm);
    hal_pwm_start(&LedPwm);
    while(1) {
        for(count=0;count<=280;count++)
        {
            pwmparam.duty_cycle=count*0.001;
            hal_pwm_para_chg(&LedPwm,pwmparam);
            printf("zyy%d",count);
            aos_msleep(5);
        }
        for(count=280;count>=0;count--)
        {
            pwmparam.duty_cycle=count*0.001;
            hal_pwm_para_chg(&LedPwm,pwmparam);
            printf("zyy%d",count);
            aos_msleep(5);
        }
    };
}
/*
add code to AliOS-Things-rel_3.1.0\platform\mcu\esp32\hal\pwm.c
//only change duty
int32_t hal_pwm_para_chg(pwm_dev_t *pwm, pwm_config_t para)
{
	uint32_t duty;
	int8_t slot_idx = find_registered_slot_by_gpio_num(pwm->port);
    if (slot_idx < 0)
    {
        return -1;
    }
	duty=LEDC_CHANNEL_MAX_DUTY*para.duty_cycle;
	ledc_set_duty(DEFAULT_LEDC_SPEED_MODE, slot_idx, duty);
	return ledc_update_duty(DEFAULT_LEDC_SPEED_MODE, slot_idx);
}

*/
