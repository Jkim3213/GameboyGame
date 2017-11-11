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
LASER lasers[2];
const u16 *marioColor;

unsigned int shpAdjRow;
unsigned int shpAdjCol;
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
WOLF newWolves[wsize];
unsigned int redScore;
unsigned int greenScore;
unsigned int blueScore;
int spreadFactor = 10;
//cloud
volatile unsigned int cloudRow;
volatile unsigned int cloudCol;
const unsigned int cloudRate = 100;
static volatile unsigned int cloudCooldown;//1700 is initial push
int cloudState;
const unsigned int cloudRowOrigin = 20;
const unsigned int cloudColOrigin = 240 - CLOUD_WIDTH - 20;
unsigned int gameTime;
unsigned int newCnter;

WOLF *ptrWolf;
WOLF *ptrNewWolf;
LASER *ptrLaser;

int gameState;

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
	lCD = 15;//the constant value that laserCoolDown refreshes to
	wolfRate = 180;
	laserSpeed = 20;
	laserLength = 20;

	shpAdjRow = ADJPOS(shpRow, shpHeight);
	shpAdjCol = ADJPOS(shpCol, shpWidth);
	//maxWolves = 3;
	laserGirth = shpHeight/2;
	laserRow = shpRow - laserGirth/2;
   	laserCol = shpCol + shpWidth/2;
	wRectRow = ADJPOS(wlfRow, dwlfHeight);
	score = 0;
	scoreMulti = 0;
	
	//marioColor = m000;
	playerHealth = 3;
	populateWolves(wolves, wsize);


	cloudRow = cloudRowOrigin;
	cloudCol = cloudColOrigin;
	cloudCooldown = cloudRate;
	cloudState = 0;

	gameState = 2;
	gameTime = 0;

	fillScreen(BGCOLOR);
	updateScore();
	updateHealth();
	drawImage(112, 0, MFLOOR_WIDTH, MFLOOR_HEIGHT, mfloor);
	

	updateColor(0);
	updateSheep();
	srand(seed);


}

void populateWolves(WOLF wolves[], int size)
{
	
	for(int i = 0; i < size; i++)
	{
		WOLF wolf = {1, BLUE, wRectRow, wlfCol, 0};
		wolves[i] = wolf;
	}


}

void shootLaser()
{
  
  LASER lead = {1, currentColor, laserRow, laserCol, laserSpeed, laserLength};
  LASER decay = {1, BGCOLOR, laserRow, laserCol, laserSpeed/4, laserLength/4};
  lasers[0] = lead;
  lasers[1] = decay;
  scoreMulti = 1;
}

