#include "stm32f10x.h"                  // Device header
#include "INA3221.h"
#include "MyI2C.h"

void INA3221_Init(u8  Channal_HexNum)//该Num填开启通道的十六进制数，如开启通道一则填4，开启通道1和2，填6
{
	u16 Config = (AvgSample<<9)|(VBUS_CT<<6)|(VSH_CT<<3)|Mode;
	MyI2C_Init();
	INA3221_WriteHalfWord(ConfigRegisterAdress , (Channal_HexNum<<12)|Config);
}

void INA3221_SetWorn_CriticalRegister(u8 Channal ,u16 Value)
{
	INA3221_WriteHalfWord(Channal, Value);
}

void INA3221_SetReadMask_EnableRegister(u16 Value)
{
	Value = (SCC1_3<<12)|(WEN<<11)|(CF1_3<<7)|(SF<<6)|(WF1_3<<3)|(PVF<<2)|(TCF<<1);
	INA3221_WriteHalfWord(Mask_Enable, Value);
}

u16 INA3221_ReadMask_EnableRegister(void)
{
	u16 Flag;
	Flag = INA3221_ReadHalfWord(Mask_Enable);
	return Flag;
}


void INA3221_GetSV_BV_Voltage(u8 Channal1 , float *Buff)
{
	u8 Channal2=Channal1;
	u16 Flag=0 ,Value1 , Value2 ;
	Channal2 = 2*Channal1;
	Channal1=2*Channal1-1;
	
	Flag = INA3221_ReadMask_EnableRegister();
	if((Flag&0x0001) == 1)
	{
		Value1 = INA3221_ReadHalfWord(Channal1);
		Value2 = INA3221_ReadHalfWord(Channal2);
		Buff[0] =  Value1*40/1000;
	  Buff[1] =  Value2*8;
	}

}

u16 INA3221_GetMFID(void)
{
	u16 temp=0;
	temp = INA3221_ReadHalfWord(MF_ID );
	return temp;
}

void INA3221_WriteHalfWord(u8 Adress, u16 data)
{
	uint8_t temp=0;
	MyI2C_Start();
	MyI2C_SendByte(SlaveAdress_W); 
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Adress);
	MyI2C_ReceiveAck();
	temp = (uint8_t)(data>>8); 
	MyI2C_SendByte(temp);
	MyI2C_ReceiveAck();	
	temp = (uint8_t)(data&0x00FF);
	MyI2C_SendByte(temp); 
	MyI2C_ReceiveAck();
	
	MyI2C_Stop();
}

s16 INA3221_ReadHalfWord(u8 Adress)
{
	s16 temp=0;
	
	MyI2C_Start();
	MyI2C_SendByte(SlaveAdress_W); 
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Adress);
	MyI2C_ReceiveAck();	
	MyI2C_Stop();
	
	MyI2C_Start();
	MyI2C_SendByte(SlaveAdress_R);
	MyI2C_ReceiveAck();	
	temp = MyI2C_ReceiveByte();
	MyI2C_SendAck(0);//等待16位数据接收完成
	temp = temp <<8;
	temp |=MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	return temp; 
}



