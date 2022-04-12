#define _CRT_SECURE_NO_WARNINGS 1
#include "serial.h"
#include <windows.h>
#include <stdio.h>

int main()
{
    PORT COM_epuck;
    PORT COM_fpga;
    char buff[1024] = { 0 };
    char fpga_com = 15;
    char epuck_com = 19;
   

    printf("Please input fpga's serial port number:");
    scanf("%d", &fpga_com);
    COM_fpga = serial_init(fpga_com, 115200, 8, 1, 0);
    printf("Please input epuck's serial port number:");
    scanf("%d", &epuck_com);
    COM_epuck = serial_init(epuck_com, 115200, 8, 1, 0);
    

    for(;;)
    {

        if (Serial_ReciveData(COM_fpga, buff, 4) >= 1)
        {
            Serial_SendData(COM_epuck, buff, 4);
            printf("left_speed:%d   right_speed:%d\n", buff[1] * 256 + buff[0], buff[3] * 256 + buff[2]);
            memset(buff, 0, 1024);
        }

        if (Serial_ReciveData(COM_epuck, buff, 12) >= 1)
        {
            Serial_SendData(COM_fpga, buff, 12);
            printf("IR0:%d  IR1:%d  IR2:%d  IR5:%d  IR6:%d  IR7:%d  ", buff[1] * 256 + buff[0], buff[3] * 256 + buff[2], buff[5] * 256 + buff[4], buff[7] * 256 + buff[6], buff[9] * 256 + buff[8], buff[11] * 256 + buff[10]);
            memset(buff, 0, 1024);
        }
        Sleep(1);
    }
    return 0;
}
