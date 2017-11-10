#include <stdio.h>
#include "lib.h"

int seed; 
WOLF wolves[wsize];
int LCD;
unsigned short *videoBuffer;

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;


	while(!KEY_DOWN_NOW(BUTTON_START))
	{
		seed++;

	}

	init();

	videoBuffer = (unsigned short *)0x6000000;

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
	drawImage(112, 0, MFLOOR_WIDTH, MFLOOR_HEIGHT, mfloor);
	
	
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
	    updatePipe();
	    if(laserCooldown)
	    	laserCooldown--;

	    if(wolfCooldown)
	    	wolfCooldown--;

	  	waitForVblank();
	  
	}

}
