#include <stdio.h>
#include <stdint.h>
#include <aos/kernel.h>
#include "cjson.h"

int application_start(int argc, char *argv[])
{
    cJSON* cjson_test = NULL;
	cJSON* cjson_address = NULL;
	cJSON* cjson_skill = NULL;
	char* str = NULL;
	printf("nano entry here!\r\n");
	/* 创建一个JSON数据对象(链表头结点) */
	cjson_test = cJSON_CreateObject();
	/* 添加一条字符串类型的JSON数据(添加一个链表节点) */
	cJSON_AddStringToObject(cjson_test, "name", "mculover666");
	/* 添加一条整数类型的JSON数据(添加一个链表节点) */
	cJSON_AddNumberToObject(cjson_test, "age", 22);
	/* 添加一条浮点类型的JSON数据(添加一个链表节点) */
	cJSON_AddNumberToObject(cjson_test, "weight", 55.5);
    cjson_address = cJSON_CreateObject();
    cJSON_AddStringToObject(cjson_address, "country", "China");
    cJSON_AddNumberToObject(cjson_address, "zip-code", 111111);
    cJSON_AddItemToObject(cjson_test, "address", cjson_address);
    /* 添加一个数组类型的JSON数据(添加一个链表节点) */
    cjson_skill = cJSON_CreateArray();
    cJSON_AddItemToArray(cjson_skill, cJSON_CreateString( "C" ));
    cJSON_AddItemToArray(cjson_skill, cJSON_CreateString( "Java" ));
    cJSON_AddItemToArray(cjson_skill, cJSON_CreateString( "Python" ));
    cJSON_AddItemToObject(cjson_test, "skill", cjson_skill);
    /* 添加一个值为 False 的布尔类型的JSON数据(添加一个链表节点) */
    cJSON_AddFalseToObject(cjson_test, "student");
    /* 打印JSON对象(整条链表)的所有数据 */
    str = cJSON_Print(cjson_test);
    printf("%s\n", str);
    while(1) {
        aos_msleep(1000);
    };
}
