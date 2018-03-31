/* 
 * File:   main.c
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include"uart_msg.h"

int port=6789;
///////receive///////////////////////////////////////////
int parse_char(unsigned char c, rcvd_msg *msg, int *state)
{
    int ret = 0;
    static unsigned char sum = 0;
    switch(*state)
    {
        case PARSE_STATE_IDLE:
            {
                msg->hdr_index = 0;
                msg->msg_index = 0;
                sum = 0;
                if(c == MESSAGE_MAGIC1)
                {
                    msg->header[msg->hdr_index++] = c;
                    *state = PARSE_STATE_GOT_MSG_STX;
                }
            }
            break;
        case PARSE_STATE_GOT_MSG_STX:
            {
                if(c == MESSAGE_MAGIC2)
                {
                msg->header[msg->hdr_index++] = c;
                *state = PARSE_STATE_GOT_MSG_STX2;
                }
            }
            break;
        case PARSE_STATE_GOT_MSG_STX2:
            {
                msg->header[msg->hdr_index++] = c;
                *state = PARSE_STATE_GOT_SENSOR_TYPE;
            }
            break;
        case PARSE_STATE_GOT_SENSOR_TYPE:
            {
                msg->header[msg->hdr_index++] = c;
                *state = PARSE_STATE_GOT_CHECK_SUM;
            }
            break;
        case PARSE_STATE_GOT_CHECK_SUM:
            {
                msg->header[msg->hdr_index++] = c;
                if(c <= 0 || c > MSG_MAX_LEN)
                {
                    *state = PARSE_STATE_IDLE;
                }
                else
                {
                    *state = PARSE_STATE_GOT_MSG_LEN;
                }
            }
            break;
        case PARSE_STATE_GOT_MSG_LEN:
            {
                msg->msg[msg->msg_index++] = c;
                sum += c;
                if(msg->header[MSG_LEN] == msg->msg_index)
                {
                    if(sum == (unsigned char)msg->header[MSG_SUM])
                    {
                        ret=1;
                    }
                    else
                    {
                        printf("CRC checksum error! %d != %d \n",sum,(unsigned char)msg->header[MSG_SUM]);
                    }
                    *state = PARSE_STATE_IDLE;
                }

            }
            break;
        default:
            {
                *state = PARSE_STATE_IDLE;
                printf("VSENSOR parse message state error!\n");
            }
            break;
    }
    return ret;
}

int total_msg=0;
void handle_received_message(rcvd_msg *msg){
/*
    int i;
    int len=msg->header[MSG_LEN];
    total_msg+=len;
    printf("\nreceived %d  type=[%d]\n",len,msg->header[MSG_TYPE]);
    for(i=0;i<len;i++){
        printf("%x ",msg->msg[i]);
    }
    printf("\n");
*/
//do somthing 

//data fusion
//do_kalman_filter(float accX, float accY, float accZ, float magX, float magY, float magZ,
//        float GyroR, float GyroP, float GyroY);
float accX=0, accY=0, accZ=0, magX=0, magY=0, magZ=0, GyroR=0, GyroP=0, GyroY=0;
do_kalman_filter(accX, accY, accZ, magX, magY, magZ, GyroR, GyroP, GyroY);

}


///////////////////////////////////////////////////////////

int main(int argc, char** argv) {
    int sin_len;
    char buf[2000];
    rcvd_msg  msg;
    int total_rcv=0;

    int socket_descriptor;
    struct sockaddr_in sin;
    printf("Waiting for data form sender \n");

    bzero(&sin,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=htonl(INADDR_ANY);
    sin.sin_port=htons(port);
    sin_len=sizeof(sin);

    socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);
    bind(socket_descriptor,(struct sockaddr *)&sin,sizeof(sin));
    
    int rcv_state = PARSE_STATE_IDLE;
    while(1)
    {
        int nread=recvfrom(socket_descriptor,buf,sizeof(buf),0,(struct sockaddr *)&sin,&sin_len);
           printf("recv %d\n",nread);
           total_rcv+=nread;
        int i;
            for (i = 0; i < nread; i++)
            {
                if (parse_char(buf[i], &msg, &rcv_state))
                {
                    handle_received_message(&msg);
                }
            }

        if(total_rcv>200000){
            printf("total_rcv=%d total_msg=%d\n",total_rcv,total_msg);
        }
    }

    close(socket_descriptor);
    exit(0);

    return (EXIT_SUCCESS);
}
