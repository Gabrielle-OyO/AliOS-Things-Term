/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>
#include <k_api.h>

#define STRBUFSIZE	1024	//分配空间
aos_task_t htask1;
aos_task_t htask2;

aos_sem_t sem1;		//创建信号量
aos_sem_t sem2;
char * str=NULL; 

void func1(void * arg)
{
	int count=0;
	while(1)
	{
		aos_sem_wait(&sem2, AOS_WAIT_FOREVER);//获取信号量
		str=(char*)aos_malloc(STRBUFSIZE);
		if(str==NULL)		//错误判断
		{
			printf("aos_malloc fail!\r\n");
			continue;
		}
		sprintf(str, "aos_malloc running %d\r\n",count);//字串打印到缓存中
		count++;
		aos_sem_signal(&sem1);//释放信号量
		aos_msleep(500);
	}
}
void func2(void * arg)
{
	while(1)
	{
		aos_sem_wait(&sem1, AOS_WAIT_FOREVER);		//必须等到任务1运行
		printf("%s",str);
		//aos_free(str);//删除信号量
		str=NULL;
		aos_sem_signal(&sem2);
	}
}


int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	aos_sem_new(&sem1, 0);		//初始值为0
	aos_sem_new(&sem2, 1);		//初始值必须是1，得到信号
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);

    while(1) {
        aos_msleep(1000);
    };
}
