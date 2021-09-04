/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>

#include <aos/kernel.h>

aos_timer_t mytimer1;
int count1=0;
void func(void * timer,void * arg)
{
	printf("Hello\r\n");
	count1++;
}


int application_start(int argc, char *argv[])
{
    int count = 0;
    printf("nano entry here!\r\n");
	aos_timer_new(&mytimer1, func, 0, 2000, 1);
	aos_timer_start(&mytimer1);
    while(1) {
		if(count1==5)
		{
			aos_timer_stop(&mytimer1);
			aos_timer_change(&mytimer1, 1000);
			aos_timer_start(&mytimer1);
		}
        printf("hello world! count %d \r\n", count++);
        aos_msleep(1000);
    };
}
