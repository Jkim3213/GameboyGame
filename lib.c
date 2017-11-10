#include "lib.h"

unsigned int shpRow;
unsigned int shpCol;
unsigned int shpWidth;
unsigned int shpHeight;
unsigned int shpDeathCol;
unsigned int wlfRow;
unsigned int wlfCol;
unsigned int dwlfWidth;
unsigned int dwlfHeight;
unsigned int gFactor;
unsigned int lCD;
unsigned int wolfRate;
unsigned int laserSpeed;
unsigned int laserLength;
unsigned short currentColor;


int shpAdjRow;
int shpAdjCol;
int laserGirth;
int laserRow;
int laserCol;
unsigned int wRectRow;
int score;
int scoreMulti;
unsigned int seed;
unsigned short *videoBuffer;
WOLF wolves[wsize];
int playerHealth;

void init()
{
	shpRow = 96;//describes center of sheep
	shpCol = 40;//describes center of sheep
	shpWidth = MARIO_WIDTH;
	shpHeight = MARIO_HEIGHT;
	shpDeathCol = 50;//shpCol + shpWidth/2
	wlfRow = 96;
	wlfCol = 239;
	dwlfWidth = MARIO_WIDTH;
	dwlfHeight = MARIO_HEIGHT;
	gFactor = 5; //growthfactor for wolves
	lCD = 30;//the constant value that laserCoolDown refreshes to
	wolfRate = 180;
	laserSpeed = 10;
	laserLength = 10;

	shpAdjRow = ADJPOS(shpRow, shpHeight);
	shpAdjCol = ADJPOS(shpCol, shpWidth);
	//maxWolves = 3;
	laserGirth = shpHeight/2;
	laserRow = shpRow - laserGirth/2;
   	laserCol = shpCol + shpWidth/2;
	wRectRow = ADJPOS(wlfRow, dwlfHeight);
	score = 0;
	scoreMulti = 0;
	videoBuffer = (unsigned short *)0x6000000;
	//marioColor = m000;
	playerHealth = 3;
	populateWolves(wolves, wsize);
}

void populateWolves(WOLF wolves[], int size)
{
	
	for(int i = 0; i < size; i++)
	{
		WOLF wolf = WOLF1(DBLUE, wRectRow, wlfCol);
		wolves[i] = wolf;
	}


}

void shootLaser()
{
  
  LASER lead = {1, currentColor, laserRow, laserCol, laserSpeed};
  LASER decay = {1, BGCOLOR, laserRow, laserCol, laserSpeed/2};
  lasers[0] = lead;
  lasers[1] = decay;
}

void updateLaser()
{

	for(int i = 0; i < 2; i++)
	{
		if(lasers[i].exists)
		{
			
			if(lasers[i].col + lasers[i].speed <= 240)
			{
				drawRect(lasers[i].row, lasers[i].col, laserGirth, laserLength, lasers[i].color);
			}
			else
			{
				lasers[i].exists = 0;
				drawRect(4, 120, 8, 120, BGCOLOR);//Clears score block to be written over
			}
			lasers[i].col = lasers[i].col + lasers[i].speed;

		}
	}

}

void updateSheep()
{
	const u16 **ptrMarioImage = &marioColor;
	getMarioImage(currentColor, ptrMarioImage);
	drawImage(shpAdjRow, shpAdjCol, MARIO_WIDTH, MARIO_HEIGHT, marioColor);
}

void getMarioImage(unsigned short color, const u16 **ptrMarioImage)
{
	switch(color)
	{
		case MC000:
			*ptrMarioImage = m000;
			break;
		case MC111:
			*ptrMarioImage = m111;
			break;
		case MC222:
			*ptrMarioImage = m222;
			break;
		case MC100:
			*ptrMarioImage = m100;
			break;
		case MC010:
			*ptrMarioImage = m010;
			break;
		case MC001:
			*ptrMarioImage = m001;
			break;
		case MC200:
			*ptrMarioImage = m200;
			break;
		case MC020:
			*ptrMarioImage = m020;
			break;
		case MC002:
			*ptrMarioImage = m002;
			break;
		case MC110:
			*ptrMarioImage = m110;
			break;
		case MC101:
			*ptrMarioImage = m101;
			break;
		case MC011:
			*ptrMarioImage = m011;
			break;
		case MC220:
			*ptrMarioImage = m220;
			break;
		case MC202:
			*ptrMarioImage = m202;
			break;
		case MC022:
			*ptrMarioImage = m022;
			break;
		case MC210:
			*ptrMarioImage = m210;
			break;
		case MC201:
			*ptrMarioImage = m201;
			break;
		case MC120:
			*ptrMarioImage = m120;
			break;
		case MC021:
			*ptrMarioImage = m021;
			break;
		case MC102:
			*ptrMarioImage = m102;
			break;
		case MC012:
			*ptrMarioImage = m012;
			break;
		case MC211:
			*ptrMarioImage = m211;
			break;
		case MC121:
			*ptrMarioImage = m121;
			break;
		case MC112:
			*ptrMarioImage = m112;
			break;
		case MC221:
			*ptrMarioImage = m221;
			break;
		case MC212:
			*ptrMarioImage = m212;
			break;
		case MC122:
			*ptrMarioImage = m122;
			break;
				
	}
}

