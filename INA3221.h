#ifndef __INA3221_H
#define __INA3221_H
#include "stm32f10x.h"                  // Device header


//寄存器地址
#define SlaveAdress_W          0x80
#define SlaveAdress_R          0x81

#define ConfigRegisterAdress   0x00
#define Channel_1_SVAdress     0x01
#define Channel_1_BVAdress     0x02
#define Channel_2_SVAdress     0x03
#define Channel_2_BVAdress     0x04
#define Channel_3_SVAdress     0x05
#define Channel_3_BVAdress     0x06

#define CritiAlert_Channel_1   0x07
#define WarnAlertChannel_1     0x08
#define CritiAlert_Channel_2   0x09
#define WarnAlertChannel_2     0x0A
#define CritiAlert_Channel_3   0x0B
#define WarnAlertChannel_3     0x0C

#define ShuntVolSum            0x0D
#define ShuntVolSum_Limit      0x0E
#define Mask_Enable            0x0F
#define PVUpper_Limit          0x10
#define PVLower_Limit          0x11
#define MF_ID                  0xFE
#define Die_ID                 0xFF

//ConfigRegister Configure
#define  AvgSample             0x00//平均采样数量
#define  VBUS_CT               0x04//VBUS转换时间
#define  VSH_CT                0x04//VS转换时间
#define  Mode                  0x07//模式选择

//Mask_EnableRegister Configure，此处配置为默认状态
#define  SCC1_3                0x0
#define	 WEN                   0x0
#define	 CF1_3                 0x0
#define	 SF                    0x0
#define	 WF1_3                 0x0
#define	 PF                    0x0
#define	 PVF                   0x0
#define	 TCF                   0x1               

//CRVF不用设置

void INA3221_Init(u8 Channal_HexNum);
void INA3221_GetSV_BV_Voltage(u8 Channal1 , float *Buff);
u16  INA3221_GetMFID(void);

void INA3221_SetWorn_CriticalRegister(u8 Channal ,u16 Value);
void INA3221_SetReadMask_EnableRegister(u16 Value);
u16  INA3221_ReadMask_EnableRegister(void);

s16  INA3221_ReadHalfWord(u8 Adress);
void INA3221_WriteHalfWord(u8 Adress, u16 data);

#endif
