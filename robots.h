// robots.h
// by Chris Minich
// cfminich@gmail.com

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>   // for rand
#include <stdlib.h> // for rand
#include <string.h>

#define LIMIT 500 // was 400
//#define LIMIT 200  // test win function
#define INCREMENT 25 // additional robots per level
#define START 150
#define WIDTH 70
#define HEIGHT 30
#define esc 27
#define cls printf("%c[2J",esc)
#define pos(row,col) printf("%c[%d;%dH",esc,row,col)
#define BLUE 34 // foreground colors are in the 30s
#define CYAN 36
#define GREEN 32
#define RED 31
#define YELLOW 33
#define WHITE 37
#define BLACK 40 // background color (since it is 40 and not 30)
#define FOREGROUND "\x1b[%d;1m"
#define BACKGROUND "\x1b[%dm"
#define NORMAL "%c[0m",esc
#define UNBOLD "%c[22m",esc
#define ROBOT "\x1b[%d;1m@"
#define MINE  "\x1b[%d;1m#"
#define HUMAN "\x1b[%d;1mH"
#define BOARD "\x1b[%dm."
#define OS_DEFAULT "\x1b[39;49;0m"
#define GREEN_SCORES "%c[32;44;1m",esc
#define WHITE_INFO "%c[37;1m",esc

int robot[LIMIT], maxrobots = START - INCREMENT; // maxrobots will increase each level
int mine[LIMIT];
int minecount = 0;
int robotcount = 0;
int clone[LIMIT]; // copy of all robots. Purpose is to revert after invalid move by (H) into a robot.
int y, x; // position of (H)uman
int oldy, oldx; // previous position of (H)uman
int alive = 1, points = 0;
int safeTeleports = 0;
int safeMode = 0;
int init = 1; // set-up mode
char hit = 'x'; // Human caught by: x is by a robot. @ is by transport on top of a robot. # is by transport onto a mine.
int color = 0; // values are: 0 for off, and 1 for on
int bg = 40; // all backgrounds are numbers in the 40s
int tracemode = 0;
int mega_teleports_achieved = 0;
int start_amt = 0; // number of robots successfully instantiated for each level
int level = 0;
int offset = 1; // top menu height
int bottom = 0; // bottom line - will be computed by printstats()

//helpers.c
int mygetch( void );
void trace(int* arr, int col);

//board.c
void makeBoard();
void refreshboard();
void printStats();
void finishLevel();
void youLose(int killer);
void message(int n);

//place.c
void placeAllMines(void);
void placeAllRobots();
void placeMine(int mine);
int insertIntoArray(int new, int size);
int getNewCoordinates();
void makeRobots(int max);

//moverobots.c
void consolidate(int* arr, int* arr_count);
void sortRobots(void);
void moveRobots();
int advanceRobots();

//human.c
int humanUnSafe(int location);
int validateMove(int yy, int xx);
int trymove(char d1, char d2);
int teleport();
void pteleport();
