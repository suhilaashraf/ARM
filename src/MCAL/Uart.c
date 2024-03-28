#include "Uart.h"

/**************************Uart define************************************/
#define Uart_TXE        BIT_7_MASK
#define Uart_TC         BIT_6_MASK

#define Uart_TXEIE      BIT_7_MASK

#define SR_RXNE			BIT_5_MASK			//0: Data is not received 1: Received data is ready to be read.

#define UART_TE         BIT_3_MASK
#define UART_EN         BIT_13_MASK
#define UART_Mbit       BIT_12_MASK
#define STOP_1BITMASK   0x00003000
#define CLK_FRQ         16000000
#define BAUDRATE_MASK   4
/**************************Uart TYPEDEF************************************/
typedef struct Uart
{
    uint32_t SR;
    uint32_t DR;
    uint32_t BRR;
    uint32_t CR1;
    uint32_t CR2;
    uint32_t CR3;
    uint32_t GTPR;
} Uart_t;

/***********************UART VARIABLES**************************************/

TxReq TxUserRequest;
RxReq RxUserRequest;

/**************************Uart APIs PROTOTYPES******************************/

Error_enumStatus_t Uart_Cfg(void);
Error_enumStatus_t Uart_SendByte(uint8_t Byte);
Error_enumStatus_t Uart_ReceiveByte(void);
/***********************UART APIS IMPLEMENTATION*****************************/
Error_enumStatus_t Uart_Cfg(void)
{
    Error_enumStatus_t Returnstatus = Status_enumNotOk;
    uint32_t localmask;
    if (!((TxUserRequest.UART_X == UART_1) || (TxUserRequest.UART_X == UART_2) || (TxUserRequest.UART_X == UART_6)))
    {
        Returnstatus = Status_enumParameterError;
    }
    else
    {
        Returnstatus = Status_enumOk;
        localmask = (CLK_FRQ / (8 * 2 * 9600));
        ((Uart_t *)TxUserRequest.UART_X)->BRR |= localmask << BAUDRATE_MASK;

        ((Uart_t *)TxUserRequest.UART_X)->CR1 |= UART_EN;
        ((Uart_t *)TxUserRequest.UART_X)->CR1 &= ~UART_Mbit;
        localmask = ((Uart_t *)TxUserRequest.UART_X)->CR2;
        localmask &= ~STOP_1BITMASK;
        ((Uart_t *)TxUserRequest.UART_X)->CR2 = localmask;
        ((Uart_t *)TxUserRequest.UART_X)->CR1 |= UART_TE;
#if UART_BY == UART_INT
        ((Uart_t *)TxUserRequest.UART_X)->CR1 |= Uart_TXEIE;
#endif
    }
    return Returnstatus;
}

Error_enumStatus_t Uart_SendByte(uint8_t Byte)
{
    Error_enumStatus_t Returnstatus = Status_enumNotOk;
    if (((Uart_t *)TxUserRequest.UART_X)->SR & Uart_TXE)
    {
        ((Uart_t *)TxUserRequest.UART_X)->CR1 |= UART_TE;
        ((Uart_t *)TxUserRequest.UART_X)->DR = Byte;
        TxUserRequest.buffer.pos++;

        Returnstatus = Status_enumOk;
    }
    return Returnstatus;
}

Error_enumStatus_t Uart_ReceiveByte(void)
{
    Error_enumStatus_t Returnstatus = Status_enumNotOk;
    if (((Uart_t *)RxUserRequest.UART_X)->SR & SR_RXNE)
    {
        RxUserRequest.buffer.data[RxUserRequest.buffer.pos]= ((Uart_t *)TxUserRequest.UART_X)->DR ;
        RxUserRequest.buffer.pos++;

        Returnstatus = Status_enumOk;
    }
    return Returnstatus;
}



Error_enumStatus_t Uart_TxBufferAsync(uint8_t *buffer, uint32_t len, void *UART_x)
{
    Error_enumStatus_t Returnstatus = Status_enumNotOk;
    if (TxUserRequest.state == Ready)
    {
        TxUserRequest.state = Busy;
        TxUserRequest.buffer.size = len;
        TxUserRequest.UART_X = UART_x;
        TxUserRequest.buffer.data = buffer;
        Uart_Cfg();
        ((Uart_t *)TxUserRequest.UART_X)->CR1 |= UART_TE;
        Uart_SendByte(TxUserRequest.buffer.data[TxUserRequest.buffer.pos]);

        Returnstatus = Status_enumOk;
    }
    return Returnstatus;
}

Error_enumStatus_t Uart_RxBufferAsync(uint8_t *buffer, uint32_t len, void *UART_x)
{
    Error_enumStatus_t Returnstatus = Status_enumNotOk;
    if (RxUserRequest.state == Ready)
    {
        RxUserRequest.buffer.size = len;
        RxUserRequest.state = Busy;
        RxUserRequest.UART_X = UART_x;
        RxUserRequest.buffer.data = buffer;
        Returnstatus = Status_enumOk;
    }
    return Returnstatus;
}


void USART1_IRQHandler(void)
{
    if (TxUserRequest.state == Busy)
    {
        if (((Uart_t *)TxUserRequest.UART_X)->SR & Uart_TXE)
        {
            if (TxUserRequest.buffer.pos < TxUserRequest.buffer.size)
            {
                ((Uart_t *)TxUserRequest.UART_X)->DR = TxUserRequest.buffer.data[TxUserRequest.buffer.pos];
                TxUserRequest.buffer.pos++;            
            }
            else
            {
                TxUserRequest.state = Ready;
            }
        }
    }
    if (RxUserRequest.state == Busy)
    {
        if (((Uart_t *)RxUserRequest.UART_X)->SR & SR_RXNE)
        {
            if (RxUserRequest.buffer.pos < RxUserRequest.buffer.size)
            {
                RxUserRequest.buffer.data[TxUserRequest.buffer.pos] =((Uart_t *)RxUserRequest.UART_X)->DR ;
                RxUserRequest.buffer.pos++;            
            }
            else
            {
                RxUserRequest.state = Ready;
            }
        }
    }
}

Error_enumStatus_t UartTx_done(void)
{
    Error_enumStatus_t Returnstatus = Status_enumNotOk;
    if (((Uart_t *)TxUserRequest.UART_X)->SR & Uart_TC)
    {
        Returnstatus = Status_enumOk;
    }
    return Returnstatus;
}
/*
void USART2_IRQHandler(void)
{

}

void USART6_IRQHandler(void)
{
}
*/