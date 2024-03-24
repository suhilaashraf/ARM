#include "Lcd.h"
#include "gpio.h"
#include "Lcdcfg.h"

/******the LCD commands***********/

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define FUNCTION_SET 0x38
#define DISPLAYOFF_CURSOROFF 0x08
#define DISPLAYOFF_CURSORON 0x0A
#define DISPLAYON_CURSOROFF 0x0C
#define DISPLAYON_CURSORON 0x0E
#define DISPLAYON_CURSORBLINK 0x0F
#define ENTERY_SET 0x06
#define SHIFT_DISPLAY 0x07

#define FIRSTROW 0x80
#define SECONDROW 0xC0
#define COLNUMBER 16

#define periodicity 4 // 10 ms

/***********************LCD TYPEDEF*****************************/

typedef enum
{
	NoReq,
	InitReq,
	WriteReq,
	ClearReq,
	MovCurReq,
} ReqType;

typedef struct Lcd
{
	const char *message;
	uint8_t len;
	ReqType State;
	uint8_t row;
	uint8_t col;
} UserRequest;

typedef enum
{
	init,
	operational,
	off,
} LcdState;

typedef enum
{
	poweron,
	functionset,
	enterymode,
	cleardisplay,
	eneteryset,
} initState;
typedef enum
{
	lcdEnableON,
	lcdEnableOFF,
	lcdEnabledone,
} lcdEnable_state;

/***********************VARIABLES*****************************/

UserRequest userreq;
LcdState lcdstate;
initState initstate;
lcdEnable_state EnableState;

extern LCDCFG_str Lcd_cfg[LCDPINS];

/***********************FUNCTIONS PROTOTYPES*****************************/

static Error_enumStatus_t lcdinit(void);
static Error_enumStatus_t lcdwrite_command(uint8_t command);
static Error_enumStatus_t lcdwrite_string(void);
static Error_enumStatus_t lcdwrite_char(uint8_t character);
static Error_enumStatus_t Lcd_SetCursorPos(void);
static Error_enumStatus_t lcdEnable(void);

/***********************IMPLEMENTATIONS*****************************/

void Lcdinit_Asyn(void)
{
	lcdstate = init;
	userreq.State = InitReq;
}
Error_enumStatus_t LcdWriteString_Asyn(const char *msg, uint8_t length)
{
	Error_enumStatus_t ReturnStatus = Status_enumNotOk;
	if (userreq.State == NoReq)
	{
		userreq.message = msg;
		userreq.len = length;
		userreq.State = WriteReq;
		ReturnStatus = Status_enumOk;
	}

	return ReturnStatus;
}

Error_enumStatus_t Lcd_ClearScreen_Asyn(void)
{
	Error_enumStatus_t ReturnStatus = Status_enumNotOk;
	if (userreq.State == NoReq)
	{
		userreq.State = ClearReq;
		ReturnStatus = Status_enumOk;
	}
	return ReturnStatus;
}
Error_enumStatus_t Lcd_SetCursorPosAsyn(uint8_t row, uint8_t coln)
{
	Error_enumStatus_t Returnstatus = Status_enumNotOk;
	if (userreq.State == NoReq)
	{
		if (row != FIRSTROW && row != SECONDROW)
		{
			Returnstatus = Status_enumParameterError;
		}
		else if (coln > COLNUMBER)
		{
			Returnstatus = Status_enumParameterError;
		}
		else
		{
			userreq.row = row;
			userreq.col = coln;
			userreq.State = MovCurReq;
			Returnstatus = Status_enumOk;
		}
	}
	return Returnstatus;
}

void LCD_TASK(void)
{
	if (lcdstate == init)
	{
		lcdinit();
	}
	else if (lcdstate == operational)
	{
		if (userreq.State != NoReq)
		{
			switch (userreq.State)
			{
			case WriteReq:
				lcdwrite_string();
				break;

			case ClearReq:
				if (lcdwrite_command(CLEAR_DISPLAY) == Status_enumOk)
				{
					userreq.State = NoReq;
				}
				break;

			case MovCurReq:
			Lcd_SetCursorPos();
				break;

			default:
				break;
			}
		}
	}

	else if (lcdstate == off)
	{
	}
}
static Error_enumStatus_t lcdinit(void) // 10 ms
{
	Error_enumStatus_t Returnstatus = Status_enumNotOk;
	uint8_t idx;
	GPIOPIN_t lcd_str;
	switch (initstate)
	{
	case poweron:

		lcd_str.gpioSPEED = GPIO_HIGHSPEED;
		for (idx = 0; idx < LCDPINS; idx++)
		{
			lcd_str.gpioMODE = GPIO_OUTPUT_PP;
			lcd_str.gpioPORT = Lcd_cfg[idx].Lcdport;
			lcd_str.gpioPIN = Lcd_cfg[idx].Lcdpin;
			GPIO_InitPin(&lcd_str);
		}
		initstate = functionset;
		break;

	case functionset:
		if (lcdwrite_command(FUNCTION_SET) == Status_enumOk)
		{
			initstate = enterymode;
		}
		break;

	case enterymode:
		if (lcdwrite_command(DISPLAYON_CURSORON) == Status_enumOk)
		{
			initstate = cleardisplay;
		}
		break;

	case cleardisplay:
		if (lcdwrite_command(CLEAR_DISPLAY) == Status_enumOk)
		{
			initstate = eneteryset;
		}
		break;

	case eneteryset:
		if (lcdwrite_command(ENTERY_SET) == Status_enumOk)
		{
			lcdstate = operational;
			userreq.State = NoReq;
			Returnstatus = Status_enumOk;
		}
		break;

	default:
		break;
	}
	return Returnstatus;
}

