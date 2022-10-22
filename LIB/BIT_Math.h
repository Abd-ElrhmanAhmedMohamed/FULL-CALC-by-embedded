/***************************************************/
/* Description : Standard lib for bit manipulation */
/* Author      : 3abooudy                          */
/* Date        : 6-8-2022                          */
/* Version     : 1V                                */
/***************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(Reg , BitNo) ( (Reg) = (Reg) | ( 1 << (BitNo) ) )
#define CLR_BIT(Reg , BitNo) ( (Reg) = (Reg) & ~( 1 << (BitNo) ) )
#define TGL_BIT(Reg , BitNo) ( (Reg) = (Reg) ^ ( 1 << (BitNo) ) )
#define GET_BIT(Reg , BitNo) ( (Reg) >> (BitNo) & 0x01)

#endif 

