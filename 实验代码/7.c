//krhino_idle_add_hook have bug, need to add "break;"

#include <stdio.h>
#include <k_api.h>
#include <aos/kernel.h>
void hook1(void)
{
	printf("idle hook1\r\n");
}
void hook2(void)
{
	printf("idle hook2\r\n");
}
int application_start(int argc, char *argv[])
{
    int count = 0;
    printf("nano entry here!\r\n");
	krhino_idle_add_hook(hook1,0);
	krhino_idle_add_hook(hook2,0);
    while(1) {
        printf("task run now!\r\n");
		count++;
		if(count>100)
        	aos_msleep(300);
    };
}
