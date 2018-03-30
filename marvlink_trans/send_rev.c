#include"uart_msg.h"
#include<stdio.h>
#include<poll.h>
///////send////////////////////////////////////////////

void real_send(int fd,char *str,int len){
    write(fd,str,len);
}

void send_blk_data(int fd,int type,char *buff,int buf_len)
{
    char header[HEAD_LEN] = {0};
    unsigned char sum = 0;

    header[MSG_MGC1] = MESSAGE_MAGIC1;
    header[MSG_MGC2] = MESSAGE_MAGIC2;
    header[MSG_TYPE] = type;

    header[MSG_LEN] = buf_len;
    int i;
    for(i=0;i<buf_len;i++){
        sum = sum + (unsigned char)buff[i];
    }
    header[MSG_SUM] = sum;

    real_send(fd,header, sizeof(header));
    real_send(fd,buff, buf_len);
}





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
                        printf("CRC checksum error! %d != %d \n",sum,msg->header[MSG_SUM]);
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




///////////////////////////test//////////////////////////////////


void handle_received_message(rcvd_msg * msg)
{

}




void test_main()
{    
    struct pollfd fds[1] = {0};
    int nread = 0;
    unsigned char buf[128];
    const int timeout = 1000;
    rcvd_msg  msg;


    sleep(2);

    int _uart_fd =0;//= open_uart(VSENSOR_UART, VSENSOR_UART_BAUD_RATE);

    if (_uart_fd < 0) 
    {
        warnx("ERR open  failed.\n");
        return;
    }    


    fds[0].fd = _uart_fd;
    fds[0].events = POLLIN;
    int rcv_state = PARSE_STATE_IDLE;
    while (1) 
    {
        if (poll(&fds[0], 1, timeout) > 0) 
        {

            /* non-blocking read. read may return negative values */
            nread = read(fds[0].fd, buf, sizeof(buf));
            /* if read failed, this loop won't execute */
            int i;
            for (i = 0; i < nread; i++) 
            {
                if (parse_char(buf[i], &msg, &rcv_state)) 
                {
                    /* handle generic messages and commands */
                    handle_received_message(&msg);
                }
            }
        }
        usleep(100);
    }

    if(_uart_fd >=0)
    {
        close(_uart_fd);
    }


}
