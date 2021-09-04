#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>
#define QUEUESIZE	1024
aos_task_t htask1;
aos_task_t htask2;
aos_task_t htask3;
aos_queue_t que;
uint8_t queBuf[QUEUESIZE];
char strBuf[100];//字符串地址
void func1(void * arg)
{
	int count=0;
	char* str=strBuf;
	while(1)
	{
		sprintf(strBuf,"task1 send msg %d\r\n",count);
		aos_queue_send(&que, &str, sizeof(char*));
		count++;
		aos_msleep(1000);
	}
}
void func2(void * arg)
{
	char *str;
	unsigned int size;
	while(1)
	{
		aos_queue_recv(&que, AOS_WAIT_FOREVER, &str, &size);//取指针，打印信息，哪个任务获取就是哪个任务打印字串
		//printf("%s,size=%d\r\n",str,size);
		//printf("%s",(char*)arg);
		printf("%s recv: ",(char*)arg);
		printf("%s",str);
	}
}
int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	aos_queue_new(&que,queBuf,QUEUESIZE,sizeof(char*));//传递字符串的指针
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,35);
	aos_task_new_ext(&htask2,"task2", func2,"task2", 8192,33);
	aos_task_new_ext(&htask3,"task3", func2,"task3", 8192,34);
    while(1) {
        aos_msleep(1000);
    };
}
