// human.c
// by Chris Minich
// cfminich@gmail.com

int humanUnSafe(int location) // return -1, if human is safe
{
	int i;
	hit = '@'; // caught by robot
	for(i=0; i<robotcount; i++)
		if(location == robot[i]) return i; // unsafe, return position index
      
	hit = '#'; // landed on mine
	for(i=0; i<minecount; i++)
		if(location == mine[i]) return i; // unsafe, return position index
      
	hit = 'x'; // human still safe
	return -1; // safe move for human
}

/***
 validateMove()
 
 	If humanUnSafe() returns a robot index, then move is not valid
 	because we won't let the human move purposely into a robot.
 	Otherwise, if humanUnSafe() returns -1, then update the human's
 	x and y coordinates.
*/

int validateMove(int yy, int xx)
{
   if((yy>HEIGHT) || (yy<1) || (xx>WIDTH) || (xx<1)) return 0;
   int value = yy * 100 + xx;
   if(humanUnSafe(value) < 0)
   {
      y = yy;
      x = xx;
      return 1;
   }
   else return 0;
}

/***
 trymove()

 	save current position of human
	call validateMove()
	if new position is valid, update position of man
	else, return 0
*/
int trymove(char d1, char d2)
{
   int valid_move = 0;
   oldy = y; oldx = x;
   
   if(d1 == 'u' && d2 == 'n') valid_move = (validateMove(y-1, x));
   if(d1 == 'd' && d2 == 'n') valid_move = (validateMove(y+1, x));
   if(d1 == 'l' && d2 == 'n') valid_move = (validateMove(y, x-1));
   if(d1 == 'r' && d2 == 'n') valid_move = (validateMove(y, x+1));
   if(d1 == 'u' && d2 == 'l') valid_move = (validateMove(y-1, x-1));
   if(d1 == 'u' && d2 == 'r') valid_move = (validateMove(y-1, x+1));
   if(d1 == 'd' && d2 == 'l') valid_move = (validateMove(y+1, x-1));
   if(d1 == 'd' && d2 == 'r') valid_move = (validateMove(y+1, x+1));
   
   return valid_move; // 1 = yes; 0 = no
}   

int teleport() // compute new position for human
{
	int value;

	y = rand() % HEIGHT + 1;
	x = rand() % WIDTH + 1;
	value = y * 100 + x;
	return value;
}

void pteleport() // print teleport action
{
	int py = y + offset;
	if (x>1)
	{
		pos(py,x-1);
		printf(FOREGROUND,YELLOW);
		if (color) printf(BACKGROUND,bg);
		printf("[");
	}
	else
	{
		pos(py,x);
	}
	if (color) printf(BACKGROUND,bg);
	printf(HUMAN,CYAN); 
	if (x<WIDTH)
	{
		printf(FOREGROUND,YELLOW);
		printf("]");
	}
	message(1);
	pos(py,x);
	if (color) { printf(FOREGROUND,39); printf(UNBOLD); }
	else printf(NORMAL);
	mygetch();
	refreshboard();
	
	if (tracemode)
	{
		trace(robot, 3);
		trace(mine, 4);
	}
}
