/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_gpio.h"

static const char* CMockString_GPIO_GetPinValue = "GPIO_GetPinValue";
static const char* CMockString_GPIO_InitPin = "GPIO_InitPin";
static const char* CMockString_GPIO_SetPinValue = "GPIO_SetPinValue";
static const char* CMockString_PORT = "PORT";
static const char* CMockString_gpio_pinNumber = "gpio_pinNumber";
static const char* CMockString_gpiopin = "gpiopin";
static const char* CMockString_gpiopinStatus = "gpiopinStatus";

typedef struct _CMOCK_GPIO_InitPin_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  Error_enumStatus_t ReturnVal;
  int CallOrder;
  GPIOPIN_t* Expected_gpiopin;

} CMOCK_GPIO_InitPin_CALL_INSTANCE;

typedef struct _CMOCK_GPIO_SetPinValue_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  Error_enumStatus_t ReturnVal;
  int CallOrder;
  void* Expected_PORT;
  uint32_t Expected_gpio_pinNumber;
  uint32_t Expected_gpiopinStatus;

} CMOCK_GPIO_SetPinValue_CALL_INSTANCE;

typedef struct _CMOCK_GPIO_GetPinValue_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  Error_enumStatus_t ReturnVal;
  int CallOrder;
  void* Expected_PORT;
  uint32_t Expected_gpio_pinNumber;
  uint32_t* Expected_gpiopinStatus;

} CMOCK_GPIO_GetPinValue_CALL_INSTANCE;

static struct mock_gpioInstance
{
  char GPIO_InitPin_IgnoreBool;
  Error_enumStatus_t GPIO_InitPin_FinalReturn;
  char GPIO_InitPin_CallbackBool;
  CMOCK_GPIO_InitPin_CALLBACK GPIO_InitPin_CallbackFunctionPointer;
  int GPIO_InitPin_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE GPIO_InitPin_CallInstance;
  char GPIO_SetPinValue_IgnoreBool;
  Error_enumStatus_t GPIO_SetPinValue_FinalReturn;
  char GPIO_SetPinValue_CallbackBool;
  CMOCK_GPIO_SetPinValue_CALLBACK GPIO_SetPinValue_CallbackFunctionPointer;
  int GPIO_SetPinValue_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE GPIO_SetPinValue_CallInstance;
  char GPIO_GetPinValue_IgnoreBool;
  Error_enumStatus_t GPIO_GetPinValue_FinalReturn;
  char GPIO_GetPinValue_CallbackBool;
  CMOCK_GPIO_GetPinValue_CALLBACK GPIO_GetPinValue_CallbackFunctionPointer;
  int GPIO_GetPinValue_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE GPIO_GetPinValue_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_gpio_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.GPIO_InitPin_CallInstance;
  if (Mock.GPIO_InitPin_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_GPIO_InitPin);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.GPIO_InitPin_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.GPIO_SetPinValue_CallInstance;
  if (Mock.GPIO_SetPinValue_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_GPIO_SetPinValue);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.GPIO_SetPinValue_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.GPIO_GetPinValue_CallInstance;
  if (Mock.GPIO_GetPinValue_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_GPIO_GetPinValue);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.GPIO_GetPinValue_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
}

void mock_gpio_Init(void)
{
  mock_gpio_Destroy();
}

void mock_gpio_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

