#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/* ***********
 * 截取帐号密码
 * ***********/
bool getNamePwd(const char *data, int len, char *name, char *pwd)
{
    int i;
    bool find_name = false,find_pwd = false;
    for (i=0; i < len; i++) {
        if (data[i] == '"' ) {
            if (!find_name && 0 == strncmp(data+(i+1),"username",8) ) {
                int j = 0;
                for (;;j++) {
                    if(data[i+14+j] == 13 || j > 49){
                        name[j]  = '\0';
                        find_name = true;
                        break;
                    }
                    name[j] = (char)data[i+14+j];

                }
                i += j;
            }

            if ( !find_pwd && 0 == strncmp(data+i+1,"password",8) ) {
                int k = 0;
                for (;;k++) {

                    if(data[i+14+k] == 13 || k > 19){
                        pwd[k] = '\0';
                        find_pwd = true;
                        break;
                    }
                    pwd[k] = data[i+14+k];
                }
                return true;
            }
        }
    }
    return false;

}

int main()
{
    //web
    size_t i = 0,n = 0;
    char *method = NULL;
    char name[50],pwd[20];

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
            getNamePwd(inputdata,length,name,pwd);
            //读出帐号密码
            free(inputdata);
        }
    }else if (getenv("QUERY_STRING") && strcmp(method,"GET") == 0){
        //环境变量的长度有限,导致GET方法传送数据被限制
        char * inputdata = getenv("QUERY_STRING");
        if (inputdata == NULL){
            printf("<p>错误：数据没有被输入或数据传输发生错误</p>");
        }else{
            printf("+len = %d++%s+++",strlen(inputdata),inputdata);
         //   sscanf(inputdata,"username=%[^&]&password=%s",name,pwd);
        }

    }else{
          printf("%s\n","bad request!");
          return 0;
    }

}
