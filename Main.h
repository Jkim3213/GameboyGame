#ifndef MAIN_H_
#define MAIN_H_
#include "marios.h"

typedef unsigned int u32;
typedef unsigned short u16;

#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3

#define SCANLINECOUNTER *(volatile unsigned short *) 0x4000006

#define SCREENHEIGHT 149

#define BG2_ENABLE (1<<10)
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define DRED COLOR(15, 0, 0)
#define DGREEN COLOR(0, 15, 0)
#define DBLUE COLOR(0, 0, 15)
#define YELLOW COLOR(31, 31,0)
#define WHITE COLOR(31, 31, 31)
#define BGCOLOR 0x7e4b
#define OFFSET(r, c, rowlen) ((r)*(rowlen)+(c))
#define BLACK 0

//if current color = MC000 draw image m000
#define MC000 BLACK
#define MC111 DRED | DGREEN | DBLUE
#define MC222  RED |  GREEN | BLUE
#define MC100 DRED |      0 |     0
#define MC010    0 | DGREEN |     0
#define MC001    0 |      0 | DBLUE
#define MC200  RED |      0 |     0
#define MC020    0 |  GREEN |     0
#define MC002    0 |      0 |  BLUE
#define MC110 DRED | DGREEN |     0
#define MC101 DRED |      0 | DBLUE
#define MC011    0 | DGREEN | DBLUE
#define MC220  RED |  GREEN |     0
#define MC202  RED |      0 |  BLUE
#define MC022    0 |  GREEN |  BLUE
#define MC210  RED | DGREEN |     0
#define MC201  RED |      0 | DBLUE
#define MC120 DRED |  GREEN |     0
#define MC021    0 |  GREEN | DBLUE
#define MC102 DRED |      0 |  BLUE
#define MC012    0 | DGREEN |  BLUE
#define MC211  RED | DGREEN | DBLUE
#define MC121 DRED |  GREEN | DBLUE
#define MC112 DRED | DGREEN |  BLUE
#define MC221  RED |  GREEN | DBLUE
#define MC212  RED | DGREEN |  BLUE
#define MC122 DRED |  GREEN |  BLUE



extern const unsigned char fontdata_6x8[12288];

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	        (1<<2)
#define BUTTON_START	        (1<<3)
#define BUTTON_RIGHT	        (1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130

/* DMA */

#define REG_DMA0SAD         *(volatile u32*)0x40000B0 		// source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(volatile u32*)0x40000BC 		// source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(volatile u32*)0x40000C8 		// source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(volatile u32*)0x40000D4 		// source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register


typedef struct
{
	const volatile void *src;
	volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)


#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define WOLF1(color, row, col) {1, color, 1, 1, row, col, 0}
#define ADJPOS(pos, length) ((pos) - (length)/2)

typedef struct WOLF
{
	unsigned int speed;
	unsigned short color;
	unsigned short health;//directly related to size
	unsigned short spawnType;//0 - normal. 1 - rushed start. 2 - airborne
	unsigned int row;
	volatile unsigned int col;
	unsigned short alive;//1 or 0

} WOLF;

typedef struct LASER
{
	unsigned short exists;
	unsigned short color;
	unsigned int row;
	volatile unsigned int col;
	unsigned int speed;
} LASER;

const unsigned int shpRow = 88;//describes center of sheep
const unsigned int shpCol = 40;//describes center of sheep
const unsigned int shpWidth = MARIO_WIDTH;
const unsigned int shpHeight = MARIO_HEIGHT;
const unsigned int shpDeathCol = 50;//shpCol + shpWidth/2
const unsigned int wlfRow = 88;
const unsigned int wlfCol = 239;
const unsigned int dwlfWidth = 25;
const unsigned int dwlfHeight = 20;
const unsigned int gFactor = 5; //growthfactor for wolves
const unsigned int lCD = 30;//the constant value that laserCoolDown refreshes to
const unsigned int laserSpeed = 10;
const unsigned int laserLength = 10;
int maxWolves;

int shpAdjRow;
int shpAdjCol;
int laserGirth;


unsigned short *videoBuffer = (unsigned short *)0x6000000;
extern unsigned short currentColor;//store color of sheep

// Prototypes
void populateWolves(WOLF wolves[], int size);
void shootLaser();//Shoots current color and resets to black sheep
void updateLaser();
void updateSheep();//draws sheep
void updateColor(int color);//updates color value
void setPixel(int row, int col, unsigned short color);
void drawRect(int row, int col, int height, int width, unsigned short color);
//void spawnWolf(int speed, short color, short health, short spawnType);
void createWolf();//actually creates the wolf
void updateWolves();
void delay(int n);
void waitForVblank();
void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char str[], unsigned short color);
void drawImage(int row, int col, int width, int height, const unsigned short* image);




#endif
