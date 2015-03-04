#include <stdio.h>
#include </home/hunk/桌面/client/proc.h>
#include </home/hunk/桌面/client/math.h>
#include </home/hunk/桌面/client/convert.h>

////加密
void encode(int m)
{
	///////随机数k
	long long k;
	k=rand()+MINk;
	while(gcd(k,p-1)!=1)       k++;
    c1=mod(g,k,p);
    c2=mod(y,k,p);
    c2*=m;
    c2%=p;
    printf("密文:%lld %lld\n",c1,c2);
}

/////取得公钥
void getPK(int sockfd)
{
	char str[100];
	recv(sockfd,str,sizeof(str),0);
	y=convertNum(str);
    recv(sockfd,str,sizeof(str),0);
    p=convertNum(str);
    recv(sockfd,str,sizeof(str),0);
    g=convertNum(str);
}

//////发送消息
void sendmsgg(int sockfd)
{
	char str[100],msg[100];
	int i;
	////发送消息
	while(1)
	{
		printf("Enter send message:");
		scanf("%s",msg);
		///////发送加密消息
		for(i=0;msg[i]!='\0';i++)
		{
			encode(msg[i]);
			convertChar(c1,str);
			send(sockfd,str,sizeof(str),0);
			convertChar(c2,str);
			send(sockfd,str,sizeof(str),0);
        }
        ///////发送'\n'
        encode('\n');
        convertChar(c1,str);
        send(sockfd,str,sizeof(str),0);
        convertChar(c2,str);
        send(sockfd,str,sizeof(str),0);
	}
}
