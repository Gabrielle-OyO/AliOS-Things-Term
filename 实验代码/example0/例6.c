/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>
#include <k_api.h>


aos_task_t htask1;
aos_task_t htask2;
aos_task_t htask3;

kevent_t event;


void func1(void * arg)
{
	uint32_t flag;
	while(1)
	{
		krhino_event_get(&event,0x03,RHINO_AND_CLEAR,&flag,RHINO_WAIT_FOREVER);
		printf("task1 running!\r\n");
	}
}
void func2(void * arg)
{
	while(1)
	{
		printf("task2 running!\r\n");
		krhino_event_set(&event,0x01,RHINO_OR);
		aos_msleep(1000);
	}
}
void func3(void * arg)
{
	while(1)
	{	
		printf("task3 running!\r\n");
		krhino_event_set(&event,0x02,RHINO_OR);
		aos_msleep(2000);
	}
}

int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	krhino_event_create(&event,"myevent",0);
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);
	aos_task_new_ext(&htask3,"task3", func3,0, 8192,35);
    while(1) {
        aos_msleep(1000);
    };
}