Error_enumStatus_t GPIO_InitPin(GPIOPIN_t* gpiopin)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_GPIO_InitPin_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_GPIO_InitPin);
  cmock_call_instance = (CMOCK_GPIO_InitPin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.GPIO_InitPin_CallInstance);
  Mock.GPIO_InitPin_CallInstance = CMock_Guts_MemNext(Mock.GPIO_InitPin_CallInstance);
  if (Mock.GPIO_InitPin_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.GPIO_InitPin_FinalReturn;
    memcpy((void*)(&Mock.GPIO_InitPin_FinalReturn), (void*)(&cmock_call_instance->ReturnVal),
         sizeof(Error_enumStatus_t[sizeof(cmock_call_instance->ReturnVal) == sizeof(Error_enumStatus_t) ? 1 : -1])); /* add Error_enumStatus_t to :treat_as_array if this causes an error */
    return cmock_call_instance->ReturnVal;
  }
  if (!Mock.GPIO_InitPin_CallbackBool &&
      Mock.GPIO_InitPin_CallbackFunctionPointer != NULL)
  {
    Error_enumStatus_t cmock_cb_ret = Mock.GPIO_InitPin_CallbackFunctionPointer(gpiopin, Mock.GPIO_InitPin_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return cmock_cb_ret;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  {
    UNITY_SET_DETAILS(CMockString_GPIO_InitPin,CMockString_gpiopin);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_gpiopin), (void*)(gpiopin), sizeof(GPIOPIN_t), cmock_line, CMockStringMismatch);
  }
  if (Mock.GPIO_InitPin_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.GPIO_InitPin_CallbackFunctionPointer(gpiopin, Mock.GPIO_InitPin_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_GPIO_InitPin(CMOCK_GPIO_InitPin_CALL_INSTANCE* cmock_call_instance, GPIOPIN_t* gpiopin);
void CMockExpectParameters_GPIO_InitPin(CMOCK_GPIO_InitPin_CALL_INSTANCE* cmock_call_instance, GPIOPIN_t* gpiopin)
{
  cmock_call_instance->Expected_gpiopin = gpiopin;
}

void GPIO_InitPin_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, Error_enumStatus_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_GPIO_InitPin_CALL_INSTANCE));
  CMOCK_GPIO_InitPin_CALL_INSTANCE* cmock_call_instance = (CMOCK_GPIO_InitPin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.GPIO_InitPin_CallInstance = CMock_Guts_MemChain(Mock.GPIO_InitPin_CallInstance, cmock_guts_index);
  Mock.GPIO_InitPin_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.GPIO_InitPin_IgnoreBool = (char)1;
}

void GPIO_InitPin_CMockStopIgnore(void)
{
  if(Mock.GPIO_InitPin_IgnoreBool)
    Mock.GPIO_InitPin_CallInstance = CMock_Guts_MemNext(Mock.GPIO_InitPin_CallInstance);
  Mock.GPIO_InitPin_IgnoreBool = (char)0;
}

void GPIO_InitPin_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, GPIOPIN_t* gpiopin, Error_enumStatus_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_GPIO_InitPin_CALL_INSTANCE));
  CMOCK_GPIO_InitPin_CALL_INSTANCE* cmock_call_instance = (CMOCK_GPIO_InitPin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.GPIO_InitPin_CallInstance = CMock_Guts_MemChain(Mock.GPIO_InitPin_CallInstance, cmock_guts_index);
  Mock.GPIO_InitPin_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_GPIO_InitPin(cmock_call_instance, gpiopin);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(Error_enumStatus_t[sizeof(cmock_to_return) == sizeof(Error_enumStatus_t) ? 1 : -1])); /* add Error_enumStatus_t to :treat_as_array if this causes an error */
}

void GPIO_InitPin_AddCallback(CMOCK_GPIO_InitPin_CALLBACK Callback)
{
  Mock.GPIO_InitPin_IgnoreBool = (char)0;
  Mock.GPIO_InitPin_CallbackBool = (char)1;
  Mock.GPIO_InitPin_CallbackFunctionPointer = Callback;
}

void GPIO_InitPin_Stub(CMOCK_GPIO_InitPin_CALLBACK Callback)
{
  Mock.GPIO_InitPin_IgnoreBool = (char)0;
  Mock.GPIO_InitPin_CallbackBool = (char)0;
  Mock.GPIO_InitPin_CallbackFunctionPointer = Callback;
}

