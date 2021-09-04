/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>

#include <aos/kernel.h>

volatile int count1=0;
volatile int count2=0;
aos_task_t htask1;
aos_task_t htask2;


void func1(void * arg)
{
	while(1)
		count1++;
}
void func2(void * arg)
{
	while(1)
		count2++;
}
int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,33);
    while(1) {
        printf("count1=%d,count2=%d\r\n",count1,count2);
        aos_msleep(1000);
    };
}
