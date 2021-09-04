/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */
#include <k_api.h>
#include <stdio.h>
#include <aos/kernel.h>

//定义函数
aos_task_t task1;
aos_task_t task2;
aos_task_t task3;

//循环输出
void func(void * arg)
{
	while(1)
	{
		printf("%s\r\n",(char*)arg);
		aos_msleep(1000);
	}
}
int application_start(int argc, char *argv[])
{
    int tmp=0;
    printf("nano entry here!\r\n");
	aos_task_new_ext(&task1,"task1", func,(void*)"task1 run!", 8192,33);
	aos_task_new_ext(&task2,"task2", func,(void*)"task2 run!", 8192,33);
	aos_task_new_ext(&task3,"task3", func,(void*)"task3 run!", 8192,33);
    while(1) {
        printf("maintask print %d\r\n",tmp);
		tmp++;
        aos_msleep(1000);
    };
}
