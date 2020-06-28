#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    printf("content-type:text/html;charset=utf-8\n\n");
    printf("hello world");
    printf("<meta http-equiv=\"Refresh\" content=\"5;URL=/status.html\">");
}
