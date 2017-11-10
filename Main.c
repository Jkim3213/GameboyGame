#include <stdio.h>
#include "Main.h"

#define wsize 10
unsigned short currentColor;

//const int size = 10;
WOLF wolves[wsize];
LASER lasers[2];
//int wlfCnter = 0;//wolf counter
int laserPos; 
//LASER laser;
int laserRow;
int laserCol;
unsigned int wRectRow;
int score;
int scoreMulti;
const u16 *marioColor;

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	shpAdjRow = ADJPOS(shpRow, shpHeight);
	shpAdjCol = ADJPOS(shpCol, shpWidth);
	//maxWolves = 3;
	laserGirth = shpHeight/2;
	laserRow = shpRow - laserGirth/2;
   	laserCol = shpCol + shpWidth/2;
	wRectRow = ADJPOS(wlfRow, dwlfHeight);
	score = 0;
	scoreMulti = 0;
	marioColor = m000;
	populateWolves(wolves, wsize);

	//int score = 0;
	//char buffer[41];
	//sprintf(buffer, "Score: %d", score); //max score count
	//drawString(150, 5, buffer, YELLOW);
// Fill screen with bgcolor using DBA
	int bgcolor = BGCOLOR;
	REG_DMA3SAD = (u32)&bgcolor; // This is always an address!
	REG_DMA3DAD = (u32)videoBuffer; // This is always an address!
	REG_DMA3CNT = (240*160) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
	//drawRect(shpRow - shpHeight/2, shpCol - shpWidth/2, shpHeight, shpWidth, BLACK);
	
	updateColor(0);
	updateSheep();
	volatile unsigned int laserCooldown = 0;
	
	unsigned int wolfCooldown = 120;
	volatile const int wolfRate = 180;//8 wolves a sec

	
	while(1)
	{
	  //LIGHT COLORS
	  if(KEY_DOWN_NOW(BUTTON_LEFT) && KEY_DOWN_NOW(BUTTON_A))
	    {
	      updateColor(1);
	      updateSheep();    
	    }
	  if(KEY_DOWN_NOW(BUTTON_UP) && KEY_DOWN_NOW(BUTTON_A))
	    {
	      updateColor(2);
	      updateSheep(); 
	    }
	  if(KEY_DOWN_NOW(BUTTON_RIGHT) && KEY_DOWN_NOW(BUTTON_A))
	    {
	      updateColor(3);
	      updateSheep();
	    }
	  //DARK COLORS
	  if(KEY_DOWN_NOW(BUTTON_LEFT) && KEY_DOWN_NOW(BUTTON_B))
	    {
	      updateColor(4);
	      updateSheep();
	    }
	  if(KEY_DOWN_NOW(BUTTON_UP) && KEY_DOWN_NOW(BUTTON_B))
	    {
	      updateColor(5);
	      updateSheep();
	    }
	  if(KEY_DOWN_NOW(BUTTON_RIGHT) && KEY_DOWN_NOW(BUTTON_B))
	    {
	      updateColor(6);
	      updateSheep();
	    }
	  //RESET
	  if(KEY_DOWN_NOW(BUTTON_DOWN))
	    {
	      	updateColor(0);
	      	updateSheep();
	    }
	  if((KEY_DOWN_NOW(BUTTON_L) || KEY_DOWN_NOW(BUTTON_R)) && laserCooldown == 0)
	    {
	    	laserCooldown = lCD;
	      	shootLaser();
	      	updateColor(0);
	      	updateSheep();
	    }

	    if(wolfCooldown == 0)
	    {
	    	createWolf();
	    	wolfCooldown = wolfRate;
	    }

	    updateWolves();
	    updateLaser();

	    if(laserCooldown)
	    	laserCooldown--;

	    if(wolfCooldown)
	    	wolfCooldown--;

	  	waitForVblank();
	  
	}

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
  
  
/*
  //160x240 dim of screen
  //drawRect(laserRow, laserCol, laserGirth, 240 - laserCol, currentColor);
  const int growth = (240 - laserCol)/5;//divide by multiples of 5: 240-laserCol is 50.
  for(int i = laserCol; i < 240; i = i + growth){
    drawRect(laserRow, i, laserGirth, growth, currentColor);
    //waitForVblank();
  }
  const int decay = (240 - laserCol)/10;
  for(int i = laserCol; i < 240; i = i + decay){
    drawRect(laserRow, i, laserGirth, decay, BGCOLOR);
    //waitForVblank();
  }
*/
  LASER lead = {1, currentColor, laserRow, laserCol, laserSpeed};
  LASER decay = {1, BGCOLOR, laserRow, laserCol, laserSpeed/2};
  lasers[0] = lead;
  lasers[1] = decay;
}

