// moverobots.c
// by Chris Minich
// cfminich@gmail.com

/***
 consolidate(array, count)

 	When multiple robots are at the same location, they have collided.
 	We need to sort the array, and check consecutive elements for matching locations.
 	Once we have a match, we add a new mine to the mine array.
 	Then, see if there is one or two more matches, setting all robot[] matches to non-positive values.
	After we have looked through entire robot array and we're done matching, proceed to...
 	Delete all robot array members that have non-positive values.
*/   
void consolidate(int* arr, int* arr_count)
{
	int temp, xx;
	int count = 0;
	
	if (tracemode) trace(robot, 1);
	
	for(int i=0; i<*arr_count; i++) // Sort ascending
		for(int j=i+1; j<*arr_count; j++)
			if (arr[j]<arr[i])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}

	if (tracemode) trace(robot, 2);

	for(int i=0; i<*arr_count; i++) // Look for duplicates
		for(int j=i+1; j<*arr_count; j++)
			if ((arr[j] == arr[i]) && (arr[j] > 0))
			{
				xx = arr[j];
				if ( init == 0 ) // create another mine, add points
				{
					mine[minecount++] = xx;
					points = points + 10;
				}
				int k;
				if ( i < j ) k = i; else k = j;
				while ( ( arr[k] == xx ) && ( k < *arr_count ) ) // mark for deletion
					arr[k++] = -33; // any non-positive value is fine
   		    }

	for(int i=0; i<*arr_count; i++) // delete any array elements with a non-positive value
		if(arr[i] > 0)
		{
			arr[count++] = arr[i];
		}
		
	*arr_count = count;

	if (tracemode)
	{
		trace(robot, 3);
		trace(mine, 4);
	}
}
   
void sortRobots(void)
{
	consolidate(robot, &robotcount);
	if(robotcount<1) finishLevel(); 
	// printStats();
}

void moveRobots()
{
   if(advanceRobots()) // moves each robot
   {
      if (!alive) return;
      sortRobots();
      if (alive == 1) refreshboard();
   }
   else
   {
      y = oldy;
      x = oldx;
   }
}

/***
 advanceRobots()
 
 	compute new position for each robot and check to see if robot has caught the human

 	if player has pressed 's' for safeMode (then player believes the human is safe)
		if robot catches player, call youLose()
 	if NOT in safe mode and robot catches player, then return 0 (don't actually move the robots)

 	after computing all the new robot positions, count them, deleting any robot that ran into a mine
	if all robots are destroyed, call finishLevel()
*/      
int advanceRobots()
{
	int count = 0;
	int i, j, roboty, robotx;
	int caught = 0;
   
	for(i=0; i<robotcount; i++) // copy all robot positions
		clone[i] = robot[i];

	for(i=0; i<robotcount; i++) // Move robots
	{
		roboty = abs(robot[i] / 100);
		robotx = abs(robot[i] - (roboty * 100));
		if(y<roboty) roboty = roboty - 1;
		if(y>roboty) roboty = roboty + 1;
		if(x<robotx) robotx = robotx - 1;
		if(x>robotx) robotx = robotx + 1;

		robot[i] = roboty * 100 + robotx;
      
		if(robot[i] == y * 100 + x) // the robot caught the man
		{
			caught = 1;
			hit = 'x';
			if(safeMode == 1) // you can only lose if you are in safeMode (user pressed 's')
			{
				youLose(i);
				return(1);
			}			
		}

		for(j=0; j<minecount; j++)  // see if new positions are = to any mines
			if(mine[j] == robot[i]) robot[i] = 0;
	}
	if((caught) && (safeMode == 0)) // player DID NOT press 's', so DON'T kill player
	{
		for(i=0; i<robotcount; i++) robot[i] = clone[i];
		return(0); // don't need to refresh the board
	}
	for(i=0; i<robotcount; i++) // delete any robots that ran into a mine
		if(robot[i] > 0) robot[count++] = robot[i]; // go to next
	robotcount = count;
	if(robotcount<1) 
		finishLevel();
	return(1); 
}     
