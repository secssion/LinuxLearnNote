/*************************************************************************
	> File Name: test.c
	> Description: test.c
	> Author: lkong
	> Mail: lkong@tencent.com 
	> Created Time: 2019-09-26 09:45:35
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include "testlib.h"

void fun_test()
{
    char str[100] = {0};
    char* p = NULL;
    my_strcpy(str, "ni hao", 7);
}

int main()
{
    fun_test();
    return 0;
}
