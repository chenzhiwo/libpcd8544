#ifndef GFX_H
#define GFX_H
#include"color.h"

typedef struct gfxInitStruct{
	void (*HWFlushFunc)(void);
	void (*HWClearFunc)(void);
	void (*HWDrawPixelFunc)(int x, int y, char color);
	void (*HWDrawBitMapFunc)(int x, int y, int w, int h, char bitMap[], char colorFG, char colorBG);
	void (*HWDrawBitMapBinFunc)(int x, int y, int w, int h, char bitMap[], char colorFG, char colorBG);
} gfxInitStruct;

void (*gfxFlush)(void);
void (*gfxClear)(void);
void (*gfxDrawPixel)(int x, int y, char color);
void (*gfxDrawBitMap)(int x, int y, int w, int h, char bitMap[], char colorFG, char colorBG);
void (*gfxDrawBitMapBin)(int x, int y, int w, int h, char bitMap[], char colorFG, char colorBG);

void gfxInit(gfxInitStruct gfxInitStr);
void gfxPrintASCII5x8(int x, int y, char string[], char color);
void gfxDrawLine(int x0, int y0, int x1, int y1, char color);
void gfxDrawFastHLine(int x, int y, int w, char color);
void gfxDrawFastVLine(int x, int y, int h, char color);
void gfxDrawCircle(int x0, int y0, int r, char color);
void gfxDrawCircleHelper( int x0, int y0, int r, char cornername, char color);
void gfxDrawFillCircle(int x0, int y0, int r, char color);
void gfxDrawFillCircleHelper(int x0, int y0, int r, char cornername, int delta, char color);
void gfxDrawRect(int x, int y, int w, int h, char color);
void gfxDrawFillRect(int x, int y, int w, int h, char color);
void gfxDrawRoundRect(int x, int y, int w, int h, int r, char color);
void gfxDrawFillRoundRect(int x, int y, int w, int h, int r, char color);
void gfxDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, char color);
void gfxDrawFillTriangle ( int x0, int y0, int x1, int y1, int x2, int y2, char color);

#endif
