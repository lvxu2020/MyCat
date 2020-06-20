#include<stdio.h> 
#include<stdlib.h>
#include <string.h>  
int main() 
{   
    char *date;   
    char name[50],pwd[20];   
    printf("content-type:text/html;charset=utf-8\n\n");  
    printf("<TITLE>登陆结果</TITLE>");
//   printf("<H3>登陆结果</h3>");  
    printf( "<script>function show(){var date =new Date(); var now = \"\"; now = date.getFullYear()+\"年\"; now = now + (date.getMonth()+1)+\"月\"; \ now = now + date.getDate()+\"日\"; now = now + date.getHours()+\"时\"; now = now + date.getMinutes()+\"分\";now = now + date.getSeconds()+\"秒\"; document.getElementById(\"nowDiv\").innerHTML = now; setTimeout(\"show()\",1000);} </script> \n ");	
    date=getenv("QUERY_STRING");
  printf( "<h2><font face=\"Broadway\"><font color=\"#00FAF0\">Home1 Real-time Environment Info:</font></font></H2>\n ");
		printf( "<h2 align=center><font color=\"#cc0033\"><body onload=\"show()\"> <div id=\"nowDiv\"></div></font></h2> \n ");   
    if(date==NULL)    
        printf("<p>错误：数据没有被输入或数据传输发生错误</p>");  
    else
    {    
        sscanf(date,"name=%[^&]&pwd=%s",name,pwd);  
	if(strcmp(name,"lvxu")){
	    printf("<H3>deng lu shi bai</h3>");  	
	}else{
	    printf("<H3>success!</h3>");
	    printf("<meta http-equiv=\"Refresh\" content=\"3;URL=/a.html\">");
	}
        printf("<p>name=%s</p>",name);   
        printf("<p>pwd=%s</p>",pwd);   
        printf("%s",date);  
    }   
    return 0; 
}
