/*************************************************************************
	> File Name: testlib.c
	> Description: testlib.c
	> Author: lkong
	> Mail: lkong@tencent.com 
	> Created Time: 2019-09-26 09:48:25
 ************************************************************************/
#include <assert.h>

char* my_strcpy(char* src, char* dest, int size)
{
    assert(src && dest);
    assert(size > 0 && size < 2147483647);

    int i = 0;
    for(i=0; i<size; i++)
    {
        src[i] = dest[i];
    }
    return src;
}
