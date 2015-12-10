
#include <stdlib.h>
#include <stdio.h>
#include "pyinclude.h"
/*
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
*/
typedef unsigned long ulong; 
typedef unsigned char uchar;
typedef unsigned int  uint;
///*12864应用指令*/
#define CLEAR_SCREEN 0x01 //清屏指令：清屏且AC值为00H
#define AC_INIT 0x02 //将AC设置为00H。且游标移到原点位置
#define CURSE_ADD 0x06 //设定游标移到方向及图像整体移动方向（默认游标右移，图像整体不动）
#define FUN_MODE 0x30 //工作模式：8位基本指令集
#define DISPLAY_ON 0x0c //显示开,显示游标，且游标位置反白
#define DISPLAY_OFF 0x08 //显示关
#define CURSE_DIR 0x14 //游标向右移动:AC=AC+1
#define SET_CG_AC 0x40 //设置AC，范围为：00H~3FH
#define SET_DD_AC 0x80
///*初始化设置*/
#define RS sunxi_gpio_set_cfgpin(PD9,OUTPUT)
#define RW sunxi_gpio_set_cfgpin(PD10,OUTPUT)
#define EN sunxi_gpio_set_cfgpin(PD11,OUTPUT)
#define PSB sunxi_gpio_set_cfgpin(PD12,OUTPUT)
#define RST sunxi_gpio_set_cfgpin(PD13,OUTPUT)
#define DataPort_PD1	sunxi_gpio_set_cfgpin(PD1,OUTPUT)
#define DataPort_PD2	sunxi_gpio_set_cfgpin(PD2,OUTPUT)
#define DataPort_PD3	sunxi_gpio_set_cfgpin(PD3,OUTPUT)
#define DataPort_PD4	sunxi_gpio_set_cfgpin(PD4,OUTPUT)
#define DataPort_PD5	sunxi_gpio_set_cfgpin(PD5,OUTPUT)
#define DataPort_PD6	sunxi_gpio_set_cfgpin(PD6,OUTPUT)
#define DataPort_PD7 	sunxi_gpio_set_cfgpin(PD7,OUTPUT)
#define DataPort_PD8	sunxi_gpio_set_cfgpin(PD8,OUTPUT)
///*接口设置*/
#define RS_CLR sunxi_gpio_output(PD9,LOW) //RS置低
#define RS_SET sunxi_gpio_output(PD9,HIGH) //RS置高
#define RW_CLR sunxi_gpio_output(PD10,LOW) //RW置低
#define RW_SET sunxi_gpio_output(PD10,HIGH) //RW置高
#define EN_CLR sunxi_gpio_output(PD11,LOW) //E置低
#define EN_SET sunxi_gpio_output(PD11,HIGH) //E置高
#define PSB_CLR sunxi_gpio_output(PD12,LOW) //PSB置低，串口方式
#define PSB_SET sunxi_gpio_output(PD12,HIGH) //PSB置高，并口方式
#define RST_CLR sunxi_gpio_output(PD13,LOW) //RST置低
#define RST_SET sunxi_gpio_output(PD13,HIGH) //RST置高
#define DataPort_PD1_H	sunxi_gpio_output(PD1,HIGH)
#define DataPort_PD1_L	sunxi_gpio_output(PD1,LOW)
#define DataPort_PD2_H	sunxi_gpio_output(PD2,HIGH)
#define DataPort_PD2_L	sunxi_gpio_output(PD2,LOW)
#define DataPort_PD3_H	sunxi_gpio_output(PD3,HIGH)
#define DataPort_PD3_L	sunxi_gpio_output(PD3,LOW)
#define DataPort_PD4_H	sunxi_gpio_output(PD4,HIGH)
#define DataPort_PD4_L	sunxi_gpio_output(PD4,LOW)
#define DataPort_PD5_H	sunxi_gpio_output(PD5,HIGH)
#define DataPort_PD5_L	sunxi_gpio_output(PD5,LOW)
#define DataPort_PD6_H	sunxi_gpio_output(PD6,HIGH)
#define DataPort_PD6_L	sunxi_gpio_output(PD6,LOW)
#define DataPort_PD7_H	sunxi_gpio_output(PD7,HIGH)
#define DataPort_PD7_L	sunxi_gpio_output(PD7,LOW)
#define DataPort_PD8_H	sunxi_gpio_output(PD8,HIGH)
#define DataPort_PD8_L	sunxi_gpio_output(PD8,LOW)
//*************************************************************************
//数据显示函数
//*************************************************************************/
void date_gpio(char dat)
{
	int nbit;
	
	nbit =0x01;
	
	if(dat&nbit){
	DataPort_PD1_H;
	}
	else{
	DataPort_PD1_L;
	}
	nbit<<1;
	if(dat&nbit){
	DataPort_PD2_H;
	}
	else{
	DataPort_PD2_L;
	}
	nbit<<1;
	if(dat&nbit){
		DataPort_PD3_H;
		}
		else{
		DataPort_PD3_L;
		}
	nbit<<1;
	if(dat&nbit){
	DataPort_PD4_H;
		}
		else{
		DataPort_PD4_L;
		}
	nbit<<1;
	if(dat&nbit){
	DataPort_PD5_H;
		}	
		else{
		DataPort_PD5_L;
		}

	nbit<<1;
	if(dat&nbit){
	DataPort_PD6_H;
		}
		else{
		DataPort_PD6_L;
		}
	nbit<<1;
	if(dat&nbit){
	DataPort_PD7_H;
		}
		else{
		DataPort_PD7_L;
//		}
	}
	nbit<<1;
	if(dat&nbit){
	DataPort_PD8_H;
		}
		else{
		DataPort_PD8_L;
//		}
	}
	nbit=0x01; //归零
//	}
}

