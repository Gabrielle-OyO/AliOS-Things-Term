#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>
#define QUEUESIZE	1024
aos_task_t htask1;
aos_task_t htask2;
aos_queue_t que;
uint8_t queBuf[QUEUESIZE];
void func1(void * arg)
{
	int count=0;
	while(1)
	{
		aos_queue_send(&que, &count, sizeof(int));
		count++;
		aos_msleep(500);
	}
}
void func2(void * arg)
{
	int count;
	unsigned int size;
	while(1)
	{
		aos_queue_recv(&que, AOS_WAIT_FOREVER, &count, &size);
		printf("count=%d,size=%d\r\n",count,size);
	}
}
int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	aos_queue_new(&que,queBuf,QUEUESIZE,sizeof(int));
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);
    while(1) {
        aos_msleep(1000);
    };
}
