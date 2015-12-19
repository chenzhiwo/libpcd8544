#include<stdio.h>
#include<wiringPi.h>
#include"pcd8544.h"

//所使用的GPIO口，供各个函数使用。
char pcdPinCLK, pcdPinDIN, pcdPinDC, pcdPinCE, pcdPinRST; 

//像素缓冲区
char pcdBuffer[PCD_BYTE];

//记录芯片状态的结构体
pcdModedef pcdMode = {
	PCD_POWER_UP,
	PCD_ADDRESSING_HORIZONTAL,
	PCD_INSTRUCT_BASE
};


//初始化芯片到可用状态，若不能正常工作，请重新设置BIAS， Vop等参数。
void pcdInit(char pinCLK, char pinDIN, char pinDC, char pinCE, char pinRST)
{

	pcdGPIOInit(pinCLK, pinDIN, pinDC, pinCE, pinRST);
	pcdReset();
	pcdSetBIASMode(5);
	pcdSetVopMode(48);
	pcdSetTCMode(0);
	pcdSetPowerMode(PCD_POWER_UP);
	pcdSetDisplayMode(PCD_DISPLAY_NORMAL);
}

//初始化GPIO，参数为显示屏所使用的接口，使用wiringPi命名方式。若成功返回1,失败返回-1

int pcdGPIOInit(char pinCLK, char pinDIN, char pinDC, char pinCE, char pinRST)
{
	pcdPinCLK = pinCLK;
	pcdPinDIN = pinDIN;
	pcdPinDC  = pinDC;
	pcdPinCE  = pinCE;
	pcdPinRST = pinRST;

	if(wiringPiSetup() == -1)
	{
		return -1;
	}

	pinMode(pcdPinCLK, OUTPUT);
	pinMode(pcdPinDIN, OUTPUT);
	pinMode(pcdPinDC, OUTPUT);
	pinMode(pcdPinCE, OUTPUT);
	pinMode(pcdPinRST, OUTPUT);

#ifdef DEBUG_MESG
	printf("pcdGPIOInit(%d, %d, %d, %d, %d)\n", pcdPinCLK, pcdPinDIN, pcdPinDC, pcdPinCE, pcdPinRST);
#endif

	return 1;
}

//使能芯片的串行接口

void pcdEnable()
{
	digitalWrite(pcdPinCE, LOW);
	delayMicroseconds(1);

#ifdef DEBUG_MESG
	puts("pcdEnable");
#endif

}

//失能芯片的串行接口,但不是失能芯片。

void pcdDisable()
{
	digitalWrite(pcdPinCE, HIGH);
	delayMicroseconds(1);

#ifdef DEBUG_MESG
	puts("pcdDisable");
#endif

}

//复位芯片

void pcdReset()
{
	digitalWrite(pcdPinRST, LOW);
	delayMicroseconds(1);
	digitalWrite(pcdPinRST, HIGH);

#ifdef DEBUG_MESG
	puts("pcdReset");
#endif

}

//向芯片写入一字节数据

void pcdWriteByte(char dataIn)
{
	int offset = 0;

#ifdef DEBUG_MESG
	printf("pcdWriteByte:%x\n", dataIn);
#endif

	pcdEnable();
	for(offset = 0; offset < 8; offset++)
	{
		digitalWrite(pcdPinCLK, LOW);
		delayMicroseconds(1);
		if((dataIn & 0x80) != 0)
		{
			digitalWrite(pcdPinDIN, HIGH);
		}else
		{
			digitalWrite(pcdPinDIN, LOW);
		}
		digitalWrite(pcdPinCLK, HIGH);
		delayMicroseconds(1);
		dataIn = dataIn << 1;
	}
	digitalWrite(pcdPinCLK, LOW);
	pcdDisable();

}

//向芯片写入一字节的数据

void pcdWriteDataByte(char dataIn)
{
	digitalWrite(pcdPinDC, HIGH);
	pcdWriteByte(dataIn);
}

//向芯片写入特定长度的数据

void pcdWriteData(char dataInArry[], int length)
{
	int offset = 0;
	for(offset = 0; offset < length; offset++)
	{
		pcdWriteDataByte(dataInArry[offset]);
	}
}

//向芯片写入一字节的命令

void pcdWriteCommandByte(char dataIn)
{
	digitalWrite(pcdPinDC, LOW);
	pcdWriteByte(dataIn);
}


//向芯片写入特定长度的命令

void pcdWriteCommand(char dataInArry[], int length)
{
	int offset = 0;
	for(offset = 0; offset < length; offset++)
	{
		pcdWriteCommandByte(dataInArry[offset]);
	}

}

//设置芯片的工作状态，工作状态位储存在pcdMode

void pcdSetMode()
{

#ifdef DEBUG_MESG
	printf("pcdSetMode:%x\n", PCD_MODE_BASE | pcdMode.pcdPowerMode | pcdMode.pcdAddressingMode | pcdMode.pcdInstructMode);
#endif

	pcdWriteCommandByte(PCD_MODE_BASE | pcdMode.pcdPowerMode | pcdMode.pcdAddressingMode | pcdMode.pcdInstructMode);

}

//设置芯片是否进入掉电模式

void pcdSetPowerMode(enum pcdPowerModedef pcdPowerMode)
{
	pcdMode.pcdPowerMode = pcdPowerMode;
	pcdSetMode();
}

//设置芯片的寻址方式，参数为水平寻址或垂直寻址

void pcdSetAddressingMode(enum pcdAddressingModedef pcdAddressingMode)
{
	pcdMode.pcdAddressingMode = pcdAddressingMode;
	pcdSetMode();
}

