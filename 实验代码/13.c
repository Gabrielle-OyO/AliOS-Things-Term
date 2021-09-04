/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdint.h>
#include <aos/kernel.h>
#include "aos/cli.h"

void MyCmd1(char *buf, int32_t len, int32_t argc, char **argv)
{
	printf("time: %lld ms\r\n",aos_now_ms());
}
//添加命令
const struct cli_command cmd = {"gettimenow", "get time unit ms", MyCmd1};

int application_start(int argc, char *argv[])
{
    int count = 0;
    printf("nano entry here!\r\n");
	aos_cli_register_command(&cmd);//注册命令

    while(1) {
        printf("hello world! count %d \r\n", count++);
        aos_msleep(1000);
    };
}
