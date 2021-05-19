#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

#define BUF_SIZE 30

void error_handler(const char* message);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    int clnt_addr_sz;
    
    char buf[BUF_SIZE];
    int str_len;
    
    fd_set rd_set,temp_set;
    int fd_max;
    struct timeval timeout;
    int fd_num,i;

    if(argc!=2)
    {
        printf("Usage %s <port>",argv[0]);
        exit(1);
    }

    serv_sock=socket(AF_INET,SOCK_STREAM,0);
    if(serv_sock==-1)
            error_handler("socket error");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
            error_handler("bind error");

    if(listen(serv_sock,5)==-1)
            error_handler("listen error");

    FD_ZERO(&rd_set);
    FD_SET(serv_sock,&rd_set);
    fd_max=serv_sock;

    while(1)
    {
        temp_set=rd_set;
        timeout.tv_sec=5;
        timeout.tv_usec=0;

        fd_num=select(fd_max+1,&temp_set,NULL,NULL,&timeout);
        if(fd_num==-1) 
                error_handler("select error");
        if(fd_num==0)
                continue;

        for(i=0;i<fd_max+1;i++)
        {
            if(FD_ISSET(i,&temp_set))
            {
                if(i==serv_sock)
                {
                    clnt_addr_sz=sizeof(clnt_addr);
                    clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_sz);
                    FD_SET(clnt_sock,&rd_set);
                    if(fd_max<clnt_sock)
                            fd_max=clnt_sock;
                    printf("client %d connected\n",clnt_sock);
                }
                else
                {
                    str_len=read(i,buf,BUF_SIZE);
                    if(str_len<=0)
                    {
                        FD_CLR(i,&rd_set);
                        close(i);
                        printf("client %d disconnected",clnt_sock);
                    }
                    else
                    {
                        write(i,buf,str_len);
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}

void error_handler(const char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}