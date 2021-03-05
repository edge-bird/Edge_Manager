#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <shellapi.h>
#include <conio.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

using namespace std;

const int MAXN = 1e7 + 1;

struct Button{ // Button
	int x, y, color;
	const char *name;
	int len;
};

void GetPos (POINT &pt){ // Mouse Pos to screen
	HWND hwnd = GetForegroundWindow ();
	GetCursorPos (&pt);
	ScreenToClient (hwnd, &pt);
	pt.y /= 16, pt.x /= 16;	
}

void color (int color_code){ // Text Color
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color_code);
}

void gto (int x, int y){ // move mouse
	COORD pos;
	pos.X = y * 2, pos.Y = x * 2;
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), pos); 
}

Button NewButton (int x, int y, int color, const char *name){ // Creat a new Button
	Button t;
	t.x = x, t.y = y, t.name = name;
	t.color = color;
	t.len = strlen (name);
	return t;
}

bool Preserve (Button A){ // preserve a Button
	gto (A.x, A.y), color (A.color), printf ("%s", A.name);
	POINT pt;
	GetPos (pt);
	if (pt.x && (pt.x >= A.y && pt.x <= A.y + A.len / 2)){
		color (A.color + 16), gto (A.x, A.y), printf ("%s", A.name);
		if (KEY_DOWN (MOUSE_MOVED)) return 1; // click
	}
	
	return 0; // no
}

void init (){ // initialization
	SetConsoleTitle ("Edge_Manager"); // Title
	color (15); // text:white
}

int main (){
	init ();
	Button A = NewButton (1, 2, 15, "setting");
	while (1)
	{
		if (Preserve (A))
		{
			Setting ();
		}
		Sleep (100);
	}
	exit (0);
}
