#include <stdio.h>
#include <string.h>
#include <aos/kernel.h>
#include "aos/hal/uart.h"

uart_dev_t uart0;
int application_start(int argc, char *argv[])
{
    int count = 0;
	uint32_t ret;
	char SendBuf[]="hello uart\r\n";
    printf("nano entry here!\r\n");
	//uart0 setting
	memset(&uart0, 0, sizeof(uart0));
    uart0.port = 0;
    uart0.config.baud_rate = 115200;
    uart0.config.data_width = DATA_WIDTH_8BIT;
    uart0.config.flow_control = FLOW_CONTROL_DISABLED;
    uart0.config.mode = MODE_TX_RX;
    uart0.config.parity = NO_PARITY;
    uart0.config.stop_bits = STOP_BITS_1;
    ret = hal_uart_init(&uart0);
    if (ret != 0) {
        return -1;
    }

    while(1) {
        printf("hello world! count %d \r\n", count++);
		hal_uart_send(&uart0,SendBuf,sizeof(SendBuf),HAL_WAIT_FOREVER);
        aos_msleep(1000);
    };
}
