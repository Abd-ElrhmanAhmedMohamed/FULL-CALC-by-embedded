#include "STD_Types.h"

#include "KEYPAD_cfg.h"
#include "KEYPAD_priv.h"



tstrKeypadConfigSet KEYPAD_astrConfigSet[KEYPAD_MAX_NUM]=
{
    /* KEYPAD 0 */
	{
		/*  au8InputPins  */
		{24, 25,26,27} ,
		/* au8OutputPins*/
		{28,29,30,31}  ,
		{0b00001110,0b00001101,0b00001011,0b00000111},
		/* u8InputPinsNum */
		KEYPAD0_INPUT_PINS_NUM ,
		/* u8OutputPinsNum */
		KEYPAD0_OUTPUT_PINS_NUM
	}
	,
		
    /* KEYPAD 1*/
	{
		/*  au8InputPins  */
		{11,12,13} ,
		/* au8OutputPins*/
		{15,16,17,18,19} ,
	    {0b00000110,0b00000101,0b00000011},
		/* u8InputPinsNum */
		KEYPAD1_INPUT_PINS_NUM,
		/* u8OutputPinsNum */
		KEYPAD1_OUTPUT_PINS_NUM
	}
	
} ;


uint8 KEYPAD_au8SwitchMapping[KEYPAD_MAX_NUM][KEYPAD_MAX_INPUT_PINS_NUM][KEYPAD_MAX_OUTPUT_PINS_NUM] =
{
	
	{
		{'7' ,'8' ,'9' , '+'},
		{'4' ,'5' ,'6' , '-'},
		{'1' ,'2' ,'3' , '/'},
		{'ِِِِA' ,'0' ,'*' , '='}
	},
	{
		{'A' ,'B' ,'C' , 'D' , 'E'},
		{'A' ,'B' ,'C' , 'D' , 'E'},
		{'A' ,'B' ,'C' , 'D' , 'E'}
	}
	
	
	
};


