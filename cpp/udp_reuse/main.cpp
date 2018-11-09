//socket udp 服务端
#include <iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    //创建socket对象
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);

    int val =1;
    /*set SO_REUSEPORT*/
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val))<0) {
        perror("setsockopt()");         
    } 

    std::cout << "SO_REUSEADDR:" << SO_REUSEADDR << std::endl;

    //创建网络通信对象
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(7779);
    addr.sin_addr.s_addr=inet_addr("0.0.0.0");

    //绑定socket对象与通信链接
    int ret =bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(0>ret)
    {
        printf("bind\n");
        return -1;

    }
    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);

    while(true)
    {
        char buf =0;
        recvfrom(sockfd,&buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
        printf("recv num =%hhd\n",buf);

        buf =66;
        sendto(sockfd,&buf,sizeof(buf),0,(struct sockaddr*)&cli,len);

    }
    close(sockfd);
}

