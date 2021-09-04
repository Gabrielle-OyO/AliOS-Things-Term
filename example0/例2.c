/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>

#include <aos/kernel.h>

aos_timer_t mytimer1;
void func(void * timer,void * arg)
{
	printf("Hello\r\n");
}


int application_start(int argc, char *argv[])
{
    int count = 0;
    printf("nano entry here!\r\n");
	aos_timer_new(&mytimer1, func, 0, 2000, 1);
	aos_timer_start(&mytimer1);
    while(1) {
        printf("hello world! count %d \r\n", count++);
        aos_msleep(1000);
    };
}
