#include <stdio.h>
#include <k_api.h>
#include <aos/kernel.h>
void hook1(void)
{
	printf("idle hook1\r\n");
}
int application_start(int argc, char *argv[])
{
    int count = 0;
    printf("nano entry here!\r\n");
	krhino_idle_add_hook(hook1,0);
    while(1) {
        printf("task run now!\r\n");
        aos_msleep(500);
    };
}