//*************************************************************************
// 系统时钟初始化
//*************************************************************************
/*void Clock_Init()
{
uchar i;
BCSCTL1&=~XT2OFF; //打开XT振荡器
BCSCTL2|=SELM1+SELS; //MCLK为8MHZ，SMCLK为8MHZ
do{
IFG1&=~OFIFG; //清除震荡标志
for(i=0;i<100;i++)
_NOP(); //延时等待
}
while((IFG1&OFIFG)!=0); //如果标志为1，则继续循环等待
IFG1&=~OFIFG; 
}
*/
//*************************************************************************
// MSP430内部看门狗初始化
//*************************************************************************
/*void WDT_Init()
{
WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
}
*/
//*************************************************************************
// 初始化IO口子程序
//*************************************************************************/
void Port_init(void)
{
RS;
RW;
EN;
PSB;
RST;
DataPort_PD1;
DataPort_PD2;
DataPort_PD3;
DataPort_PD4;
DataPort_PD5;
DataPort_PD6;
DataPort_PD7;
DataPort_PD8;
PSB_SET; //液晶并口方式
RST_SET; //复位脚RST置高
}
/*void Port_init()
{
P4SEL = 0x00;
P4DIR = 0xFF;
P5SEL = 0x00;
P5DIR|= BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
PSB_SET; //液晶并口方式
RST_SET; //复位脚RST置高
}
*/

//***********************************************************************
// 显示屏命令写入函数
//***********************************************************************/
void LCD_write_com(unsigned char com)
{
RS_CLR;
RW_CLR;
EN_SET;
date_gpio(com);
delay_ms(5);
EN_CLR;
}
//***********************************************************************
// 显示屏数据写入函数
//***********************************************************************/
void LCD_write_data(unsigned char data)
{
RS_SET;
RW_CLR;
EN_SET;
date_gpio(data);
delay_ms(5);
EN_CLR;
}
//***********************************************************************
// 显示屏清空显示
//***********************************************************************
void LCD_clear(void) 
{
LCD_write_com(0x01);
delay_ms(5);
}
//***********************************************************************
//函数名称：DisplayCgrom(uchar hz)显示CGROM里的汉字
//***********************************************************************
void DisplayCgrom(uchar addr,uchar *hz)
{
LCD_write_com(addr);
delay_ms(5);
while(*hz != '\0')
{
LCD_write_data(*hz);
hz++;
delay_ms(5);
}
} 
//****************************************************************
//函数名称：Display()显示测试结果
//****************************************************************
void Display(void)
{
DisplayCgrom(0x80,"酒欢迎你");
DisplayCgrom(0x88,"行");
DisplayCgrom(0x98,"电话 ");
}
//***********************************************************************
// 显示屏初始化函数
//***********************************************************************
void LCD_init(void) 
{
LCD_write_com(FUN_MODE); //显示模式设置
delay_ms(5);
LCD_write_com(FUN_MODE); //显示模式设置
delay_ms(5);
LCD_write_com(DISPLAY_ON); //显示开
delay_ms(5);
LCD_write_com(CLEAR_SCREEN); //清屏
delay_ms(5);
}
//***********************************************************************
// 主程序
//***********************************************************************
void main(void)
{
//WDT_Init(); //看门狗设置
//Clock_Init(); //系统时钟设置
Port_init(); //系统初始化，设置IO口属性
delay_ms(100); //延时100ms
LCD_init(); //液晶参数初始化设置
LCD_clear(); //清屏
if(SETUP_OK!=sunxi_gpio_init())
{
        printf("Failed to initialize GPIO\n");
        return -1;
}else{
	printf("dev is ok");
	}
while(1)
{
printf("dev is ok");
Display(); //显示汉字
}
}