//设置芯片当前指令集，参数为普通指令或扩展指令

void pcdSetInstructMode(enum pcdInstructModedef pcdInstructMode)
{
	pcdMode.pcdInstructMode = pcdInstructMode;
	pcdSetMode();
}

//设置显示模式，参数为全白，全黑，正常和反转模式

void pcdSetDisplayMode(enum pcdDisplayModedef pcdDisplayMode)
{
	pcdSetInstructMode(PCD_INSTRUCT_BASE);	
	pcdWriteCommandByte(PCD_DISPLAY_MODE_BASE | pcdDisplayMode);
}

//设置当前光标的X，Y坐标

void pcdSetXYAddress(char x, char y)
{
	if(x < 0 || x > 83 || y < 0 || y > 5)
	{
		puts("X/Y out of range");
		return;
	}
	pcdSetInstructMode(PCD_INSTRUCT_BASE);	
	pcdWriteCommandByte(PCD_X_BASE | x);
	pcdWriteCommandByte(PCD_Y_BASE | y);
}

//设置温度系数，参数范围为0-3

void pcdSetTCMode(char pcdTC)
{
	if(pcdTC < 0 || pcdTC > 3)
	{
		puts("TC out of range");
		return;
	}
	pcdSetInstructMode(PCD_INSTRUCT_EXT);	
	pcdWriteCommandByte(PCD_TC_BASE | pcdTC);
}

//设置偏置系统，参数范围为0-7

void pcdSetBIASMode(char pcdBIAS)
{
	if(pcdBIAS < 0 || pcdBIAS > 7)
	{
		puts("BIAS out of range");
		return;
	}
	pcdSetInstructMode(PCD_INSTRUCT_EXT);	
	pcdWriteCommandByte(PCD_BIAS_BASE | pcdBIAS);

}

//设置Vop电压，参数范围为0-127

void pcdSetVopMode(char pcdVop)
{
	if(pcdVop < 0 || pcdVop > 127)
	{
		puts("Vop out of range");
		return;
	}
	pcdSetInstructMode(PCD_INSTRUCT_EXT);	
	pcdWriteCommandByte(PCD_VOP_BASE | pcdVop);

}

//清除显示缓冲区以及芯片RAM

void pcdBufferClear()
{
	int offset = 0;
	for(offset = 0; offset < PCD_BYTE; offset++)
	{
		pcdBuffer[offset] = 0x00;
	}
}

//刷新芯片RAM,令显示缓冲区的数据传输到芯片RAM中

void pcdBufferFlush()
{
	pcdSetXYAddress(0, 0);
	pcdWriteData(pcdBuffer, PCD_BYTE);
}

//在缓冲区特定坐标绘制一个像素点，参数为X，Y坐标以及颜色

void pcdBufferDrawPixel(int x, int y, char color)
{
	if(x < 0 || x >= PCD_X || y < 0 || y >= PCD_Y)
	{
		puts("X/Y out of range.");
		return;
	}

	if(color == COLOR_NONE)
	{
		pcdBuffer[PCD_X * (y / 8) + x] = pcdBuffer[PCD_X * (y / 8) + x] & ~(0x01 << (y % 8));
	}
	else if(color == COLOR_BLACK)
	{
		pcdBuffer[PCD_X * (y / 8) + x] = pcdBuffer[PCD_X * (y / 8) + x] | (0x01 << (y % 8));
	}else if(color == COLOR_DEFAULT)
	{
	}

}

//在缓冲区的特定位置绘制一个给定的bitmap，参数为缓冲区的X，Y，bitmap宽高，前景背景色
//这个函数以pcdBufferDrawPixel为基础。同时y应可被8整除

void pcdBufferDrawBitMap(int x, int y, int w, int h, char bitMap[], char colorFG, char colorBG)
{
	int bx = 0, by = 0;
	if(x < 0 || x >= PCD_X || y < 0 || y >= PCD_Y)
	{
		puts("X/Y out of range.");
		return;
	}
	if((x + w) > PCD_X || (y + h) > PCD_Y)
	{
		puts("H/W out of range.");
		return;
	}

	for(by = 0; by < h; by++)
	{
		for(bx = 0; bx < w; bx++)
		{
			if((bitMap[(by / 8) * w + bx] & (0x01 << (by % 8))) == 0)
			{
				pcdBufferDrawPixel(x + bx, y + by, colorBG);
			}
			else
			{
				pcdBufferDrawPixel(x + bx, y + by, colorFG);
			}

		}
	}

}

//一个位图绘制函数，可以直接使用0b11110110这样的二进制格式来绘制位图，方便直接做图
//其它与pcdBufferDrawBitMap相同
void pcdBufferDrawBitMapBin(int x, int y, int w, int h, char bitMap[], char colorFG, char colorBG)
{
	int bx = 0, by = 0, patch = 0;

	if(x < 0 || x >= PCD_X || y < 0 || y >= PCD_Y)
	{
		puts("X/Y out of range.");
		return;
	}
	if((x + w) > PCD_X || (y + h) > PCD_Y)
	{
		puts("H/W out of range.");
		return;
	}

	if((w % 8) != 0)
	{
		patch = 1;
	}

	for(bx = 0; bx < w; bx++)
	{
		for(by = 0; by < h; by++)
		{
			if((bitMap[by * ((w / 8) + patch) + (bx / 8)] & (0x80 >> (bx % 8))) == 0)
			{
				pcdBufferDrawPixel(x + bx, y + by, colorBG);
			}
			else
			{
				pcdBufferDrawPixel(x + bx, y + by, colorFG);
			}
		}
	}

}
