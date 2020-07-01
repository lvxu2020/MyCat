#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define COMMAND_MAX 1

int main()
{
//    printf("content-type:text/html;charset=utf-8\n\n");
//    printf("hello world");
 //   printf("<meta http-equiv=\"Refresh\" content=\"5;URL=/status.html\">");


    //web
    size_t i = 0,n = 0;
    char *method = NULL;
    char command[COMMAND_MAX][50] = {0};
    char num[10] = {0};
    //获取HTTP请求方法(POST/GET)
    if (NULL == (method = getenv("REQUEST_METHOD")))
    {
        return 0;
    }
    printf("content-type:text/html;charset=utf-8\n\n");
    printf("<TITLE>注册结果</TITLE>");
    //POST 方法解析,从 STDIN_FILENO 动态获取数据
    if (getenv("CONTENT_LENGTH") && strcmp(method,"POST") == 0){
        n = atoi(getenv("CONTENT_LENGTH"));
        size_t length = n * sizeof(char) + 1;
        //必须申请缓存，因为stdin是不带缓存的。
        char * inputdata = (char *)malloc(length);
        if(inputdata){
            memset((void*)inputdata,0,length);
            //从标准输入读取一定数据
            fread(inputdata, sizeof(char), length, stdin);

            free(inputdata);
        }
    }else if (getenv("QUERY_STRING") && strcmp(method,"GET") == 0){
        //环境变量的长度有限,导致GET方法传送数据被限制
        char * inputdata = getenv("QUERY_STRING");
        if (inputdata == NULL){
            printf("<p>错误：数据没有被输入或数据传输发生错误</p>");
        }else{
            int length = strlen(inputdata);
            sscanf(inputdata,"num=%s",num);
            printf("+lvxulen = %d++%s+++",strlen(inputdata),inputdata);

        }

    }else{
          printf("%s\n","bad request!");
          return 0;
    }
    printf("<meta http-equiv=\"Refresh\" content=\"6;URL=/status.html?num=%s\">",num);
}
