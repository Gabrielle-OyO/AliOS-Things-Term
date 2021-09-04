#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>
aos_task_t htask1;
aos_task_t htask2;
aos_sem_t semcount;
volatile int totalcount=0;
void func1(void * arg)
{
	int tmp;
	while(1)
	{
		aos_sem_wait(&semcount,AOS_WAIT_FOREVER);
		volatile int count1=0;
		count1++;
		tmp=totalcount;
		tmp=tmp+1;
		totalcount=tmp;
		aos_msleep(10);
	}
}
void func2(void * arg)
{
	int tmp;
	while(1)
	{
		aos_sem_signal(&semcount);
		volatile int count2=0;
		count2++;
		tmp=totalcount;
		tmp=tmp+1;
		totalcount=tmp;
	}
}
int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	count1=0;
	count2=0;
	aos_sem_new(&semcount,0);
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);
    while(1) {
        printf("cnt1=%d,cnt2=%d,cnt1+cnt2=%d,totalcnt=%d \r\n", count1,count2,count1+count2,totalcount);
        aos_msleep(1000);
    };
}#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>
aos_task_t htask1;
aos_task_t htask2;
aos_sem_t semcount;
volatile int totalcount=0;
void func1(void * arg)
{
	int tmp;
	while(1)
	{
		aos_sem_wait(&semcount,AOS_WAIT_FOREVER);
		volatile int count1=0;
		count1++;
		tmp=totalcount;
		tmp=tmp+1;
		totalcount=tmp;
		aos_msleep(10);
	}
}
void func2(void * arg)
{
	int tmp;
	while(1)
	{
		aos_sem_signal(&semcount);
		volatile int count2=0;
		count2++;
		tmp=totalcount;
		tmp=tmp+1;
		totalcount=tmp;
	}
}
int application_start(int argc, char *argv[])
{
    printf("nano entry here!\r\n");
	count1=0;
	count2=0;
	aos_sem_new(&semcount,0);
	aos_task_new_ext(&htask1,"task1", func1,0, 8192,33);
	aos_task_new_ext(&htask2,"task2", func2,0, 8192,34);
    while(1) {
        printf("cnt1=%d,cnt2=%d,cnt1+cnt2=%d,totalcnt=%d \r\n", count1,count2,count1+count2,totalcount);
        aos_msleep(1000);
    };
}