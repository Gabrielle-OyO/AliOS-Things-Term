/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <aos/kernel.h>
#include <stdint.h>
#define STRBUFSIZE	1024
int application_start(int argc, char *argv[])
{
	char * str=NULL; 
	int count=0;
	printf("nano entry here!\r\n");
	while(1) {
		str=(char*)aos_malloc(STRBUFSIZE);
		if(str==NULL)
		{
			printf("aos_malloc fail!\r\n");
			continue;
		}
		sprintf(str, "aos_malloc running %d\r\n",count);
		printf("%s",str);
		count++;
		aos_free(str);
        aos_msleep(1000);
    };
}
