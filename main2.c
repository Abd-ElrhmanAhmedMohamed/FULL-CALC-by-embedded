#include "../../app/Calculator/STD_Types.h"
#include "../../app/Calculator/BIT_Math.h"

#include <avr/delay.h>
#include "../../app/Calculator/LCD_int.h"
#include "../../app/Calculator/KEYPAD_int.h"
#include "../../app/Calculator/DIO_int.h"
uint8 inputs [16]   ;
uint8 operators[16] ;
float Numbers[16]   ;
uint8 MaxOpr        ;
uint8 MaxNum        ;
uint8 SyntxErrCheck ;
uint8 MathErrCheck  ;

float helpDEC          ;   /*NEWW*/
int helpDEC2           ;    /*NEWW*/
uint8 CH1,CH2,skipper  ;      /*NEWW*/

sint32 power(uint8 num1 , uint8 num2);
void   PrintResult(float Result)     ;
void   Add_Diff (void)               ;
void   Multiply_Divison(void)        ;
void   Sort_Oper_Num(uint8 arr[16])  ;
void   ShiftOprArr(uint8 indx)       ;
void   ShiftNumArr(uint8 indx)       ;



int main (void)
{
	DIO_voidInit()                     ;
    LCD_voidInit()                     ;
    KEYPAD_voidInit()                  ;
	uint8 u8InputCntrLoc,u8CheckLoc    ;
	uint8 reset					       ;
	uint8 SyntxErrMsg[]="Syntax Error!";
	uint8 MathErrMsg[]="Math Error!"   ;


 	while (1)
	{
	    uint8 cycle;
	    for(cycle=0;cycle<16;cycle++)
	    {
	        inputs[cycle]=0   ;
	        Numbers[cycle]=0  ;
	        operators[cycle]=0;
	    }

 		LCD_voidClrDisplay(0);
		MaxNum=0       ;
		MaxOpr=0       ;
		reset=0        ;
		SyntxErrCheck=0;
		MathErrCheck=0 ;
		for(u8InputCntrLoc=0;u8InputCntrLoc<16;u8InputCntrLoc++)
		{
            do
            {
                u8CheckLoc = KEYPAD_u8GetPressedKey(0);
            }
            while(u8CheckLoc==0xFF);
            if(u8CheckLoc=='=')
            {
                break;
            }
            if(u8CheckLoc=='A')
            {
                reset=1;
                break  ;
            }
            inputs[u8InputCntrLoc] = u8CheckLoc       ;
            LCD_enuWriteData(0,inputs[u8InputCntrLoc]);
            _delay_ms(100)                            ;
		}
		if (reset)
		{
			LCD_voidClrDisplay(0);
			continue             ;
		}
		while(u8InputCntrLoc==16)
		{
			do
            {
                u8CheckLoc = KEYPAD_u8GetPressedKey(0);
            }
            while(u8CheckLoc==0xFF);
			if(u8CheckLoc=='=')
			{
				break;
			}
		}
		Sort_Oper_Num(inputs)             ;
        if(SyntxErrCheck)
        {
            LCD_voidClrDisplay(0)              ;
            LCD_voidWriteString(0,SyntxErrMsg);
        }
        else
        {
            Multiply_Divison()                ;
            if (MathErrCheck)
            {
                LCD_voidClrDisplay(0)              ;
                LCD_voidWriteString(0,MathErrMsg) ;
            }
            else
            {
                Add_Diff ()                       ;
                PrintResult(Numbers[0])           ;
            }
        }


		while(1)
				{
					do{u8CheckLoc = KEYPAD_u8GetPressedKey(0);}
							while(u8CheckLoc==0xFF);
					if(u8CheckLoc=='A')
					{
						break;
					}
				}
	}
	return 0;
}
void ShiftOprArr(uint8 indx)
{uint8 i;
	for( i =indx; i<MaxOpr;i++)
	{
		if (i==15)
		{
			operators[i]==0;
			break    ;
		}
		operators[i]=operators[i+1];
	}
}
void ShiftNumArr(uint8 indx)
{
    uint8 i;
	for( i =indx; i<MaxNum;i++)
	{
		if (i==15)
		{
			Numbers[i]==0;
			break    ;
		}
		Numbers[i]=Numbers[i+1];
	}
}
void Sort_Oper_Num(uint8 arr[16])
{
	uint8 NewNumCheck=1,NewOprCheck=1,i;
	if (inputs[0]=='-')
    {
        Numbers[MaxNum]=0    ;
        operators[MaxOpr]='-';
        MaxNum++        ;
        MaxOpr++        ;
        NewOprCheck=0   ;
    }
	for(i=MaxNum;i<16;i++)
	{
		if (arr[i]>='0'&&arr[i]<='9')
		{
		    NewOprCheck=1;
			if(NewNumCheck)
			{
				Numbers[MaxNum]=(float)(arr[i]-'0');
				NewNumCheck=0                      ;
				MaxNum++						   ;
			}
			else
			{
				Numbers[MaxNum-1]=Numbers[MaxNum-1]*10+(float)(arr[i]-'0');
			}
		}
		else if (arr[i]=='+' ||arr[i]== '-')
		{
		    if(!NewOprCheck)
            {
                if(arr[i]=='-')
                {
                    if(operators[MaxOpr-1]=='*'||operators[MaxOpr-1]=='/')
                    {
                        Numbers[MaxNum]=1    ;
                        operators[MaxOpr]='-';
                        MaxNum++             ;
                        MaxOpr++             ;
                        NewOprCheck=0        ;
                    }
                    else if(operators[MaxOpr-1]=='+')
                    {
                        ShiftOprArr(MaxOpr-1)  ;
                        MaxOpr--               ;
                    }
                    else
                    {
                        operators[MaxOpr-1]='+';
                        continue;
                    }
                }
                else
                {
                    continue;

                }
            }
			NewNumCheck=1            ;
			operators[MaxOpr]=arr[i] ;
			MaxOpr++				 ;
			NewOprCheck=0            ;
		}
		else if(arr[i]=='/' ||arr[i]=='*')
        {
            if(!NewOprCheck)
            {
                SyntxErrCheck=1;
                break     ;
            }
            NewNumCheck=1            ;
            operators[MaxOpr]=arr[i] ;
			MaxOpr++				 ;
			NewOprCheck=0            ;
        }
	}
}
void Multiply_Divison(void)
{
    uint8 i;
	for ( i=0;i<MaxOpr;i++)
	{
		if(operators[i]=='*')
		{
			Numbers[i]=Numbers[i]*Numbers[i+1];
			ShiftNumArr(i+1)                  ;
			MaxNum--						  ;
			ShiftOprArr(i)                    ;
			MaxOpr--						  ;
			i--                               ;
		}
		else if (operators[i]=='/')
		{
		    if(Numbers[i+1]==0)
            {
                MathErrCheck=1;
                break         ;
            }
            else
            {
                Numbers[i]=Numbers[i]/Numbers[i+1];
                ShiftNumArr(i+1)                   ;
                MaxNum--						  ;
                ShiftOprArr(i)                       ;
                MaxOpr--						  ;
                i--                               ;
            }
		}
	}
}
void Add_Diff (void)
{
    uint8 i;
	for ( i=0;i<MaxOpr;i++)
	{
		if(operators[i]=='+')
		{

			Numbers[i]=Numbers[i]+Numbers[i+1];
			ShiftNumArr(i+1)           ;
			MaxNum--						  ;
			ShiftOprArr(i)             ;
			MaxOpr--						  ;
			i--                               ;



		}
		else if(operators[i]=='-')
		{
			Numbers[i]=Numbers[i]-Numbers[i+1];
			ShiftNumArr(i+1)           ;
			MaxNum--						  ;
			ShiftOprArr(i)             ;
			MaxOpr--						  ;
			i--                               ;
		}


	}
}
void PrintResult(float Result)
{
	uint8 Result_As_Char[16],cntr;
	uint8 i,Ngtv=0;
	if(Result<0)
	{
        Result=-Result;
		Ngtv=1;
	}



	helpDEC=0                ;
	helpDEC2=Result          ;     /*NEWW*/
	helpDEC=Result-helpDEC2  ;     /*NEWW*/
	if(helpDEC>0)                  /*NEWW*/
	{
     	helpDEC*=100000  ;
		if ((uint32)helpDEC%10==0)
		{
			skipper=1;
			if ((uint32)helpDEC%100==0)
			{
				skipper=2;
				if ((uint32)helpDEC%1000==0)
				{
					skipper=3;

			     	if ((uint32)helpDEC%10000==0)
			    	{
					   skipper=4;
			    	}
				}
			}
		}
       helpDEC=helpDEC/power(10,skipper);
		for( i=1;i<6-skipper;i++)         /*  i think (-skipper) has no use !*/
	{
		Result_As_Char[i-1]=(uint8)((((uint32)helpDEC)%(power(10,i)))/power(10,i-1));
		helpDEC-=(float)((uint32)helpDEC%(power(10,i)));
		if (helpDEC==0||helpDEC<1)
		{
			break;
		}
	}
        for(CH1=1;CH1<(i+1);CH1++)
	{
		LCD_enuWriteCmd(0,0xD0-CH1);
		LCD_enuWriteData(0,Result_As_Char[CH1-1]+'0');
	}
		LCD_enuWriteCmd(0,0xD0-CH1);
		LCD_enuWriteData(0,'.');
    for( i=1;i<17;i++)
	{
		Result_As_Char[i-1]=(uint8)((((uint32)helpDEC2)%(power(10,i)))/power(10,i-1));
		helpDEC2-=(float)((uint32)helpDEC2%(power(10,i)));
		if (helpDEC2==0)
		{
			break;
		}
	}
	for(CH2=1;CH2<(i+1);CH2++)
	{
		LCD_enuWriteCmd(0,0xD0-CH2-CH1);
		LCD_enuWriteData(0,Result_As_Char[CH2-1]+'0');
	}
    if(Ngtv)
    {
        LCD_enuWriteCmd(0,0xD0-CH2-CH1);
        LCD_enuWriteData(0,'-');
    }

		return  ;
    }




	for( i=1;i<17;i++)
	{
		Result_As_Char[i-1]=(uint8)((((uint32)Result)%(power(10,i)))/power(10,i-1));
		Result-=(float)((uint32)Result%(power(10,i)));
		if (Result==0)
		{
			break;
		}
	}
	for(cntr=1;cntr<(i+1);cntr++)
	{
		LCD_enuWriteCmd(0,0xD0-cntr);
		LCD_enuWriteData(0,Result_As_Char[cntr-1]+'0');
	}
	if(Ngtv)
    {
        LCD_enuWriteCmd(0,0xD0-cntr);
        LCD_enuWriteData(0,'-');
    }

}
sint32 power(uint8 num1 , uint8 num2)
{
	if(num2==0)
	{
		return 1;
	}
	else if (num2==1)
	{
		return num1;
	}
	else
	{
		return num1 * power(num1,num2-1);
	}
}
