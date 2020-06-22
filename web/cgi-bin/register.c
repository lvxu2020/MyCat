#include <stdio.h>
#include <sqlite3.h>
#define USER_DB_PATH "../sqlite/user.db"

bool found = false;

/* ***********
 * 查找特定元素
 * ***********/
int find(void *para,int ncolumn, char ** columnvalue,char *columnname[]){
    int i;
    for(i = 0; i < ncolumn; i++){
        if(strcmp(columnname[i],(char*)para) == 0){
            found = true;
        }
    }
    return 0;
}
int main(int argc, char* argv[])
{
    //web
    size_t i = 0,n = 0;
    char * method = NULL;
    char name[50],pwd[20];
    //获取HTTP请求方法(POST/GET)
    if(NULL == (method = getenv("REQUEST_METHOD")))
    {
        return 0;
    }
    //POST 方法解析,从 STDIN_FILENO 动态获取数据
    if (getenv("CONTENT_LENGTH") && strcmp(method,"POST") == 0){
        n = atoi(getenv("CONTENT_LENGTH"));
        size_t length = n * sizeof(char) + 1;
        char * inputdata = (char *)malloc(length);
        if(inputdata){
            memset((void*)inputdata,0,length);
            if(n != read(STDIN_FILENO,inputdata,n)){

            }
            //读出帐号密码
            free(inputdata);
        }
    }else if (getenv("QUERY_STRING") && strcmp(method,"GET") == 0){
        //环境变量的长度有限,导致GET方法传送数据被限制
        char * inputdata = getenv("QUERY_STRING");
        if (inputdata == NULL){
            printf("<p>错误：数据没有被输入或数据传输发生错误</p>");
        }else{
            sscanf(date,"username=%[^&]&password=%s",name,pwd);
        }

    }else{
          printf("%s\n","bad request!");
          return 0;
    }




    //数据库
    sqlite3 *db;/*句柄*/
    int res;
    char *errmsg = NULL;
    char **result;
    int row,col;
    int i;
    const char *sqlcmd;

   //校验数据库中，是否重名
    sqlcmd = "SELECT * FROM USER_PASS";
    res = sqlite3_exec(db,sqlcmd,display,(void*)find,&errmsg);//查询数据
    if(res!=SQLITE_OK){
        printf("数据库操作失败：%d-%s\n",res,errmsg);
        sqlite3_close(db);
        return 0;
    }
    if(found){

    }else{//添加进数据库

    }


   sqlite3_close(db);
}
