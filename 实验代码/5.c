/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>

int application_start(int argc, char *argv[])
{
    int count = 0;
	long long t1,t2;
    printf("nano entry here!\r\n");

    while(1) {
        
		t1=aos_now_ms ();
		aos_msleep(1);
		t2=aos_now_ms ();
		printf("time %lld \r\n", t2-t1);
    };
}
