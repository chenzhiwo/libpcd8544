#ifndef PCD8544_H
#define PCD8544_H
#include"color.h"

#define PCD_X 84
#define PCD_Y 48
#define PCD_BYTE (PCD_X * PCD_Y / 8)

#define PCD_MODE_BASE 0x20
#define PCD_DISPLAY_MODE_BASE 0x8
#define PCD_X_BASE 0x80
#define PCD_Y_BASE 0x40
#define PCD_TC_BASE 0x04
#define PCD_BIAS_BASE 0x10
#define PCD_VOP_BASE 0x80

enum pcdPowerModedef{
	PCD_POWER_UP = 0x00,
	PCD_POWER_DOWN = 0x04
};

enum pcdAddressingModedef{
	PCD_ADDRESSING_HORIZONTAL = 0x00,
	PCD_ADDRESSING_VERTICAL = 0x02
};

enum pcdInstructModedef{
	PCD_INSTRUCT_BASE = 0x00,
	PCD_INSTRUCT_EXT = 0x01
};

enum pcdDisplayModedef{
	PCD_DISPLAY_BLANK = 0x00,
	PCD_DISPLAY_NORMAL = 0x04,
	PCD_DISPLAY_ALLON = 0x01,
	PCD_DISPLAY_INVERSE = 0x05,
};

enum pcdColor{
	PCD_NONE = 0,
	PCD_BLACK = 1,
	PCD_DEFAULT = 2,
};

typedef struct{
	enum pcdPowerModedef pcdPowerMode;
	enum pcdAddressingModedef pcdAddressingMode;
	enum pcdInstructModedef pcdInstructMode;
} pcdModedef;


void pcdInit(char pinCLK, char pinDIN, char pinDC, char pinCE, char pinRST);
int pcdGPIOInit(char pinCLK, char pinDIN, char pinDC, char pinCE, char pinRST);
void pcdEnable();
void pcdDisable();
void pcdReset();
void pcdWriteByte(char dataIn);
void pcdWriteDataByte(char dataIn);
void pcdWriteData(char dataInArry[], int length);
void pcdWriteCommandByte(char dataIn);
void pcdWriteCommand(char dataInArry[], int length);
void pcdSetMode();
void pcdSetPowerMode(enum pcdPowerModedef pcdPowerMode);
void pcdSetAddressingMode(enum pcdAddressingModedef pcdAddressingMode);
void pcdSetInstructMode(enum pcdInstructModedef pcdInstructMode);
void pcdSetDisplayMode(enum pcdDisplayModedef pcdDisplayMode);
void pcdSetXYAddress(char x, char y);
void pcdSetTCMode(char pcdTC);
void pcdSetBIASMode(char pcdBIAS);
void pcdSetVopMode(char pcdVop);
void pcdBufferClear();
void pcdBufferFlush();
void pcdBufferDrawPixel(int x, int y, char color);
void pcdBufferDrawBitMap(int x, int y, int w, int h, char bitMap[], char colorFG, char colorBG);
void pcdBufferDrawBitMapBin(int x, int y, int w, int h, char bitMap[], char colorFG, char colorBG);



#endif
