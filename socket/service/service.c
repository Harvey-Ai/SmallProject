#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include </home/hunk/桌面/service/math.h>
#include </home/hunk/桌面/service/proc.h>

int main()
{
        creatKey();
        ////公布公钥,服务器端
        int sockfd,newfd;/////有两个进程,监听进程，服务进程
        struct sockaddr_in servaddr;
        
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=0;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        
        ////打印端口号
        printf("socket port #%d\n",ntohs(servaddr.sin_port));
        
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
        	perror("socket() error!\n");
            exit(1);
        }
        if(bind(sockfd,(struct sockaddr *)(&servaddr),sizeof(servaddr))==-1)//////绑定socket和sockaddr
        {
        	perror("bind() error\n");
            exit(1);
        }
        if(listen(sockfd,10)==-1)///////设置监听数
        {
        	perror("listen() error!\n");
        	exit(1);
        }
        
        /////接受，直到有请求
        while(1)
        {
        	newfd=accept(sockfd,(struct sockaddr *)NULL,NULL);
        	if(!fork())
        	{
        		///////发布公钥
        		printf("公钥：%lld %lld %lld\n",y,p,g);
        		
        		printf("messages: ");
        		while(1)
        		{
        			int newwfd;
        			newwfd=accept(sockfd,(struct sockaddr *)NULL,NULL);
            		getmsg(newfd);
        		}
        	}
        	close(newfd);
        }
        close(sockfd);
        return 0;
}
