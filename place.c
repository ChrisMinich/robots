// place.c
// by Chris Minich
// cfminich@gmail.com

/***
 placeAllMines()
 	Call placeMine() for each mine.
*/
void placeAllMines(void)
{
	for (int i=0; i<minecount; i++)
		placeMine(mine[i]);
}

/*** 
 placeAllRobots()
 
 	Each robot contains a 4-digit integer which represents its x and y coordinates.
	Place each array member on the board. 
*/
void placeAllRobots()
{
	int i, roboty, robotx;

	for(i=0; i<robotcount; i++)
	{
		roboty = abs(robot[i] / 100);
		robotx = abs(robot[i] - (roboty * 100));
		pos(roboty+offset,robotx); printf(ROBOT,BLUE); printf(UNBOLD);
	}
}

/*** 
 placeMine()
 
 	Each mine contains a 4-digit integer which represents its x and y coordinates.
	Print a mine onto the board. 
*/   
void placeMine(int mine)
{
	int miney = abs(mine / 100);
	int minex = abs(mine - (miney * 100));
	pos(miney+offset, minex); printf(MINE,RED);
}
