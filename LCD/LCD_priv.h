#ifndef LCD_PRIV_H
#define LCD_PRIV_H

#define LCD_4BIT_MODE   0
#define LCD_8BIT_MODE   1

#define LCD_ONE_LINE  0
#define LCD_TWO_LINE  1

#define LCD_CHAR_FONT_5x7   0
#define LCD_CHAR_FONT_5x11  1

#define LCD_DISPLAY_OFF 0
#define LCD_DISPLAY_ON  1


#define LCD_CURSOR_OFF 0
#define LCD_CURSOR_ON  1


#define LCD_CURSOR_BLINK_OFF 0
#define LCD_CURSOR_BLINK_ON  1

#define LCD_SHIFT_OFF 0
#define LCD_SHIFT_ON  1

#define LCD_INC_LTR 1
#define LCD_INC_RTL 0

typedef struct {
	uint8 u8LcdMode ;
	uint8 au8ControlPins[3];
	uint8 au8DataPins[8];
	
}tstrLcdPinOutCfg;

typedef struct {
	uint8 u8LineMode     :1 ; 
	uint8 u8CharFont     :1 ;
	uint8 u8DisplayState :1 ;
	uint8 u8CursorState  :1 ;
	uint8 u8BlinkState   :1 ;
	uint8 u8IncreMode    :1 ;
	uint8 u8WindowMode   :1 ;
}tstrLcdOptionCfg;

typedef struct {
	tstrLcdPinOutCfg strLcdPinOutCfg;
	tstrLcdOptionCfg strLcdOptionCfg ;
}tstrLcdCfg;
extern  tstrLcdCfg  LCD_astrConfig[LCD_MAX_NUM] ;
static void LCD_voidHelp(uint8 u8LcdIndxCpy, uint8 u8LcdCmdDataCpy);

#endif