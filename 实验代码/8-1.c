/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>

aos_task_t htask1;
aos_task_t htask2;
volatile int count1=0;
volatile int count2=0;
volatile int totalcount=0;
void func1(void * arg)
{
	int tmp;
	while(1)
	{
	printf("Hello\r\n");
	count1++;
	}
}
void func2(void * arg)
{
	printf("Hello\r\n");
	count2++;
}
int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);
    while(1) {
        printf("cnt1=%d,cnt2=%d,cnt1+cnt2=%d,totalcnt=%d \r\n", count1,count2,count1+count2,totalcount);
        aos_msleep(1000);
    };
}