void updateLaser()
{

	for(int i = 0; i < 2; i++)
	{
		ptrLaser = lasers + i;
		if(ptrLaser->exists)
		{
			
			if(ptrLaser->col + ptrLaser->speed <= 240)
			{
				drawRect(ptrLaser->row, ptrLaser->col, laserGirth, ptrLaser->laserLength, ptrLaser->color);
			}
			else
			{
				ptrLaser->exists = 0;
				
				updateScore();
			}
			ptrLaser->col = ptrLaser->col + ptrLaser->speed;

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
	//unsigned short health;//directly related to size
	//unsigned short spawnType;//0 - normal. 1 - rushed start. 2 - airborne
	unsigned int row;
	volatile unsigned int col;
	unsigned short alive;//1 or 0

} WOLF;
*/

void createWolf()
{
	//drawRect(0, 0, 15, 15, GREEN);
	unsigned short colorSet1[3]  = {MC200, MC020, MC002};

	unsigned short colorSet2[6]  = {MC200, MC020, MC002, MC100, MC010, MC001};

	unsigned short colorSet3[15] = {MC200, MC020, MC002, MC202, MC220, MC022, MC222, 
									MC100, MC010, MC001, MC111, MC110, MC101, MC011, 
									MC000};
	
	unsigned short colorSet4[16] = {MC200, MC020, MC002, MC202, MC220, MC022, MC222, 
									MC100, MC010, MC001, MC111, MC110, MC101, MC011, 
									MC000, MC210};
	
	unsigned short colorSet5[18] = {MC200, MC020, MC002, MC202, MC220, MC022, MC222, 
									MC100, MC010, MC001, MC111, MC110, MC101, MC011, 
									MC000, MC210, MC102, MC012};

	unsigned short colorSet6[20] = {MC200, MC020, MC002, MC202, MC220, MC022, MC222, 
									MC100, MC010, MC001, MC111, MC110, MC101, MC011, 
									MC000, MC210, MC102, MC012, MC112, MC212};
	unsigned short *ptrColorSet;
	unsigned int speedPotential;
	unsigned int setSize;
	
	if(gameTime < 10)
	{
		ptrColorSet = colorSet1;
		setSize = 3;
		speedPotential = 1;
	}
	else if(gameTime < 30)
	{
		ptrColorSet = colorSet2;
		setSize = 6;
		speedPotential = 1;
	}
	else if(gameTime < 60)
	{
		ptrColorSet = colorSet3;
		setSize = 15;
		speedPotential = 2;
	}
	else if(gameTime < 90)
	{
		ptrColorSet = colorSet4;
		setSize = 16;
		speedPotential = 2;
	}
	else if(gameTime < 120)
	{
		ptrColorSet = colorSet5;
		setSize = 18;
		speedPotential = 2;
	}
	else
	{
		ptrColorSet = colorSet6;
		setSize = 20;
		speedPotential = 3;
	}



	for(int i = 0; i < wsize; i++)
	{
		newWolves[i].speed = 1 + rand()%speedPotential;
		newWolves[i].color = ptrColorSet[rand()%setSize];
		newWolves[i].row = wRectRow;
		newWolves[i].col = wlfCol;
		newWolves[i].alive = 1;
	}	

	newCnter = 0;
	spreadFactor = 10;
	
	

}

void spawnWolf()
{
	if(spreadFactor == 0)
	{
		for(int i = 0; i < wsize; i++)
		{
			ptrWolf = wolves + i;
			if(!ptrWolf->alive)
				break;
		
		}
		if(newCnter < 4)
		{
		*ptrWolf = *(newWolves + newCnter);
		newCnter++;
		spreadFactor = 10;
		}
	}
}

void drawPoints(unsigned int row ,unsigned int col, unsigned short color, unsigned int points)
{
	
	char buffer[41];
	sprintf(buffer, "%d", points);
	
	drawString(row - 8, col, buffer, color);

	delay(7);
	drawRect(row - 8, col, 8, 20, BGCOLOR);//Clears score block to be written over
}

void updateWolves()
{
	const u16 *wolfColor;;
	const u16 **ptrMarioImage = &wolfColor;
	if(spreadFactor > 0)
		spreadFactor--;
	for(int j = 0; j < wsize; j++)
	{
		ptrWolf = wolves + j;
		if(ptrWolf->alive)
			drawRect(ptrWolf->row, ptrWolf->col, MARIO_HEIGHT, MARIO_WIDTH, BGCOLOR);
	}

	for(int i = 0; i < wsize; i++)
	{
		ptrWolf = wolves + i;

		if(ptrWolf->alive)
		{	
			getMarioImage(ptrWolf->color, ptrMarioImage);
			
			
			if(lasers[0].color == ptrWolf->color){
				if(ptrWolf->col > lasers[1].col && ptrWolf->col < lasers[0].col + laserLength)//wolf intersecting laser
				{
					ptrWolf->alive = 0;
					int wolfPoints = 100*scoreMulti;
					score += wolfPoints;
					scoreMulti *= 2;
					drawPoints(ptrWolf->row, ptrWolf->col, ptrWolf->color, wolfPoints);

				}
			}
			ptrWolf->col = ptrWolf->col - ptrWolf->speed;
			if(ptrWolf->col <= shpDeathCol)
			{
				ptrWolf->alive = 0;
				playerHealth--;
				if(playerHealth == 0)
				{
					redScore = ptrWolf->color & RED;
					greenScore = ptrWolf->color & BLUE;
					blueScore = ptrWolf->color & GREEN;
				}
				updateHealth();
			
			}
			else if(ptrWolf->alive)
			{
				//drawRect(wolves[i].row, wolves[i].col, dwlfHeight, dwlfWidth, wolves[i].color);		
				drawImageFlippedLR(ptrWolf->row, ptrWolf->col, MARIO_WIDTH, MARIO_HEIGHT, wolfColor);
			}

			if(ptrWolf->col >= wlfCol - dwlfWidth)//on spawn to get rid of overlap
			{
				//drawRect(0, 0, dwlfHeight, dwlfWidth, GREEN);
				drawRect(ptrWolf->row + 1, 0, dwlfHeight, dwlfWidth, BGCOLOR);

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
	while(SCANLINECOUNTER < 161);
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
	drawImage(cloudRow, cloudCol, CLOUD_WIDTH, CLOUD_HEIGHT, cloud);
}


void updatePipe()
{
	drawImage(80, 224, PIPE_WIDTH, PIPE_HEIGHT, pipe);
}

void updateScore()
{
	drawRect(3, 120, 9, 120, BGCOLOR);//Clears score block to be written over
	char buffer[41];
	sprintf(buffer, "Score: %d", score);
	drawString(4, 131, buffer, BLACK);
	drawString(3, 130, buffer, WHITE);
	
}

void updateHealth()
{
	drawRect(4, 19, 9, 60, BGCOLOR);//Clears score block to be written over
	char buffer[41];
	sprintf(buffer, "Health: %d", playerHealth);
	drawString(5, 20, buffer, BLACK);
	drawString(4, 19, buffer, WHITE);
}

void gameOver()
{
	delay(4);
	drawImage(0, 0, 240, 160, GameOverScreen);
	char buffer[41];
	sprintf(buffer, "Final Score: %d", score);
	drawString(124, 84, buffer, blueScore);
	drawString(122, 82, buffer, greenScore);
	drawString(120, 80, buffer, redScore);

	char time[41];
	sprintf(time, "  Game Time: %d", gameTime);
	drawString(140, 80, time, WHITE);


	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_START))
		{

			gameState = 0;
			break;
		}

	}
}

void updateCloud()
{
	
	if(cloudCooldown > 0)
		cloudCooldown--;
	
	const int cloudSpeed = 1;
	volatile int oldcloudRow = cloudRow;
	volatile int oldcloudCol = cloudCol;
	u32 tempRowOrigin = cloudRowOrigin;
	u32 tempColOrigin = cloudColOrigin;

	if(cloudCooldown == 0)
	{
		//drawRect(cloudRow, cloudCol, CLOUD_HEIGHT, CLOUD_WIDTH, BGCOLOR);
		
		switch(cloudState){
			case(0):
				cloudRow = cloudRow + cloudSpeed;//down
				//drawImage(0, 0, MARIO_WIDTH, MARIO_HEIGHT, m121);
				if(cloudRow == shpAdjRow)
					cloudState = 1;
				break;
			case(1):
				cloudCol -= cloudSpeed;//left
				//drawImage(5, 5, MARIO_WIDTH, MARIO_HEIGHT, m220);
				if(cloudCol == shpAdjCol + MARIO_WIDTH + 2)
					cloudState = 2;
				break;
			case(2):
				cloudRow -= cloudSpeed;//up
				if(cloudRow == tempRowOrigin)
					cloudState = 3;
				break;
			case(3):
				cloudCol += cloudSpeed;//right
				if(cloudCol == tempColOrigin)
					cloudState = 4;
				break;
			default:
				cloudCooldown = cloudRate * 10;//cloudRate;//stationary
				cloudState = 0;

				break;
		}
		drawRect(oldcloudRow, oldcloudCol, CLOUD_HEIGHT, CLOUD_WIDTH, BGCOLOR);
		drawImage(cloudRow, cloudCol, CLOUD_WIDTH, CLOUD_HEIGHT, cloud);


	}

}

void startGame()
{
	videoBuffer = (unsigned short *)0x6000000;

	drawImage(0, 0, STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, StartScreen);
	delay(10);	
	while(!KEY_DOWN_NOW(BUTTON_START))
	{
		seed++;

	}
	init();
	


}
