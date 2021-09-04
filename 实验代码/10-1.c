/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */
//低---高---中---中---低---高
#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>

aos_task_t htask1;
aos_task_t htask2;
aos_task_t htask3;

aos_sem_t semcount;

void funcH(void * arg)//低优先级任务结束，高优先级唤醒
{
	aos_msleep(1000);
	printf("TaskH running!\r\n");
	printf("TaskH wait sem!\r\n");
	aos_sem_wait(&semcount, AOS_WAIT_FOREVER);
	printf("TaskH get sem!\r\n");
	printf("TaskH signal sem!\r\n");
	aos_sem_signal(&semcount);
	while(1)
	{
		aos_msleep(1000);
	}
}
void funcM(void * arg)//高优先级任务结束，中优先级任务运行//低优先级任务优先级低，中抢高运行
{
	int count=0;
	long long time=0;
	long long timeold=0;
	aos_msleep(1000);
	while(1)
	{	
		time=aos_now_ms();
		if((time%1000==0)&&(time!=timeold))
		{
			printf("TaskM running!\r\n");
			count++;
			timeold=time;
		}
		if(count==10)
			break;
	}
	while(1)
	{
		aos_msleep(1000);
	}
}
void funcL(void * arg)
{
	int count=0;
	long long time=0;
	long long timeold=0;
	printf("TaskL running!\r\n");
	printf("TaskL wait sem!\r\n");
	aos_sem_wait(&semcount, AOS_WAIT_FOREVER);
	printf("TaskL get sem!\r\n");
	while(1)
	{	
		time=aos_now_ms();
		if((time%1000==0)&&(time!=timeold))
		{
			printf("TaskL running!\r\n");
			count++;
			timeold=time;
		}
		if(count==10)
			break;
	}
	printf("TaskL signal sem!\r\n");
	aos_sem_signal(&semcount);
	while(1)
	{	
		aos_msleep(1000);
	}
}

int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	aos_sem_new(&semcount, 1);
	aos_task_new_ext(&htask1,"taskH", funcH,0, 8192,33);
	aos_task_new_ext(&htask2,"taskM", funcM,0, 8192,34);
	aos_task_new_ext(&htask3,"taskL", funcL,0, 8192,35);//低优先级先运行，获取信号量
    while(1) {
        aos_msleep(1000);
    };
}
