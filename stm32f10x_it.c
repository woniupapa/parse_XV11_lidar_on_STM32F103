/* 包含头文件 ----------------------------------------------------------------*/
#include "includes.h"

/* 变量定义 ------------------------------------------------------------------*/

/* 函数定义 ------------------------------------------------------------------*/
//----------------------------------------------------------------------------//
//函数功能：不可屏蔽中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void NMI_Handler(void)
{
}

//----------------------------------------------------------------------------//
//函数功能：硬Fault中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void HardFault_Handler(void)
{
	while (1)
	{
	}
}

//----------------------------------------------------------------------------//
//函数功能：Memory Management中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void MemManage_Handler(void)
{
	while (1)
	{
	}
}

//----------------------------------------------------------------------------//
//函数功能：总线Fault中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void BusFault_Handler(void)
{
	while (1)
	{
	}
}

//----------------------------------------------------------------------------//
//函数功能：用法Fault中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void UsageFault_Handler(void)
{
	while (1)
	{
	}
}

//----------------------------------------------------------------------------//
//函数功能：SV Call中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void SVC_Handler(void)
{
}

//----------------------------------------------------------------------------//
//函数功能：Debug Monitor中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void DebugMon_Handler(void)
{
}

//----------------------------------------------------------------------------//
//函数功能：Pend SV中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void PendSV_Handler(void)
{
}

//----------------------------------------------------------------------------//
//函数功能：SysTick中断函数
//入口参数：无
//出口参数：无
//最后修改：2016.4.18
//备注：
//----------------------------------------------------------------------------//
void SysTick_Handler(void)
{
}

//int test[22] = {0};//for debug
//----------------------------------------------------------------------------//
//函数功能：USART2中断函数
//入口参数：无
//出口参数：无
//最后修改：2017.2.3
//备注：
//----------------------------------------------------------------------------//
void USART2_IRQHandler(void)
{ 
}

//----------------------------------------------------------------------------//
//函数功能：TIM2中断函数
//入口参数：无
//出口参数：无
//最后修改：2017.2.3
//备注：
//----------------------------------------------------------------------------//
void TIM2_IRQHandler(void)
{
	
}
//----------------------------------------------------------------------------//
//函数功能：USART1中断函数
//入口参数：无
//出口参数：无
//最后修改：2017.2.3
//备注：
//----------------------------------------------------------------------------//
void USART1_IRQHandler(void)
{ 
	if (USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET)
	{
		/************************************************************  
        环形队列  
        ************************************************************/        
		USART_ClearFlag(USART1, USART_IT_RXNE);//清除接收标志位
		raderReceiveQueue[raderReceiveCnt] = USART_ReceiveData(USART1);
		/************************************************************  
        单向队列  
        ************************************************************/        
		for(u8 i = 0; i < 21; i++)
		{
			raderReceiveQueue[i] = raderReceiveQueue[i + 1];
		}
		raderReceiveQueue[21] = USART_ReceiveData(USART1);		
		if (raderReceiveQueue[0] == 0xfa)
		{			
			int chk32 = 0;
			int checknum = 0;
			for (u8 i = 0; i < 10; i++)
			{
				int d = raderReceiveQueue[2 * i] + (raderReceiveQueue[2 * i + 1] << 8);
				chk32 = (chk32 << 1) + d;
			}
			chk32 = (chk32 & 0x7FFF) + (chk32 >> 15);
			chk32 = chk32 & 0x7FFF;
			checknum = (raderReceiveQueue[21] << 8) + raderReceiveQueue[20];
			if (checknum == chk32)//校验成功
			{
				for (u8 i = 0; i < 22; i++)
				{
					raderReceiveBuffer[i] = raderReceiveQueue[i];
				}
				raderDataCorrectFlag = SET;				
			}
		}	
	}
}