static Error_enumStatus_t lcdwrite_string(void)
{
	Error_enumStatus_t Returnstatus = Status_enumNotOk;
	static uint8_t idx = 0;
	static uint8_t counter;
	if ((idx < userreq.len) && (counter == 0))
	{
		Returnstatus = lcdwrite_char(userreq.message[idx]);
		idx++;
		counter++;
	}
	if (EnableState != lcdEnabledone)
	{
		lcdEnable();
	}
	else
	{
		counter = 0;
		EnableState = lcdEnableON;
		if (idx == userreq.len)
		{
			Returnstatus = Status_enumOk;
			userreq.State = NoReq;
			idx = 0;
		}
	}
	return Returnstatus;
}

static Error_enumStatus_t lcdwrite_command(uint8_t command)
{
	Error_enumStatus_t Returnstatus = Status_enumNotOk;
	static uint8_t idx;
	uint8_t count = 0;
	static uint8_t counter = 0;

	if (counter == 0)
	{
		GPIO_SetPinValue(Lcd_cfg[RS].Lcdport, Lcd_cfg[RS].Lcdpin, LOGIC_LOW);
		GPIO_SetPinValue(Lcd_cfg[RW].Lcdport, Lcd_cfg[RW].Lcdpin, LOGIC_LOW);
		for (idx = DB0; idx < LCDPINS; idx++)
		{
			GPIO_SetPinValue(Lcd_cfg[idx].Lcdport, Lcd_cfg[idx].Lcdpin, ((command >> count) & 1));
			count++;
		}
		counter++;
	}
	if (EnableState != lcdEnabledone)
	{
		lcdEnable();
	}
	else
	{
		counter = 0;
		EnableState = lcdEnableON;
		if (idx == LCDPINS)
		{
			Returnstatus = Status_enumOk;
		}
	}
	return Returnstatus;
}

static Error_enumStatus_t lcdwrite_char(uint8_t character)
{
	Error_enumStatus_t Returnstatus = Status_enumNotOk;
	uint8_t idx;
	uint8_t count = 0;
	GPIO_SetPinValue(Lcd_cfg[RS].Lcdport, Lcd_cfg[RS].Lcdpin, LOGIC_HIGH);
	GPIO_SetPinValue(Lcd_cfg[RW].Lcdport, Lcd_cfg[RW].Lcdpin, LOGIC_LOW);
	for (idx = DB0; idx < LCDPINS; idx++)
	{
		Returnstatus = GPIO_SetPinValue(Lcd_cfg[idx].Lcdport, Lcd_cfg[idx].Lcdpin, ((character >> count) & 1));
		count++;
	}

	return Returnstatus;
}

static Error_enumStatus_t lcdEnable(void) // Delay 30
{
	Error_enumStatus_t Returnstatus = Status_enumNotOk;
	static uint8_t count;
	count += periodicity;
	if (EnableState == lcdEnableON && count == 4)
	{
		Returnstatus = GPIO_SetPinValue(Lcd_cfg[EN].Lcdport, Lcd_cfg[EN].Lcdpin, LOGIC_HIGH);
		EnableState = lcdEnableOFF;
	}
	else if (EnableState == lcdEnableOFF && count == 8)
	{
		Returnstatus = GPIO_SetPinValue(Lcd_cfg[EN].Lcdport, Lcd_cfg[EN].Lcdpin, LOGIC_LOW);
	}
	else if (count == 12)
	{
		count = 0;
		EnableState = lcdEnabledone;
	}
	return Returnstatus;
}

static Error_enumStatus_t Lcd_SetCursorPos(void)
{
	Error_enumStatus_t Returnstatus = Status_enumNotOk;
	uint8_t pos;
	pos = userreq.row + userreq.col;
	if (lcdwrite_command(pos) == Status_enumOk)
	{
		userreq.State = NoReq;
	}

	return Returnstatus;
}
