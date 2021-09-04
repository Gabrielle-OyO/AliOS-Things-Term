
#include <stdio.h>
#include <stdint.h>
#include <aos/kernel.h>
#include "aos/yloop.h"

void func(void * arg)
{
	printf("hello yloop\r\n");
	aos_post_delayed_action(1000,func,0);
}


int application_start(int argc, char *argv[])
{
    int count = 0;
    printf("nano entry here!\r\n");
	aos_post_delayed_action(1000,func,0);
	aos_loop_run();
	return 0;
}
