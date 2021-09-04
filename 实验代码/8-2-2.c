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
aos_sem_t semcount;

void func1(void * arg)
{
	int tmp;
	while(1)
	{
		
		aos_sem_wait(&semcount, AOS_WAIT_FOREVER);//获取
		count1++;
		tmp=totalcount;
		tmp=tmp+1;
		totalcount=tmp;
		aos_sem_signal(&semcount);//释放
		aos_msleep(10);
	}
}
void func2(void * arg)
{
	int tmp;
	while(1)
	{
		
		aos_sem_wait(&semcount, AOS_WAIT_FOREVER);
		count2++;
		tmp=totalcount;
		tmp=tmp+1;
		totalcount=tmp;
		aos_sem_signal(&semcount);
	}
}
int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	count1=0;
	count2=0;
	aos_sem_new(&semcount, 1);//创建函数，启动访问
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);
    while(1) {
        printf("cnt1=%d,cnt2=%d,cnt1+cnt2=%d,totalcnt=%d \r\n", count1,count2,count1+count2,totalcount);
        aos_msleep(1000);
    };
}