void updateLaser()
{
	//TODOx/
	//static volatile int laserTime = 120;
	

	for(int i = 0; i < 2; i++)
	{
		if(lasers[i].exists)
		{
			//drawRect(laser.row, laser.col, laserGirth, laser.speed, BGCOLOR);
			//if(laserTime == 0)
			//	laserTime = 180;
			//drawRect(lasers[i].row, lasers[i].col, laserGirth, lasers[i].speed, BGCOLOR);
			
			if(lasers[i].col + lasers[i].speed <= 240)
			{
				drawRect(lasers[i].row, lasers[i].col, laserGirth, laserLength, lasers[i].color);
			}
			else
			{
				lasers[i].exists = 0;
			}
			lasers[i].col = lasers[i].col + lasers[i].speed;

		}
	}
	//if(laserTime > 0)
	//	laserTime--;


}

void updateSheep()
{
	switch(currentColor)
	{
		case MC000:
			marioColor = m000;
			break;
		case MC111:
			marioColor = m111;
			break;
		case MC222:
			marioColor = m222;
			break;
		case MC100:
			marioColor = m100;
			break;
		case MC010:
			marioColor = m010;
			break;
		case MC001:
			marioColor = m001;
			break;
		case MC200:
			marioColor = m200;
			break;
		case MC020:
			marioColor = m020;
			break;
		case MC002:
			marioColor = m002;
			break;
		case MC110:
			marioColor = m110;
			break;
		case MC101:
			marioColor = m101;
			break;
		case MC011:
			marioColor = m011;
			break;
		case MC220:
			marioColor = m220;
			break;
		case MC202:
			marioColor = m202;
			break;
		case MC022:
			marioColor = m022;
			break;
		case MC210:
			marioColor = m210;
			break;
		case MC201:
			marioColor = m201;
			break;
		case MC120:
			marioColor = m120;
			break;
		case MC021:
			marioColor = m021;
			break;
		case MC102:
			marioColor = m102;
			break;
		case MC012:
			marioColor = m012;
			break;
		case MC211:
			marioColor = m211;
			break;
		case MC121:
			marioColor = m121;
			break;
		case MC112:
			marioColor = m112;
			break;
		case MC221:
			marioColor = m221;
			break;
		case MC212:
			marioColor = m212;
			break;
		case MC122:
			marioColor = m122;
			break;
				
	}
	drawImage(shpAdjRow, shpAdjCol, MARIO_WIDTH, MARIO_HEIGHT, marioColor);
	/*
  	drawRect(shpAdjRow - 1, shpAdjCol - 1, shpHeight + 2, shpWidth + 2, currentColor - currentColor/2);	
  	drawRect(shpAdjRow, shpAdjCol, shpHeight, shpWidth, currentColor);
*/
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

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		REG_DMA3SAD = (u32)&color; // This is always an address!
		REG_DMA3DAD = (u32)&videoBuffer[OFFSET(row+r, col, 240)]; // This is always an address!
		//REG_DMA3DAD = (u32)(videoBuffer + OFFSET(row+r, col, 240) ); // This is always an address!
		REG_DMA3CNT = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
	}
}

/*
void spawnWolf(int speed, short color, short health, short spawnType)
{
	//WOLF wolf = {speed, color, health, spawnType, wlfRow, wlfCol};
	//unsigned int wRectRow = ADJPOS(wlfRow, dwlfHeight + health*gFactor);
	//unsigned int wRectCol = ADJPOS(wlfCol, dwlfWidth + health*gFactor); I want it to spawn at the edge of the screen

	

}
*/
void createWolf()
{
	//drawRect(0, 0, 15, 15, GREEN);
	WOLF wolf = {1, RED, 5, 0, wRectRow, wlfCol, 1};
	for(int i = 0; i < wsize; i++)
	{
		if(!wolves[i].alive)
		{
			wolves[i] = wolf;
			break;
		}

	}
	/*
	if(wlfCnter < maxWolves){
		wolves[wlfCnter] = wolf;
		wlfCnter++;
	}
*/
}

void updateWolves()
{
	for(int i = 0; i < wsize; i++)
	{


		if(wolves[i].alive)
		{		
			drawRect(wolves[i].row, wolves[i].col, dwlfHeight, dwlfWidth, BGCOLOR);
			
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
				//wlfCnter--;
			
			}
			else if(wolves[i].alive)
			{
				drawRect(wolves[i].row, wolves[i].col, dwlfHeight, dwlfWidth, wolves[i].color);		
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

