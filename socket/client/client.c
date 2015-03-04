#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include </home/hunk/桌面/client/proc.h>

#define Port1 27012//////服务端口号
#define Port2 1234//////服务端口号
//#define Ip "59.72.9.95"///////服务ip地址


int main(int argc,char **argv)
{
        ////请求公钥
        int sockfdg,sockfds;
        //////主机IP--hp
        char hostent *hp;
        struct sockaddr_in servaddr;
        /////生成socket嵌套字
        if((sockfdg=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
                perror("socket() error!\n");
                exit(1);
        }
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(atoi(argv[2]));
        printf("%s %s\n",argv[1],argv[2]);
        /////查找主机IP
        if((hp=gethostbyname(argv[1]))==NULL)
        {
        	perror("unknown host\n");
        	exit(1);
        }
        printf("aa");
        /////填入IP
        ///*
        if((servaddr.sin_addr.s_addr=inet_addr(hp))==-1)
        {
        	printf("fdsa\n");
                perror("inet_addr error");
                exit(1);
        }
        //*/
         printf("aa\n");
        /////连接
        if(connect(sockfdg,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
        {
                perror("connect error");
                exit(1);
        }
        //////取得公钥
        getPK(sockfdg);
        close(sockfdg);
        
        if((sockfds=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
                perror("socket() error!\n");
                exit(1);
        }
        /////连接
        if(connect(sockfds,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
        {
                perror("connect error");
                exit(1);
        }
        //////发送消息
        sendmsgg(sockfds);
        close(sockfds);
        
        printf("finished\n");
        return 0;
}        
