
#include "STD_Types.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

tstrLcdCfg  LCD_astrConfig[LCD_MAX_NUM]=
{
	{
		/*   strLcdPinOutCfg  */
		/* Mode          RS  RW  EN    D0 D1                  D7 */
		{LCD_8BIT_MODE ,{0  ,1  ,2  },{8 ,9 , 10 ,11,12,13,14,15}},
		/*   strLcdOptionCfg  */
		{
		    LCD_TWO_LINE        ,LCD_CHAR_FONT_5x7,
		    LCD_DISPLAY_ON      ,LCD_CURSOR_OFF   ,
		    LCD_CURSOR_BLINK_OFF,LCD_INC_LTR      ,
		    LCD_SHIFT_OFF
		 }
	}
	
	
};











