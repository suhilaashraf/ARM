#include "Uart.h"
#include "RCC.h"

#define TXE BIT_7_MASK

/**************************VARIABLES******************************/

extern TxReq TxUserRequest;
extern RxReq RxUserRequest;

extern Error_enumStatus_t Uart_SendByte(uint8_t Byte);

/***********************IMPLEMENTATION*****************************/

void Uart_TxBuffer(void)
{
    if (TxUserRequest.state == Busy)
    {
        if (TxUserRequest.buffer.pos < TxUserRequest.buffer.size)
        {
            Uart_SendByte(TxUserRequest.buffer.data[TxUserRequest.buffer.pos]);
        }
        else
        {
            if (!(UartTx_done()))
            {
                TxUserRequest.state = Ready;
            }
        }
    }
}

void Uart_Rxbuffer(void)
{
        if (RxUserRequest.buffer.pos < RxUserRequest.buffer.size)
        {
            Uart_ReceiveByte();
        }
        else
        {
            RxUserRequest.state = Ready;   
        }
}
