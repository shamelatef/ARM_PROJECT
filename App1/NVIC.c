/*
 * NVIC.c
 *
 *  Created on: Jul 27, 2024
 *      Author: Radwan
 */


/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/

#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"


/*******************************************************************************
 *                           Functions' Definitions                           *
 *******************************************************************************/




    /*********************************************************************
    * Service Name: NVIC_EnableIRQ
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): IRQ_Num - The interrupt request Number
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: The function takes the interrupt request number and enable its corresponding bit in nvic enable registers
    **********************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num<32)
    {
        NVIC_EN0_REG |= 1<<IRQ_Num;
    }
    else if (IRQ_Num>31 && IRQ_Num<64)
    {
        NVIC_EN1_REG |= (1<<(IRQ_Num-32));
    }
    else if (IRQ_Num>63 && IRQ_Num<96)
    {
        NVIC_EN2_REG |= (1<<(IRQ_Num-64));
    }
    else if (IRQ_Num>95 && IRQ_Num<128)
    {
        NVIC_EN3_REG |= (1<<(IRQ_Num-96));
    }

    else if (IRQ_Num>127 && IRQ_Num<139)
    {
        NVIC_EN4_REG |= (1<<(IRQ_Num-128));
    }

}


    /*********************************************************************
    * Service Name: NVIC_DisableIRQ
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): IRQ_Num - The interrupt request Number
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: The function takes the interrupt request number and disable its corresponding bit in nvic enable registers
    **********************************************************************/

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num<32)
    {
        NVIC_DIS0_REG &= ~(1<<IRQ_Num);
    }
    else if (IRQ_Num>31 && IRQ_Num<64)
    {
        NVIC_DIS1_REG &= ~(1<<(IRQ_Num-32));
    }
    else if (IRQ_Num>63 && IRQ_Num<96)
    {
        NVIC_DIS2_REG &= ~(1<<(IRQ_Num-64));
    }
    else if (IRQ_Num>95 && IRQ_Num<128)
    {
        NVIC_DIS3_REG &= ~(1<<(IRQ_Num-96));
    }
    else if (IRQ_Num>127 && IRQ_Num<139)
    {
        NVIC_DIS4_REG |= (1<<(IRQ_Num-128));
    }


}

    /*********************************************************************
    * Service Name: NVIC_SetPriorityIRQ
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): IRQ_Num, IRQ_Priority - The interrupt request Number, The interrupt request Priority
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: The function takes the interrupt request number and set its priority.
    **********************************************************************/


void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,NVIC_IRQPriorityType IRQ_Priority)
{
    /*bits from 5 to 7 in any priority register*/

    if (IRQ_Num % 4 == 0)
    {
        /*Macro that takes irq number and divide it by 4 to know which pri register to be in */
        NVIC_PRI_REG(IRQ_Num) = ( NVIC_PRI_REG(IRQ_Num) & 0xFFFFFF1F )| (IRQ_Priority<<5);
    }

    /*interrupts 4n+1 ,  bits from 13-15*/
    else if ((IRQ_Num - 1) % 4 == 0)
    {
        NVIC_PRI_REG(IRQ_Num) = ( NVIC_PRI_REG(IRQ_Num) & 0xFFFF1FFF)| (IRQ_Priority<<13);


    }

    /*interrupts 4n+2 ,  bits from 21-23*/
    else if ((IRQ_Num - 2) % 4 == 0)
    {
        NVIC_PRI_REG(IRQ_Num) = ( NVIC_PRI_REG(IRQ_Num) & 0xFF1FFFFF)|(IRQ_Priority<<21);

    }

    /*interrupts 4n+3 ,  bits from 29-31*/
    else if ((IRQ_Num - 3) % 4 == 0 )
    {
        NVIC_PRI_REG(IRQ_Num) = (NVIC_PRI_REG(IRQ_Num) & 0x1FFFFFFF)| (IRQ_Priority<<29);
    }



}

    /*********************************************************************
    * Service Name: NVIC_EnableException
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): Exception_Num
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Takes THE EXCeption number and enable its corresponding interrupt bit
    **********************************************************************/


void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
    }

    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;

    }
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;

    }


}


    /*********************************************************************
    * Service Name: NVIC_DisableException
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): Exception_Num
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Takes THE EXCeption number and disable its corresponding interrupt bit
    **********************************************************************/

void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
    }

    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;

    }
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;

    }

}

    /*********************************************************************
    * Service Name: NVIC_SetPriorityException
    * Sync/Async: Synchronous
    * Reentrancy: non-reentrant
    * Parameters (in): Exception_Num , Priority
    * Parameters (inout): None
    * Parameters (out): None
    * Return value: None
    * Description: Takes THE EXCeption number and set its priority
    **********************************************************************/


void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG =   (NVIC_SYSTEM_PRI1_REG & ~MEM_FAULT_PRIORITY_MASK)|(Exception_Priority<<MEM_FAULT_PRIORITY_BITS_POS) ;
    }

    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG =   (NVIC_SYSTEM_PRI1_REG & ~BUS_FAULT_PRIORITY_MASK)|(Exception_Priority<<BUS_FAULT_PRIORITY_BITS_POS) ;
    }

    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {
        NVIC_SYSTEM_PRI1_REG =   (NVIC_SYSTEM_PRI1_REG & ~USAGE_FAULT_PRIORITY_MASK)|(Exception_Priority<<USAGE_FAULT_PRIORITY_BITS_POS) ;
    }

    else if (Exception_Num == EXCEPTION_SVC_TYPE)
    {
        NVIC_SYSTEM_PRI2_REG =   (NVIC_SYSTEM_PRI1_REG & ~SVC_PRIORITY_MASK)|(Exception_Priority<<SVC_PRIORITY_BITS_POS) ;
    }

    else if (Exception_Num == EXCEPTION_DEBUG_MONITOR_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG =   (NVIC_SYSTEM_PRI1_REG & ~DEBUG_MONITOR_PRIORITY_MASK)|(Exception_Priority<<DEBUG_MONITOR_PRIORITY_BITS_POS) ;
    }


    else if (Exception_Num == EXCEPTION_PEND_SV_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG =   (NVIC_SYSTEM_PRI1_REG & ~PENDSV_PRIORITY_MASK)|(Exception_Priority<<PENDSV_PRIORITY_BITS_POS) ;
    }
    else if (Exception_Num == EXCEPTION_SYSTICK_TYPE)
    {
        NVIC_SYSTEM_PRI3_REG =   (NVIC_SYSTEM_PRI1_REG & ~SYSTICK_PRIORITY_MASK)|(Exception_Priority<<SYSTICK_PRIORITY_BITS_POS) ;
    }

}
