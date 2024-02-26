#ifndef ERROR_H_
#define ERROR_H_
typedef enum
{
	/**
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	Status_enumOk ,
	/**
	 *@brief :NOT oK ERROR
	 */
	Status_enumNotOk ,
	/**
	 *@brief :Wrong Input error
	 */
	Status_enumParameterError,
	/**
	 *@brief :Wrong Input error
	 */
	Status_enumNULLPointer,

}Error_enumStatus_t;

#endif /* ERROR */
