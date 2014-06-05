// helpers.c
// by Chris Minich
// cfminich@gmail.com

/***
 * mygetch()
 *
 * found this function on a help forum: 
 *
 *    http://www.daniweb.com/software-development/c/threads/148447/getch-implementation-in-unix
 */
int mygetch( void ) 
{
  int ch;
  struct termios oldt, newt;

  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

  return ch;
}

/***
 * trace() - debugging utility
 *
 * enables watching the robot and mine array values
 * shows the robots and mines on the line above the Human,
 * the same line as the Human, and the line below the Human.
 * Col. 1, used by consolidate to see unsorted robots,
 * col. 2, to show sorted robots with duplicates (robots that collided)
 * col. 3, to show robots with duplicates deleted
 * col. 4, to show mines
 * col. 5, to show Human's location; then show number of robots at the
 *    of each level.
 */
void trace(int* arr, int col)
{
	int count, lower, upper;
	if (arr == robot) count = robotcount;
	else count = minecount;
	lower = y - 1;
	if (lower<1) lower = 100;
	else lower = lower * 100;
	upper = y + 2;
	if (upper>HEIGHT) upper = (HEIGHT + 1) * 100;
	else upper = upper * 100;
	int tab = WIDTH + 2;
	for (int i=1; i<col; i++) tab = tab + 6;
	pos(1, tab);
	if (arr == robot) printf("ROBOT ");
	else printf("MINES ");
	
	int n = 2;
	for (int i=0; i<count; i++)
	{
		if ((n<=HEIGHT) && (arr[i]>lower) && (arr[i]<upper))
		{
			pos(n, tab);
			printf("%d ", arr[i]);
			n++;
		}
	}
	if (n<=HEIGHT) 
		for (int i=n; i<=HEIGHT; i++)
		{
			pos(i, tab);
			printf("    ");
		}
	if (col == 4)
	{
		tab = tab + 6;
		pos(1, tab);
		printf("HUMAN ");
		pos(2, tab);
		printf("%d ", y*100+x);
		
		pos(4, tab);
		if ( level == 1) printf("LEVEL");
		pos(4+level, tab);
		printf("%d: %d", level, start_amt);
	}
}

