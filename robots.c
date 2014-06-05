// Program robots.c
// by Chris Minich
// cfminich@gmail.com

/*
Algorithm:
1. a direction key is pressed
2. call trymove() to encode the move, saving the old position in case we ultimately cannot move the human
3. trymove() calls validateMove() which checks whether the proposed move is legal for current robot and mine positions
4. if move is legal (so far), call moveRobots()
5. moveRobots() calls advanceRobots() to calculate new robot positions
6. advanceRobots(): if new positions do not catch the human, the robot array is updated.
7. if player has pressed 's' to indicate that she is sure the human is safe, the robots are allowed to move into (catch) the human
8. if player has not pressed 's', the robots cannot move into the human, so they stay in place, and the player's move does not execute
9. if player moved without being killed, call sortRobots() to update all robots and mines
10. call refreshboard() show all the new positions of the robots, mines, and the human
*/

#include "robots.h"
#include "helpers.c"
#include "board.c"
#include "place.c"
#include "moverobots.c"
#include "human.c"

int main(int argc, char *argv[])
{
	cls;
	if ((argc > 1) && (argv[1][0] == 'd')) tracemode = 1;
  	srand(time(NULL)); // seed the random number generator

	int i, newposition, tempcount, killer;
	char ch;

	alive = 1;
	makeBoard();
   
	while(alive) // set up new level. youLose() sets alive = 0
	{
		safeMode = 0;
		level++;
		maxrobots = maxrobots + INCREMENT;
		start_amt = maxrobots;
		minecount = 0;
		init = 1; // set-up mode is true ( in init mode, don't create any mines )
      
		if(maxrobots<=LIMIT) robotcount = maxrobots;
		else
		{
			break; // you won
		}
         
		for(i=0; i<maxrobots; i++) // initialize all robots and mines to zero value
		{
			robot[i] = -8;
			mine[i] = -5;
		}
      
		for(i=0; i<maxrobots; i++) // store initial robots into array
		{
			robot[i] = (rand() % HEIGHT + 1) * 100;     
			robot[i] = (rand() % WIDTH + 1) + robot[i];
		}  
       
		newposition = teleport();
		while(humanUnSafe(newposition) >= 0)
			newposition = teleport(); // place (H)uman in a random location
		sortRobots();
		start_amt = robotcount;

		refreshboard();
		pteleport();

		init = 0; // set-up of new level is complete

		while(alive == 1) // get keystrokes until level is complete. finishLevel() sets alive = 2
		{
			pos(y+offset,x);
			ch = mygetch();
			if(ch == 'q') alive = 0; // quit game
			else if(ch == 'r') { cls; refreshboard(); }
			else if(ch == 'c')
			{
				if (color) color = 0;
				else color = 1;	
				refreshboard();
			}
			else if(ch == 'd') // toggle trace mode (d = debug)
			{
				if (tracemode) tracemode = 0;
				else tracemode = 1;
				refreshboard();
			}

			else if(ch == 'S' || ch == 's') // Press 's' when you are sure that you are safe.
			{
				safeMode = 1;
				tempcount = safeTeleports + robotcount;
				while(alive == 1)
				{
					int i;
					for (i = 0; i < 10000; i++)
					{
			    		pos(HEIGHT+4+offset,1); printf(UNBOLD); printf("");
			    	}
			    	if (i>=10000) moveRobots();
				}
				if(alive) safeTeleports = tempcount;
				if (safeTeleports > maxrobots)
				{
					mega_teleports_achieved = 1;
					finishLevel(); // you won
					alive = 0;
				}				
				
			}

			else if(ch == 't' || ch == 'T' || ch == '+' || ch == '*') // teleport
			{
				pos(y+offset,x); printf(UNBOLD);
				
				if (! color) printf(".");
				else printf(BOARD,bg);				
				
				newposition = teleport();
				if(ch == 'T' || ch == '*' || safeTeleports < 1 )
				{
					pteleport();
					killer = humanUnSafe(newposition);
					if( killer >= 0 )
					{
						youLose(killer);
						break;
					}
				}
				if((ch == 't' || ch == '+') && (safeTeleports > 0))
				{
					while(humanUnSafe(newposition) >= 0)
						newposition = teleport();
					safeTeleports = safeTeleports - 1;
					printStats(); // to update safe teleports immediately
					pteleport();					
				}
			}
            
			else if(ch == '5' || ch == ' ') { oldy = y; oldx = x; moveRobots(); } // stay
			else if(ch == 'k' || ch == '8') { if(trymove('u','n')) moveRobots(); } // up
			else if(ch == 'j' || ch == '2') { if(trymove('d','n')) moveRobots(); } // down
			else if(ch == 'h' || ch == '4') { if(trymove('l','n')) moveRobots(); } // left
			else if(ch == 'l' || ch == '6') { if(trymove('r','n')) moveRobots(); } // right
			else if(ch == 'n' || ch == '1') { if(trymove('d','l')) moveRobots(); } // down-left
			else if(ch == 'm' || ch == '3') { if(trymove('d','r')) moveRobots(); } // down-right
			else if(ch == 'u' || ch == '7') { if(trymove('u','l')) moveRobots(); } // up-left
			else if(ch == 'i' || ch == '9') { if(trymove('u','r')) moveRobots(); } // up-right
		}
		if (alive == 2) alive = 1;
	}
	pos(bottom,1);
	printf(OS_DEFAULT); printf("\n");
}      
