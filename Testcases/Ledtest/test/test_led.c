#ifdef TEST

//#include <stddef.h>
#include "unity.h"
#include "mock_gpio.h"
#include "led.h"

LedCfg_str Ledcfg [_LEDNUM];

int Led_three = 2;

void setUp(void)
{

}

void tearDown(void)
{

}


void test_LEDinit_1(void)
{
    GPIO_InitPin_IgnoreAndReturn(Status_enumParameterError);
    uint8_t result = LED_init ();
    TEST_ASSERT_EQUAL_INT8(Status_enumParameterError ,result);
}

void test_LEDinit(void)
{
    GPIO_InitPin_IgnoreAndReturn(Status_enumOk );
    uint8_t result = LED_init ();
    TEST_ASSERT_EQUAL_INT8(Status_enumOk ,result);
}

void test_LEDSetStatus_0(void)
{
    GPIO_SetPinValue_IgnoreAndReturn(Status_enumOk );
    uint8_t result = Led_SetStatus(Led_one,LED_OFF);
    TEST_ASSERT_EQUAL_INT8(Status_enumOk ,result);
}

/*Test Case 1 for LED_SetStatus*/
void test_LEDSetStatus_1(void)
{
    GPIO_SetPinValue_IgnoreAndReturn(Status_enumOk );
    uint8_t result = Led_SetStatus(Led_one,LED_ON);
    TEST_ASSERT_EQUAL_INT8(Status_enumOk ,result);
}


void test_LEDSetStatus_2(void)
{
    GPIO_SetPinValue_IgnoreAndReturn(Status_enumOk );
    uint8_t result = Led_SetStatus(Led_three,LED_ON); // wrong input 
    TEST_ASSERT_EQUAL_INT8(Status_enumParameterError ,result);
}


void test_LEDSetStatus_3(void)
{
    GPIO_SetPinValue_IgnoreAndReturn(Status_enumOk );
    uint8_t result = Led_SetStatus(Led_one,2); // wrong set value
    TEST_ASSERT_EQUAL_INT8(Status_enumParameterError ,result);
}

void test_LEDSetStatus_4(void)
{
    GPIO_SetPinValue_IgnoreAndReturn(Status_enumParameterError);
    uint8_t result = Led_SetStatus(Led_one,LED_ON); // wrong set value
    TEST_ASSERT_EQUAL_INT8(Status_enumParameterError ,result);
}


#endif // TEST
