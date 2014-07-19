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
/*		if ((roboty > HEIGHT) || (roboty < 1)) { printf("error y\n"); exit(0); }*/
/*		if ((robotx > WIDTH ) || (robotx < 1)) { printf("error x\n"); exit(0); }*/
	}
}

int insertIntoArray(int new, int size)
{
	if (size == 0) {
		robot[0] = new;
		return 1;
	}

	int inserted = 0;
	int i = 0;

	do {
		if (new == robot[i]) {
			return 0;
		}
		if (new < robot[i]) {
			for (int j=size; j>i; j--)
				robot[j] = robot[j-1];
			robot[i] = new;
			inserted = 1;
		}
		++i;
	} while ((!inserted) && (i<size));
	
	if ((!inserted) && (new > robot[size-1])) {
		robot[size] = new;
		inserted = 1;
	}
	
	if (inserted) return 1;
	else return 0;
}

int getNewCoordinates()
{
	int location = (rand() % HEIGHT + 1) * 100;    
	location = location + (rand() % WIDTH + 1);
	return location;
}

void makeRobots(int max)
{
	int i;
	int point;
	
	for (i=0; i<max; i++) // store initial robots into array
	{
		do {
			point = getNewCoordinates();
		} while ( ! insertIntoArray(point, i) );
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
