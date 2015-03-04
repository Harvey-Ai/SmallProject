#include <stdio.h>
#include </home/hunk/桌面/client/convert.h>
//////将num转换为*p，p[0]为低端
void convertChar(long long num,char *p)
{
        int i;
        for(i=0;num;i++)
        {
                p[i]=num%10+'0';
                num/=10;
        }
        p[i]='\0';
}
//////将*p转换为long long，p[0]为低端
long long convertNum(char *p)
{
        int i;
        long long res=0,quan=1;
        for(i=0;p[i]!='\0';i++)
        {
                res+=(p[i]-'0')*quan;
                quan*=10;
        }
        return res;
}