void updateColor(int x)
{
	switch(x)
	{

	 case 0:
	   currentColor = BLACK;
	   break;
	 case 1:
	   currentColor = currentColor & ~RED;
	   currentColor = currentColor | RED;
	   break;
	 case 2:
	   currentColor = currentColor & ~GREEN;
	   currentColor = currentColor | GREEN;
	   break;
	 case 3:
	   currentColor = currentColor & ~BLUE;
	   currentColor = currentColor | BLUE;
	   break;
	 case 4:
	   currentColor = currentColor & ~RED;
	   currentColor = currentColor | DRED;
	   break;
	 case 5:
	   currentColor = currentColor & ~GREEN;
	   currentColor = currentColor | DGREEN;
	   break;
	 case 6:
	   currentColor = currentColor & ~BLUE;
	   currentColor = currentColor | DBLUE;
	   break;
	 
	   
	 }
}

/*typedef struct WOLF
{
	unsigned int speed;
	unsigned short color;
	unsigned short health;//directly related to size
	unsigned short spawnType;//0 - normal. 1 - rushed start. 2 - airborne
	unsigned int row;
	volatile unsigned int col;
	unsigned short alive;//1 or 0

} WOLF;
*/

void createWolf()
{
	//drawRect(0, 0, 15, 15, GREEN);
	WOLF wolf1 = {1, RED, 5, 0, wRectRow, wlfCol, 1};
	for(int i = 0; i < wsize/2; i++)
	{
		if(!wolves[i].alive)
		{
			wolves[i] = wolf1;
			break;
		}

	}
	WOLF wolf2 = {2, YELLOW, 5, 0, wRectRow, wlfCol, 1};
	for(int i = wsize/2; i < wsize; i++)
	{
		if(!wolves[i].alive)
		{
			wolves[i] = wolf2;
			break;
		}

	}

}

void updateWolves()
{
	const u16 *wolfColor;;
	const u16 **ptrMarioImage = &wolfColor;

	for(int i = 0; i < wsize; i++)
	{


		if(wolves[i].alive)
		{	
			getMarioImage(wolves[i].color, ptrMarioImage);
			drawRect(wolves[i].row, wolves[i].col, MARIO_HEIGHT, MARIO_WIDTH, BGCOLOR);
			
			if(lasers[0].color == wolves[i].color){
				if(wolves[i].col > lasers[0].col && wolves[i].col < lasers[0].col + laserLength)//wolf intersecting laser
				{
					wolves[i].alive = 0;
					scoreMulti++;
					score += 100*scoreMulti;

				}
			}
			wolves[i].col = wolves[i].col - wolves[i].speed;
			if(wolves[i].col <= shpDeathCol)
			{
				wolves[i].alive = 0;
				playerHealth--;
			
			}
			else if(wolves[i].alive)
			{
				//drawRect(wolves[i].row, wolves[i].col, dwlfHeight, dwlfWidth, wolves[i].color);		
				drawImageFlippedLR(wolves[i].row, wolves[i].col, MARIO_WIDTH, MARIO_HEIGHT, wolfColor);
			}

			if(wolves[i].col >= wlfCol - dwlfWidth)//on spawn to get rid of overlap
			{
				//drawRect(0, 0, dwlfHeight, dwlfWidth, GREEN);
				drawRect(wolves[i].row + 1, 0, dwlfHeight, dwlfWidth, BGCOLOR);

			}
			
		}

	}

}


void delay(int n)
{
	volatile int x = 0;
	for(int i=0; i<n*5000; i++)
	{
		x = x + 1;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		DMA[3].src = &color; // This is always an address!
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)]; // This is always an address!
		DMA[3].cnt = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
	}
}

void drawChar(int row, int col, char ch, unsigned short color)
{
	for(int r = 0; r< 8; r++)
	{
		
		for(int c=0; c< 6; c++)
		{
			if( fontdata_6x8[OFFSET(r, c, 6) + ch*48] == 1)
			{
				setPixel(r+row, c+col, color);
			}
		}
	}
}

void drawString(int row, int col, char str[], unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col += 6;
	}
}

void drawImage(int row, int col, int width, int height, const u16* image) 
{
    for (int r = 0; r < height; r++) {
        DMA[3].src = &image[r*width];
        DMA[3].dst = &videoBuffer[(row + r) * 240 + col];
        DMA[3].cnt = width | DMA_ON;

    }
}

void drawImageFlippedLR(int row, int col, int width, int height, const u16* image) 
{
    for (int r = 0; r < height; r++) {
        DMA[3].src = &image[r*width];
        DMA[3].dst = &videoBuffer[(row + r) * 240 + col + width - 2];
        DMA[3].cnt = width | DMA_ON | DMA_DESTINATION_DECREMENT;
    }
}

void fillScreen(volatile u16 color)
{
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (160*240) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;

}


void updatePipe()
{
	drawImage(80, 224, PIPE_WIDTH, PIPE_HEIGHT, pipe);
}

void updateScore()
{
	char buffer[41];
	sprintf(buffer, "Score: %d", score);
	
	drawString(4, 120, buffer, WHITE);

}

void gameOver()
{
	fillScreen(WHITE);
	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_START))
		{

			fillScreen(BGCOLOR);
			drawImage(112, 0, MFLOOR_WIDTH, MFLOOR_HEIGHT, mfloor);
			updateSheep();	
			init();
			break;

		}

	}
}