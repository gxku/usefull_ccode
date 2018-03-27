#include<stdio.h>
#include"uart_msg.h"
int main(int argc, char *argv[])
{
    int fd;
    int nread,i;
    char buf[200];
    rcvd_msg  msg;

    if(argc<2)
    {
        perror("Usage: test /dev/ttyX");
        return;
    }
    if((fd=open_port(argv[1]))<0)
    {
        perror("open_port error");
        return;
    }
    if((i=set_opt(fd,9600,8,'N',1))<0)
    {
        perror("set_opt error");
        return;
    }
    printf("fd=%d\n",fd);
    int rcv_state = PARSE_STATE_IDLE;
    while (1)
    {

            send_blk_data(fd,1,argv[2],10);
            /* non-blocking read. read may return negative values */
            nread = read(fd, buf, sizeof(buf));
            /* if read failed, this loop won't execute */
            int i;
            for (i = 0; i < nread; i++)
            {
                if (parse_char(buf[i], &msg, &rcv_state))
                {
                    /* handle generic messages and commands */
                    printf("\ngot one:\n");
                    int j;
                    for(j=0;j<10;j++){
                        printf("%c ",msg.msg[j]);
                    }
                   // handle_received_message(&msg);
                }
            }
        sleep(1);
    }

    close(fd);
    return;
}

