/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		�ж��ļ�
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/



#include "isr.h"
extern struct ParameterStruct Parameter;
extern struct InfoStruct Info;
extern struct FlagStruct Flag;
void PIT_CH1_IRQHandler(void)
{
    PIT_FlAG_CLR(pit1);

    
}

void IRQ_IRQHandler(void)
{
    CLEAR_IRQ_FLAG;
    
}

void KBI0_IRQHandler(void)
{       
    CLEAN_KBI0_FLAG;
    if(!gpio_get(D5)){
      if(!Flag.start)Flag.start++;
      else if(Flag.start==128){
        Flag.start=0;
        Flag.FlagMotor*=-1;
      }
    }
    
   if(!gpio_get(D2)){
      if(Flag.FlagMotor==-1) 
        Flag.FlagMotor=1;
      else
        if(Parameter.ExpectSpeed==0)
          Parameter.ExpectSpeed=Info.ExpectSpeed;
        else 
          Flag.FlagMotor=-1;
   }else if(!gpio_get(A3)){
     if(Info.dip[1] && Info.dip[2]);
     else if(!Info.dip[1] && Info.dip[2]);
     else if(!Info.dip[1] && !Info.dip[2]);
     else if(Info.dip[1] && !Info.dip[2]);

   }else if(!gpio_get(A0)){
     if(Info.dip[1] && Info.dip[2])Parameter.D_Balance-=3;
     else if(!Info.dip[1] && Info.dip[2])Info.ExpectSpeed-=5;
     else if(!Info.dip[1] && !Info.dip[2])Parameter.I_Speed-=1;
     else if(Info.dip[1] && !Info.dip[2])Parameter.D_Turn-=1;
   

   }else if(!gpio_get(C7)){
     if(Info.dip[1] && Info.dip[2])Parameter.D_Balance+=3;
     else if(!Info.dip[1] && Info. dip[2])Info.ExpectSpeed+=5;
     else if(!Info.dip[1] && !Info.dip[2])Parameter.I_Speed+=1;
     else if(Info.dip[1] && !Info.dip[2])Parameter.D_Turn+=1;
  
   }else if(!gpio_get(A2)){
     if(Info.dip[1] && Info.dip[2])Info.ExpectAD-=50;
     else if(!Info.dip[1] && Info.dip[2])Info.acc_z_offset-=10;
     else if(!Info.dip[1] && !Info.dip[2])Parameter.P_Speed-=1;
     else if(Info.dip[1] && !Info.dip[2])Parameter.P_Turn-=1;

    
   }else if(!gpio_get(A1)){
     if(Info.dip[1] && Info.dip[2])Info.ExpectAD+=50;
     else if(!Info.dip[1] && Info.dip[2])Info.acc_z_offset+=10;
     else if(!Info.dip[1] && !Info.dip[2])Parameter.P_Speed+=1;
     else if(Info.dip[1] && !Info.dip[2])Parameter.P_Turn+=1;
     
   }
}

void KBI1_IRQHandler(void)
{
    CLEAN_KBI1_FLAG;
    if(gpio_get(F3))Parameter.ExpectSpeed=Info.ExpectSpeed,gpio_turn(D1);           //C F3//270
      
    else if(gpio_get(F2))Parameter.ExpectSpeed=0,gpio_turn(D0);       //D F2
    
    else if(gpio_get(E2))Flag.TurnEnable*=-1,gpio_turn(H6);           //B E2
      
    else if(gpio_get(E3))Flag.FlagMotor*=-1,gpio_turn(H7);            //A E3
   
}

//A motor



/*
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ���������ڶ�ʱ�� ͨ��0���ж�
void PIT_CH0_IRQHandler(void)
{
    ;
}
�ǵý����жϺ������־λ

FTMRE_IRQHandler      
PMC_IRQHandler        
IRQ_IRQHandler        
I2C0_IRQHandler       
I2C1_IRQHandler       
SPI0_IRQHandler       
SPI1_IRQHandler       
UART0_IRQHandler 
UART1_IRQHandler 
UART2_IRQHandler 
ADC0_IRQHandler       
ACMP0_IRQHandler      
FTM0_IRQHandler       
FTM1_IRQHandler       
FTM2_IRQHandler       
RTC_IRQHandler        
ACMP1_IRQHandler      
PIT_CH0_IRQHandler    
PIT_CH1_IRQHandler    
KBI0_IRQHandler       
KBI1_IRQHandler       
Reserved26_IRQHandler 
ICS_IRQHandler        
WDG_IRQHandler        
PWT_IRQHandler        
MSCAN_Rx_IRQHandler   
MSCAN_Tx_IRQHandler   
*/



