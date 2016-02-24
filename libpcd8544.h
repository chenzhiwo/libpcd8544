#ifndef PCD8544_H
#define PCD8544_H

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

enum Color {
	COLOR_NONE = 0,
	COLOR_ON = 1,
	COLOR_DEFAULT = 2,
};

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

typedef unsigned char uchar;

void pcdInit(uchar pinCLK, uchar pinDIN, uchar pinDC, uchar pinCE, uchar pinRST);
int pcdGPIOInit(uchar pinCLK, uchar pinDIN, uchar pinDC, uchar pinCE, uchar pinRST);
void pcdEnable();
void pcdDisable();
void pcdReset();
void pcdWriteByte(uchar dataIn);
void pcdWriteDataByte(uchar dataIn);
void pcdWriteData(uchar dataInArry[], int length);
void pcdWriteCommandByte(uchar dataIn);
void pcdWriteCommand(uchar dataInArry[], int length);
void pcdSetMode();
void pcdSetPowerMode(enum pcdPowerModedef pcdPowerMode);
void pcdSetAddressingMode(enum pcdAddressingModedef pcdAddressingMode);
void pcdSetInstructMode(enum pcdInstructModedef pcdInstructMode);
void pcdSetDisplayMode(enum pcdDisplayModedef pcdDisplayMode);
void pcdSetXYAddress(uchar x, uchar y);
void pcdSetTCMode(uchar pcdTC);
void pcdSetBIASMode(uchar pcdBIAS);
void pcdSetVopMode(uchar pcdVop);
void pcdBufferClear();
void pcdBufferFlush();
void pcdBufferDrawPixel(int x, int y, uchar color);
void pcdBufferDrawBitMap(int x, int y, int w, int h, uchar bitMap[], uchar colorFG, uchar colorBG);
void pcdBufferDrawBitMapBin(int x, int y, int w, int h, uchar bitMap[], uchar colorFG, uchar colorBG);



#endif
