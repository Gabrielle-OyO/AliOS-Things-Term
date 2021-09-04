/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>

aos_task_t htask1;
aos_task_t htask2;
aos_sem_t semcount;

void func1(void * arg)
{
	while(1)
	{
		aos_sem_wait(&semcount, AOS_WAIT_FOREVER);
		printf("task1 running!\r\n");
	}
}
void func2(void * arg)
{
	while(1)
	{
		printf("task2 running!\r\n");
		aos_sem_signal(&semcount);
		aos_msleep(1000);
	}
}
int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	aos_sem_new(&semcount, 0);
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);
    while(1) {
        aos_msleep(1000);
    };
}
