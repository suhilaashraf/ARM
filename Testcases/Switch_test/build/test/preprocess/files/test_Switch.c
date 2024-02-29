#include "src/Switch.h"
#include "build/test/mocks/mock_gpio.h"
#include "C:/Users/ahmed/.local/share/gem/ruby/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






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

    GPIO_InitPin_CMockIgnoreAndReturn(21, Status_enumOk);

    uint8_t result = SWITCH_INIT();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Status_enumOk)), (UNITY_INT)(UNITY_INT8 )((result)), (

  ((void *)0)

  ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_INT8);

}





void test_SWITCH_GETSTATUS(void)

{

    GPIO_GetPinValue_CMockIgnoreAndReturn(29, Status_enumOk);

    uint8_t result = SWITCH_GETSTATUS(Switch_one ,&status);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Status_enumOk)), (UNITY_INT)(UNITY_INT8 )((result)), (

  ((void *)0)

  ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT8);

}



void test_SWITCH_GETSTATUS_1(void)

{

    GPIO_GetPinValue_CMockIgnoreAndReturn(36, Status_enumOk);

    uint8_t result = SWITCH_GETSTATUS(switch_three ,&status);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Status_enumParameterError)), (UNITY_INT)(UNITY_INT8 )((result)), (

  ((void *)0)

  ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT8);

}