Error_enumStatus_t GPIO_SetPinValue(void* PORT, uint32_t gpio_pinNumber, uint32_t gpiopinStatus)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_GPIO_SetPinValue_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_GPIO_SetPinValue);
  cmock_call_instance = (CMOCK_GPIO_SetPinValue_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.GPIO_SetPinValue_CallInstance);
  Mock.GPIO_SetPinValue_CallInstance = CMock_Guts_MemNext(Mock.GPIO_SetPinValue_CallInstance);
  if (Mock.GPIO_SetPinValue_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.GPIO_SetPinValue_FinalReturn;
    memcpy((void*)(&Mock.GPIO_SetPinValue_FinalReturn), (void*)(&cmock_call_instance->ReturnVal),
         sizeof(Error_enumStatus_t[sizeof(cmock_call_instance->ReturnVal) == sizeof(Error_enumStatus_t) ? 1 : -1])); /* add Error_enumStatus_t to :treat_as_array if this causes an error */
    return cmock_call_instance->ReturnVal;
  }
  if (!Mock.GPIO_SetPinValue_CallbackBool &&
      Mock.GPIO_SetPinValue_CallbackFunctionPointer != NULL)
  {
    Error_enumStatus_t cmock_cb_ret = Mock.GPIO_SetPinValue_CallbackFunctionPointer(PORT, gpio_pinNumber, gpiopinStatus, Mock.GPIO_SetPinValue_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return cmock_cb_ret;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  {
    UNITY_SET_DETAILS(CMockString_GPIO_SetPinValue,CMockString_PORT);
    if (cmock_call_instance->Expected_PORT == NULL)
      { UNITY_TEST_ASSERT_NULL(PORT, cmock_line, CMockStringExpNULL); }
    else
      { UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(cmock_call_instance->Expected_PORT, PORT, 1, cmock_line, CMockStringMismatch); }
  }
  {
    UNITY_SET_DETAILS(CMockString_GPIO_SetPinValue,CMockString_gpio_pinNumber);
    UNITY_TEST_ASSERT_EQUAL_HEX32(cmock_call_instance->Expected_gpio_pinNumber, gpio_pinNumber, cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_GPIO_SetPinValue,CMockString_gpiopinStatus);
    UNITY_TEST_ASSERT_EQUAL_HEX32(cmock_call_instance->Expected_gpiopinStatus, gpiopinStatus, cmock_line, CMockStringMismatch);
  }
  if (Mock.GPIO_SetPinValue_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.GPIO_SetPinValue_CallbackFunctionPointer(PORT, gpio_pinNumber, gpiopinStatus, Mock.GPIO_SetPinValue_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_GPIO_SetPinValue(CMOCK_GPIO_SetPinValue_CALL_INSTANCE* cmock_call_instance, void* PORT, uint32_t gpio_pinNumber, uint32_t gpiopinStatus);
void CMockExpectParameters_GPIO_SetPinValue(CMOCK_GPIO_SetPinValue_CALL_INSTANCE* cmock_call_instance, void* PORT, uint32_t gpio_pinNumber, uint32_t gpiopinStatus)
{
  cmock_call_instance->Expected_PORT = PORT;
  cmock_call_instance->Expected_gpio_pinNumber = gpio_pinNumber;
  cmock_call_instance->Expected_gpiopinStatus = gpiopinStatus;
}

void GPIO_SetPinValue_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, Error_enumStatus_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_GPIO_SetPinValue_CALL_INSTANCE));
  CMOCK_GPIO_SetPinValue_CALL_INSTANCE* cmock_call_instance = (CMOCK_GPIO_SetPinValue_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.GPIO_SetPinValue_CallInstance = CMock_Guts_MemChain(Mock.GPIO_SetPinValue_CallInstance, cmock_guts_index);
  Mock.GPIO_SetPinValue_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.GPIO_SetPinValue_IgnoreBool = (char)1;
}

void GPIO_SetPinValue_CMockStopIgnore(void)
{
  if(Mock.GPIO_SetPinValue_IgnoreBool)
    Mock.GPIO_SetPinValue_CallInstance = CMock_Guts_MemNext(Mock.GPIO_SetPinValue_CallInstance);
  Mock.GPIO_SetPinValue_IgnoreBool = (char)0;
}

void GPIO_SetPinValue_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, void* PORT, uint32_t gpio_pinNumber, uint32_t gpiopinStatus, Error_enumStatus_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_GPIO_SetPinValue_CALL_INSTANCE));
  CMOCK_GPIO_SetPinValue_CALL_INSTANCE* cmock_call_instance = (CMOCK_GPIO_SetPinValue_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.GPIO_SetPinValue_CallInstance = CMock_Guts_MemChain(Mock.GPIO_SetPinValue_CallInstance, cmock_guts_index);
  Mock.GPIO_SetPinValue_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_GPIO_SetPinValue(cmock_call_instance, PORT, gpio_pinNumber, gpiopinStatus);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(Error_enumStatus_t[sizeof(cmock_to_return) == sizeof(Error_enumStatus_t) ? 1 : -1])); /* add Error_enumStatus_t to :treat_as_array if this causes an error */
}

