#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>
#include<time.h>
#include"pcd8544.h"
#include"gfx.h"
#include"bitmap.h"

#define PIN_CLK 21
#define PIN_DIN 22
#define PIN_DC 23
#define PIN_CE 24
#define PIN_RST 25

#define RANDNUMX (rand() / (RAND_MAX / (PCD_X - 17)))
#define RANDNUMY (rand() / (RAND_MAX / (PCD_Y - 17)))

int main(int argc, char *args[])
{
	pcdInit(PIN_CLK, PIN_DIN, PIN_DC, PIN_CE, PIN_RST);
	gfxInitStruct gfxInitStr = {pcdBufferFlush, pcdBufferClear, pcdBufferDrawPixel, pcdBufferDrawBitMap, pcdBufferDrawBitMapBin};
	gfxInit(gfxInitStr);
	srand((unsigned)time(NULL)); 
	gfxClear();
	gfxFlush();
	/*	while(1)
		{
		gfxDrawBitMapBin(RANDNUMX,RANDNUMY,16,16,logo16x16,COLOR_BLACK,COLOR_NONE);
		gfxFlush();
		delay(30);
		}*/

	pcdSetAddressingMode(PCD_ADDRESSING_VERTICAL);
	int i = 0;
	char c = 0x00;
	while(1)
	{
		for(c = 0x00; c < 0xff; c++)
		{
			pcdSetXYAddress(0,0);
			for(i = 0; i < PCD_BYTE; i++)
			{
				pcdWriteDataByte(c);
				delayMicroseconds(400);
			}
		}
	}

	return 0;
}
