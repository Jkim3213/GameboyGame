#ifndef LIB_H_
#define LIB_H_
#include "marios/marios.h"
#include <stdio.h>
#include <stdlib.h>

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
#define MC111 DRED | DGREEN | DBLUE//grey
#define MC222  RED |  GREEN | BLUE //white
#define MC100 DRED |      0 |     0//dark red
#define MC010    0 | DGREEN |     0//dark green 
#define MC001    0 |      0 | DBLUE//dark blue 
#define MC200  RED |      0 |     0//red 
#define MC020    0 |  GREEN |     0//green 
#define MC002    0 |      0 |  BLUE//blue 
#define MC110 DRED | DGREEN |     0//dark yellow
#define MC101 DRED |      0 | DBLUE//dark magenta
#define MC011    0 | DGREEN | DBLUE//dark cyan
#define MC220  RED |  GREEN |     0//yellow
#define MC202  RED |      0 |  BLUE//magenta
#define MC022    0 |  GREEN |  BLUE//cyan
#define MC210  RED | DGREEN |     0//orange
#define MC201  RED |      0 | DBLUE//unused pink
#define MC120 DRED |  GREEN |     0//unused lime
#define MC021    0 |  GREEN | DBLUE//unused pastel green
#define MC102 DRED |      0 |  BLUE//pastel purple
#define MC012    0 | DGREEN |  BLUE//pastel blue
#define MC211  RED | DGREEN | DBLUE//unused peach
#define MC121 DRED |  GREEN | DBLUE//unused pale green
#define MC112 DRED | DGREEN |  BLUE//pastel indigo
#define MC221  RED |  GREEN | DBLUE//unused pastel yellow
#define MC212  RED | DGREEN |  BLUE//pink
#define MC122 DRED |  GREEN |  BLUE//unused pastel cyan



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

#define WOLF1(color, row, col) {1, color, row, col, 0}
#define ADJPOS(pos, length) ((pos) - (length)/2)
#define wsize 4
#define MARIO_WIDTH 24
#define MARIO_HEIGHT 32

typedef struct WOLF
{
	unsigned int speed;
	unsigned short color;
	//unsigned short health;//directly related to size
	//unsigned short spawnType;//0 - normal. 1 - rushed start. 2 - airborne
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
	unsigned int laserLength;
} LASER;

extern unsigned int lCD;//the constant value that laserCoolDown refreshes to
extern unsigned int wolfRate;//8 wolves a sec

extern unsigned int seed;

extern int playerHealth;


extern unsigned short *videoBuffer;
extern int gameState;
extern unsigned int gameTime;
// Prototypes
void init();
void populateWolves(WOLF wolves[], int size);
void shootLaser();//Shoots current color and resets to black sheep
void updateLaser();
void updateSheep();//draws sheep
void getMarioImage(unsigned short color, const u16 **marioColor);
void updateColor(int color);//updates color value

//void spawnWolf(int speed, short color, short health, short spawnType);
void createWolf();//actually creates the wolf
void drawPoints(unsigned int row, unsigned int col, 
				unsigned short color, unsigned int points, const u16 *wolfColor);
void updateWolves();
void delay(int n);
void waitForVblank();
void setPixel(int row, int col, unsigned short color);
void drawRect(int row, int col, int height, int width, unsigned short color);
void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char str[], unsigned short color);
void drawImage(int row, int col, int width, int height, const unsigned short* image);
void drawImageFlippedLR(int row, int col, int width, int height, const u16* image);
void fillScreen(volatile u16 color);
void updatePipe();
void updateScore();
void gameOver();
void updateCloud();
void updateHealth();
void spawnWolf();
void startGame();
void clearLaser();
#endif
