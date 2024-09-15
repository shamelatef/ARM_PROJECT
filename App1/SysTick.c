/*
 * SysTick.c
 *
 *  Created on: Jul 27, 2024
 *      Author: Radwan
 */

#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"



/***********************************************************************************************************************************
 * ******************************************************Global Variables***********************************************************
 * **********************************************************************************************************************************/


/*Global Variable - a pointer to a function that takes none and return none to store the address of callback function */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;





/***********************************************************************************************************************************
 * **********************************************************Functions**************************************************************
 * **********************************************************************************************************************************/


    /*********************************************************************
    * Service Name: SysTick_Init
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): a_TimeInMilliSeconds - The Time in milliseconds to get interrupt
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Initialize the SysTick timer with the specified time in milliseconds
    using interrupts. This function is used to setup the timer to generate periodic
    interrupts every specified time in milliseconds
    **********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = LOGIC_LOW;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  =a_TimeInMilliSeconds*(RELOAD_VALUE_PER_1_SECOND /1000);
    SYSTICK_CURRENT_REG = LOGIC_LOW;           /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Disable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x06;
    SysTick_Start();


}




    /*********************************************************************
    * Service Name: SysTick_StartBusyWait
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): a_TimeInMilliSeconds - The Time in milliseconds to get interrupt
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Initialize the SysTick timer with the specified time in milliseconds
    using polling or busy-wait technique. The function should exit when the time is
    elapsed and stops the timer at the end.

    **********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = LOGIC_LOW;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  =a_TimeInMilliSeconds*(RELOAD_VALUE_PER_1_SECOND /1000);
    SYSTICK_CURRENT_REG = LOGIC_LOW;              /* Clear the Current Register value */


    /* Configure the SysTick Control Register
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x04;
    SysTick_Start();
    while(!(SYSTICK_CTRL_REG & (1<<16))); /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ... COUNT flag is cleared after read the CTRL register value */


}


    /*********************************************************************
    * Service Name: SysTick_Handler
    * Sync/Async: Asynchronous
    * Reentrancy: non-reentrant
    * Parameters (in): None
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Handler for SysTick interrupt use to call the call-back function.
    **********************************************************************/
void SysTick_Handler(void)
{
    if(g_callBackPtr != NULL_PTR)
    {
        (*g_callBackPtr)();
    }


}



    /*********************************************************************
    * Service Name: SysTick_SetCallBack
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): a_TimeInMilliSeconds - The Time in milliseconds to get interrupt
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Function to setup the SysTick Timer call back to be executed in
    SysTick Handler.
    **********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    g_callBackPtr= Ptr2Func;

}



    /*********************************************************************
    * Service Name: SysTick_Start
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): a_TimeInMilliSeconds - The Time in milliseconds to get interrupt
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Function to start systic
    * **********************************************************************/

void SysTick_Start(void){

    SYSTICK_CTRL_REG   |= 0x01;

}


    /*********************************************************************
    * Service Name: SysTick_Stop
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): a_TimeInMilliSeconds - The Time in milliseconds to get interrupt
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Function to stop the SysTick Timer
    * **********************************************************************/
void SysTick_Stop(void){
    SYSTICK_CTRL_REG   &= 0xFE;
}


    /*********************************************************************
    * Service Name: SysTick_DeInit
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): a_TimeInMilliSeconds - The Time in milliseconds to get interrupt
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Function to de initialize Systic timer
    **********************************************************************/
void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_CURRENT_REG=0;
}



