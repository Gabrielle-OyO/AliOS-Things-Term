/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>

#include <aos/kernel.h>

void func1(void * arg)
{
	int tmp=0;
	while(1)
	{
		printf("task1 print %d\r\n",tmp);
		tmp++;
		aos_msleep(1000);
	}
}
void func2(void * arg)
{
	int tmp=0;
	while(1)
	{
		printf("task2 print %d\r\n",tmp);
		tmp++;
		aos_msleep(1000);
	}
}
int application_start(int argc, char *argv[])
{
    int tmp=0;
    printf("nano entry here!\r\n");
	aos_task_new("task1", func1,0, 8192);
	aos_task_new("task2", func2,0, 8192);
    while(1) {
        printf("maintask print %d\r\n",tmp);
		tmp++;
        aos_msleep(1000);
    };
}
