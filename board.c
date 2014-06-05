// board.c
// by Chris Minich
// cfminich@gmail.com

void makeBoard()
{
	int i, j;
/*	if (! tracemode) cls;*/
	pos(1+offset,1);
	if (color) printf(BACKGROUND,bg);
	for(i=1; i<=HEIGHT; i++)
	{
		for(j=1; j<=WIDTH; j++)
		{
			if (! color) printf(".");
			else printf(BOARD,bg);
		}
		printf("\n");
	}
	printf("\n");
}

void refreshboard()
{
	makeBoard(); 
	placeAllMines();
	placeAllRobots(); 
	pos(y+offset,x); 
	printf(HUMAN,CYAN);
	printStats();
}

/***
 printStats()
 
 	Show the level, robot and mine counts, points, and earned safeTeleports.
*/
void printStats()
{
	char* stats = malloc((WIDTH + 1) * sizeof(char));
	sprintf(stats, "Level: %d  Robots: %d  Mines: %d  Points: %d  Safe Teleports: %d", level, robotcount, minecount, points, safeTeleports);
	int xpos = ( WIDTH - strlen(stats) ) / 2 + 1;
	if (xpos < 1) xpos = 1;
	printf(GREEN_SCORES); 
	for (int i=1; i<=WIDTH; i++)
	{
		pos(1,i);
		printf(" ");
	}
	pos(1, xpos);
	printf("%s", stats);
	free(stats);
	
	printf(NORMAL);
	if (points) return;
	 
	char* info = malloc((WIDTH + 1) * sizeof(char));
	sprintf(info, "   \"s\" safe, \"*\" random teleport, \"+\" safely teleport   ");
	xpos = ( WIDTH - strlen(info) ) / 2 + 1;
	pos(HEIGHT+1+offset, xpos); 
	printf(NORMAL); printf("%s", info);
	free(info);
	bottom = HEIGHT + 1 + offset;
   
	char* info1 = malloc((WIDTH + 1) * sizeof(char));
	sprintf(info1, "Use number pad for directional movement, space or 5 to stay");
	xpos = ( WIDTH - strlen(info1) ) / 2 + 1;
	if (xpos < 1) xpos = 1;
	pos(HEIGHT+2+offset, xpos);
	bottom = HEIGHT + 2 + offset;
	printf(NORMAL); printf("%s", info1);
	free(info1);
	char* info2 = malloc((WIDTH + 1) * sizeof(char));
	sprintf(info2, "You may also use h, l, k, n, m, u, i to move, or (q)uit");
	xpos = ( WIDTH - strlen(info2) ) / 2 + 1;
	if (xpos < 1) xpos = 1;
	pos(HEIGHT+3+offset, xpos);
	bottom = HEIGHT + 3 + offset;
	printf(NORMAL); printf("%s", info2);
	free(info2);
}

void finishLevel()
{
	refreshboard();
	alive = 2;
	if((maxrobots + INCREMENT > LIMIT) || (mega_teleports_achieved))
	{
		int yy, xx;
		yy = y;
		xx = x;
		if (yy<3) yy = yy + 1;
		else yy = yy - 2;
		if(WIDTH-xx < 15) xx = WIDTH - 15;
		pos(yy+offset, xx);
		printf(FOREGROUND,YELLOW);
		if (color) printf(BACKGROUND,bg);
		printf("You win!!!");
		pos(yy+1+offset,xx);
		printf("That's awesome!");
		printf(NORMAL);
	}
}

void youLose(int killer)
{
	int yy = y-2;
	int xx = x;
   
	if(yy<2) yy=y + 2;
	if(WIDTH-xx < 10) xx = WIDTH - 10;
   
	refreshboard();

	if (hit == 'x') // caught by a robot
	{
		int ry = abs(clone[killer] / 100);
		int rx = abs(clone[killer] - (ry * 100));
		printf(FOREGROUND,YELLOW);
		if (color) printf(BACKGROUND,bg);
		pos(yy+offset,xx); printf("\"Aaahhh!!\"");
		pos(ry+offset,rx);
		printf(ROBOT,GREEN);
		pos(y+offset,x);
		printf(HUMAN,CYAN);
	}
	else // killed upon transport
	{
		printf(FOREGROUND,YELLOW);
		pos(yy+offset,xx); printf("\"Aaahhh!!\"");
		pos(y+offset,x);
		if (hit == '@') printf(ROBOT,GREEN);
		else printf(MINE,CYAN);
	}
	alive = 0;
}

void message(int n)
{
	if (n == 0) return;
	char* info1 = malloc((WIDTH + 1) * sizeof(char));
	sprintf(info1, "Press any key");
	int xpos = ( WIDTH - strlen(info1) ) / 2 + 1;
	int ypos = HEIGHT / 2;
	if (ypos == y) ypos = y + 2;
	pos(ypos+offset, xpos);
	printf(FOREGROUND,YELLOW); printf("%s", info1);
	printf(NORMAL);
	free(info1);
}

