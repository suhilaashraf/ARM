#include "src/led.h"
#include "build/test/mocks/mock_gpio.h"
#include "C:/Users/ahmed/.local/share/gem/ruby/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








LedCfg_str Ledcfg [_LEDNUM];



int Led_three = 2;



void setUp(void)

{



}



void tearDown(void)

{



}





void test_LEDinit(void)

{

    GPIO_InitPin_CMockIgnoreAndReturn(25, Status_enumOk);

    uint8_t result = LED_init ();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Status_enumOk)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT8);

}



void test_LEDSetStatus_0(void)

{

    GPIO_SetPinValue_CMockIgnoreAndReturn(32, Status_enumOk);

    uint8_t result = Led_SetStatus(Led_one,0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Status_enumOk)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT8);

}





void test_LEDSetStatus_1(void)

{

    GPIO_SetPinValue_CMockIgnoreAndReturn(40, Status_enumOk);

    uint8_t result = Led_SetStatus(Led_one,1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Status_enumOk)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_INT8);

}





void test_LEDSetStatus_2(void)

{

    GPIO_SetPinValue_CMockIgnoreAndReturn(48, Status_enumOk);

    uint8_t result = Led_SetStatus(Led_three,1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Status_enumParameterError)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT8);

}





void test_LEDSetStatus_3(void)

{

    GPIO_SetPinValue_CMockIgnoreAndReturn(56, Status_enumOk);

    uint8_t result = Led_SetStatus(Led_one,2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Status_enumParameterError)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT8);

}
