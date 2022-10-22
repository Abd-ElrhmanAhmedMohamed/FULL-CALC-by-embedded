/*************************************/
/*Description : DIO interface file   */
/*AUTHOR : Eslam                     */
/*DATE : 20/8/2022                   */
/*VERSION : 0.1V                     */
/*************************************/

#ifndef DIO_INT_H
#define DIO_INT_H

void DIO_voidInit(void);

tenuErrorStatus DIO_enuSetPinValue(uint8 u8PinNumCpy , uint8 u8PinValueCpy);

tenuErrorStatus DIO_enuGetPinValue(uint8 u8PinNumCpy , uint8 * pu8PinValueCpy);

#endif



