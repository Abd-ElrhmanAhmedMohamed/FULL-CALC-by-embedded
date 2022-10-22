

#ifndef LCD_INT_H
#define LCD_INT_H

void LCD_voidInit(void);
tenuErrorStatus LCD_enuWriteCmd(uint8 u8LcdIndxCpy , uint8 u8LcdCmdCpy);
tenuErrorStatus LCD_enuWriteData(uint8 u8LcdIndxCpy , uint8 u8LcdDataCpy);
void LCD_voidClrDisplay(void);


#endif
