#ifdef TEST

#include "unity.h"
#include "mock_gpio.h"
#include "Switch.h"

SWITCHCFG_str Switches [_SWITCH_NUM ];
uint32_t status ;
uint32_t switch_three =2;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_SWITCH_INIT(void)
{
    GPIO_InitPin_IgnoreAndReturn(Status_enumOk);
    uint8_t result = SWITCH_INIT();
    TEST_ASSERT_EQUAL_INT8 (Status_enumOk , result);
}

void test_SWITCH_INIT_1(void)
{
    GPIO_InitPin_IgnoreAndReturn(Status_enumParameterError);
    uint8_t result = SWITCH_INIT();
    TEST_ASSERT_EQUAL_INT8 (Status_enumParameterError, result);
}

void test_SWITCH_GETSTATUS(void)
{
    GPIO_GetPinValue_IgnoreAndReturn(Status_enumOk);
    uint8_t result = SWITCH_GETSTATUS(Switch_one ,&status);
    TEST_ASSERT_EQUAL_INT8 (Status_enumOk , result);
}

void test_SWITCH_GETSTATUS_1(void)
{
    GPIO_GetPinValue_IgnoreAndReturn(Status_enumOk);
    uint8_t result = SWITCH_GETSTATUS(switch_three ,&status);
    TEST_ASSERT_EQUAL_INT8 (Status_enumParameterError , result);
}

void test_SWITCH_GETSTATUS_2(void)
{
    GPIO_GetPinValue_IgnoreAndReturn(Status_enumParameterError);
    uint8_t result = SWITCH_GETSTATUS(Switch_one ,&status);
    TEST_ASSERT_EQUAL_INT8 (Status_enumParameterError , result);
}




#endif // TEST
