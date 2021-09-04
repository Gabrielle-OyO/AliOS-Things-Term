/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */
#include <k_api.h>
#include <stdio.h>
#include <aos/kernel.h>

aos_task_t htask1;
aos_task_t htask2;
aos_task_t htask3;

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
	aos_task_new_ext(&htask1,"task1", func,(void*)"task1 run!", 8192,35);
	aos_task_new_ext(&htask2,"task2", func,(void*)"task2 run!", 8192,34);
	aos_task_new_ext(&htask3,"task3", func,(void*)"task3 run!", 8192,33);
    while(1) {
        printf("maintask print %d\r\n",tmp);
		tmp++;
		if(tmp==10)
			krhino_task_suspend((ktask_t *)(htask2.hdl));//挂起任务2
		if(tmp==20)
			krhino_task_resume((ktask_t *)(htask2.hdl));//恢复任务2
        aos_msleep(1000);
    };
}