void GPIO_SetPinValue_AddCallback(CMOCK_GPIO_SetPinValue_CALLBACK Callback)
{
  Mock.GPIO_SetPinValue_IgnoreBool = (char)0;
  Mock.GPIO_SetPinValue_CallbackBool = (char)1;
  Mock.GPIO_SetPinValue_CallbackFunctionPointer = Callback;
}

void GPIO_SetPinValue_Stub(CMOCK_GPIO_SetPinValue_CALLBACK Callback)
{
  Mock.GPIO_SetPinValue_IgnoreBool = (char)0;
  Mock.GPIO_SetPinValue_CallbackBool = (char)0;
  Mock.GPIO_SetPinValue_CallbackFunctionPointer = Callback;
}

Error_enumStatus_t GPIO_GetPinValue(void* PORT, uint32_t gpio_pinNumber, uint32_t* gpiopinStatus)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_GPIO_GetPinValue_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_GPIO_GetPinValue);
  cmock_call_instance = (CMOCK_GPIO_GetPinValue_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.GPIO_GetPinValue_CallInstance);
  Mock.GPIO_GetPinValue_CallInstance = CMock_Guts_MemNext(Mock.GPIO_GetPinValue_CallInstance);
  if (Mock.GPIO_GetPinValue_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.GPIO_GetPinValue_FinalReturn;
    memcpy((void*)(&Mock.GPIO_GetPinValue_FinalReturn), (void*)(&cmock_call_instance->ReturnVal),
         sizeof(Error_enumStatus_t[sizeof(cmock_call_instance->ReturnVal) == sizeof(Error_enumStatus_t) ? 1 : -1])); /* add Error_enumStatus_t to :treat_as_array if this causes an error */
    return cmock_call_instance->ReturnVal;
  }
  if (!Mock.GPIO_GetPinValue_CallbackBool &&
      Mock.GPIO_GetPinValue_CallbackFunctionPointer != NULL)
  {
    Error_enumStatus_t cmock_cb_ret = Mock.GPIO_GetPinValue_CallbackFunctionPointer(PORT, gpio_pinNumber, gpiopinStatus, Mock.GPIO_GetPinValue_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return cmock_cb_ret;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  {
    UNITY_SET_DETAILS(CMockString_GPIO_GetPinValue,CMockString_PORT);
    if (cmock_call_instance->Expected_PORT == NULL)
      { UNITY_TEST_ASSERT_NULL(PORT, cmock_line, CMockStringExpNULL); }
    else
      { UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(cmock_call_instance->Expected_PORT, PORT, 1, cmock_line, CMockStringMismatch); }
  }
  {
    UNITY_SET_DETAILS(CMockString_GPIO_GetPinValue,CMockString_gpio_pinNumber);
    UNITY_TEST_ASSERT_EQUAL_HEX32(cmock_call_instance->Expected_gpio_pinNumber, gpio_pinNumber, cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_GPIO_GetPinValue,CMockString_gpiopinStatus);
    if (cmock_call_instance->Expected_gpiopinStatus == NULL)
      { UNITY_TEST_ASSERT_NULL(gpiopinStatus, cmock_line, CMockStringExpNULL); }
    else
      { UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(cmock_call_instance->Expected_gpiopinStatus, gpiopinStatus, 1, cmock_line, CMockStringMismatch); }
  }
  if (Mock.GPIO_GetPinValue_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.GPIO_GetPinValue_CallbackFunctionPointer(PORT, gpio_pinNumber, gpiopinStatus, Mock.GPIO_GetPinValue_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_GPIO_GetPinValue(CMOCK_GPIO_GetPinValue_CALL_INSTANCE* cmock_call_instance, void* PORT, uint32_t gpio_pinNumber, uint32_t* gpiopinStatus);
void CMockExpectParameters_GPIO_GetPinValue(CMOCK_GPIO_GetPinValue_CALL_INSTANCE* cmock_call_instance, void* PORT, uint32_t gpio_pinNumber, uint32_t* gpiopinStatus)
{
  cmock_call_instance->Expected_PORT = PORT;
  cmock_call_instance->Expected_gpio_pinNumber = gpio_pinNumber;
  cmock_call_instance->Expected_gpiopinStatus = gpiopinStatus;
}

void GPIO_GetPinValue_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, Error_enumStatus_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_GPIO_GetPinValue_CALL_INSTANCE));
  CMOCK_GPIO_GetPinValue_CALL_INSTANCE* cmock_call_instance = (CMOCK_GPIO_GetPinValue_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.GPIO_GetPinValue_CallInstance = CMock_Guts_MemChain(Mock.GPIO_GetPinValue_CallInstance, cmock_guts_index);
  Mock.GPIO_GetPinValue_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.GPIO_GetPinValue_IgnoreBool = (char)1;
}

void GPIO_GetPinValue_CMockStopIgnore(void)
{
  if(Mock.GPIO_GetPinValue_IgnoreBool)
    Mock.GPIO_GetPinValue_CallInstance = CMock_Guts_MemNext(Mock.GPIO_GetPinValue_CallInstance);
  Mock.GPIO_GetPinValue_IgnoreBool = (char)0;
}

void GPIO_GetPinValue_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, void* PORT, uint32_t gpio_pinNumber, uint32_t* gpiopinStatus, Error_enumStatus_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_GPIO_GetPinValue_CALL_INSTANCE));
  CMOCK_GPIO_GetPinValue_CALL_INSTANCE* cmock_call_instance = (CMOCK_GPIO_GetPinValue_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.GPIO_GetPinValue_CallInstance = CMock_Guts_MemChain(Mock.GPIO_GetPinValue_CallInstance, cmock_guts_index);
  Mock.GPIO_GetPinValue_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_GPIO_GetPinValue(cmock_call_instance, PORT, gpio_pinNumber, gpiopinStatus);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(Error_enumStatus_t[sizeof(cmock_to_return) == sizeof(Error_enumStatus_t) ? 1 : -1])); /* add Error_enumStatus_t to :treat_as_array if this causes an error */
}

void GPIO_GetPinValue_AddCallback(CMOCK_GPIO_GetPinValue_CALLBACK Callback)
{
  Mock.GPIO_GetPinValue_IgnoreBool = (char)0;
  Mock.GPIO_GetPinValue_CallbackBool = (char)1;
  Mock.GPIO_GetPinValue_CallbackFunctionPointer = Callback;
}

void GPIO_GetPinValue_Stub(CMOCK_GPIO_GetPinValue_CALLBACK Callback)
{
  Mock.GPIO_GetPinValue_IgnoreBool = (char)0;
  Mock.GPIO_GetPinValue_CallbackBool = (char)0;
  Mock.GPIO_GetPinValue_CallbackFunctionPointer = Callback;
}

