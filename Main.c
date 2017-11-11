#include "lib.h"

unsigned int seed; 

unsigned int LCD;
unsigned int wolfrate;
int playerHealth;
int gameState;
unsigned int gameTime;

int main()
{

	volatile unsigned int laserCooldown = 0;
	unsigned int wolfCooldown = 60;
	
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	const int second = 30;
	volatile int timer = second;
	while(1)
	{
		if(timer > 0)
			timer--;
		if(timer == 0)
		{
			gameTime++;
			timer = second;
		}
	    //LIGHT COLORS
	  	if(gameState == 0)
	  	{
	  		startGame();
	  	}
	  	else if(gameState == 1)
	  	{
	  		gameOver();
	  	}
	  	else
	  	{
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
		    if(KEY_DOWN_NOW(BUTTON_SELECT))
	    	    {
	    	    	gameState = 0;
	    	    }

	    	if(wolfCooldown == 0)
	    	    {
	    	    	createWolf();
	    	    	wolfCooldown = wolfRate;
	    	    }
	    	spawnWolf();
			updateWolves();
			updateLaser();//also blanks score
			//updateScore();
			updatePipe();
			updateCloud();
			if(laserCooldown)
				laserCooldown--;

			if(wolfCooldown)
				wolfCooldown--;

			if(playerHealth <= 0)
			{
				gameState = 1;
			}


			waitForVblank();
			waitForVblank();
		}
	}

}
