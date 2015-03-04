#include <stdio.h>
#include </home/hunk/桌面/service/proc.h>
#include </home/hunk/桌面/service/math.h>

/////生成公钥,g,p,y
void creatKey()
{
	p=createp();
	a=rand()+MINa;
	g=rand()%100;
	if(g<0)	g+=100;
	y=mod(g,a,p);
}

/////解密
void decode(int c1,int c2)
{
	long long x,y,d;
	c1=mod(c1,a,p);
    extgcd(c1,p,&d,&x,&y);
    while(x<0)	x+=p;
    printf("%c\n",(c2*x)%p);
    if((char)((c2*x)%p)=='\n')
    	printf("messages: ");
}

/////发布公钥
void sendPK(int sockfd)
{
	char  str[100];
	convertChar(y,str);
	send(sockfd,str,sizeof(str),0);
	convertChar(p,str);
	send(sockfd,str,sizeof(str),0);
	convertChar(g,str);
	send(sockfd,str,sizeof(str),0);
}

void getmsg(int sockfd)
{
	char str[100];
	long long c1,c2;
	recv(sockfd,str,sizeof(str),0);
    c1=convertNum(str);
    recv(sockfd,str,sizeof(str),0);
    c2=convertNum(str);
    decode(c1,c2);
}
