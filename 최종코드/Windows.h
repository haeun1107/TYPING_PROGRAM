#ifndef Windows_h
#define Windows_h

#include <unistd.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
using namespace std;

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 

#define FALSE 0
#define TRUE 1

#define STD_OUTPUT_HANDLE 1
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.

class COORD {
    public:
        int x;
        int y;
};

class CONSOLE_CURSOR_INFO {
    public:
        int bVisible;
        int dwSize;
};

int GetStdHandle(int a) {
    return 1;
}

void printColorString(int color) {
    cout << "\033[" << color << "m";
}

const int dcolor[] = { 0, 4, 2, 6, 1, 5, 3, 7, 0, 4, 2, 6, 1, 5, 3, 7 };

void ColorChange(unsigned short color) {
    int FG = (color & 0x000F);

    int FG_isIntensity = (color & FOREGROUND_INTENSITY) ? 60 : 0;
    int result_foreground = 30 + FG_isIntensity;

    result_foreground += dcolor[FG];
    printColorString(result_foreground);
}

void SetConsoleTextAttribute(int handle, int color) {
    ColorChange(color);
}

#endif /* Windows_h */
