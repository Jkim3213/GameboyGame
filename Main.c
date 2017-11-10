#include "lib.h"

unsigned int seed; 

unsigned int LCD;
unsigned int wolfrate;
int playerHealth;

int main()
{

	volatile unsigned int laserCooldown = 0;
	unsigned int wolfCooldown = 120;
	
	REG_DISPCTL = MODE3 | BG2_ENABLE;


	while(!KEY_DOWN_NOW(BUTTON_START))
	{
		seed++;

	}

	init();

	fillScreen(BGCOLOR);
	drawImage(112, 0, MFLOOR_WIDTH, MFLOOR_HEIGHT, mfloor);
	

	updateColor(0);
	updateSheep();


	

	
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
	    updateScore();
	    updatePipe();
	    if(laserCooldown)
	    	laserCooldown--;

	    if(wolfCooldown)
	    	wolfCooldown--;

	    if(playerHealth <= 0)
	    {
	    	gameOver();
	    }


	  	waitForVblank();
	  
	}

}
