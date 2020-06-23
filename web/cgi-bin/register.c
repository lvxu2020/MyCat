#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

#define TABLE "USER_PASS"
#define USER_DB_PATH "/home/lvxu/net/ku1.db"
#include <stdbool.h>

bool found = false;

/* ***********
 * 查找特定元素
 * ***********/
int find(void *para,int ncolumn, char ** columnvalue,char *columnname[])
{
    int i;
    for(i = 0; i < ncolumn; i++){
        if(strcmp(columnvalue[i],(char*)para) == 0){
            found = true;
        }
    }
    return 0;
}

/* ***********
 * 用户名已被注册
 * ***********/
void usrRegistered()
{
//    printf("content-type:text/html;charset=utf-8\n\n");
//    printf("<TITLE>登陆结果</TITLE>");
    printf("<H3>用户名已被注册！</h3>");
    printf("<meta http-equiv=\"Refresh\" content=\"5;URL=/register.html\">");
}

/* ***********
 * 新用户添加
 * ***********/
void newUsr(char *name,char *pwd)
{
    printf("<H3>注册成功，稍候返回登录界面</h3>");
    printf("<meta http-equiv=\"Refresh\" content=\"5;URL=/main.html\">");
}

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

int main(int argc, char* argv[])
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
         //   sscanf(inputdata,"username=%[^&]&password=%s",name,pwd);
        }

    }else{
          printf("%s\n","bad request!");
          return 0;
    }




    //数据库
    sqlite3 *db;
    int res;
    char *errmsg = NULL;
    char **result;
    int row,col;
    const char *sqlcmd;
    char insert[128];

    //打开数据库
    res = sqlite3_open(USER_DB_PATH, &db);
    if(res != SQLITE_OK){
        printf( "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    //校验数据库中，是否重名
    sqlcmd = "SELECT * FROM USER_PASS";
    res = sqlite3_exec(db,sqlcmd,find,(void*)name,&errmsg);//查询数据
    if(res!=SQLITE_OK){
        printf("数据库操作失败：%d-%s\n",res,errmsg);
        sqlite3_close(db);
        return 0;
    }

    if(found){
        usrRegistered();
    }else{//添加进数据库
        memset((void*)insert,0,sizeof(insert));
        sprintf(insert,"INSERT INTO %s VALUES ('%s','%s') ;",TABLE,name,pwd);
        sqlcmd = insert;
        res = sqlite3_exec(db,sqlcmd,NULL,0,&errmsg);//插入数据
        if(res!=SQLITE_OK){
            printf("数据库操作失败：%d-%s\n",res,errmsg);
            sqlite3_close(db);
            return 0;
        }else{
            newUsr(name,pwd);
        }

    }

   sqlite3_close(db);

}
