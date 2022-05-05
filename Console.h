#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>

#define DW 8
#define DH 8

typedef struct ConsoleDimensions {
	int WIDTH, HEIGHT;
	int cWIDTH, cHEIGHT;
	int dW, dH;
	int bWIDTH, bHEIGHT;
	int bAREA;
} ConDimensions;

typedef struct ConsoleTypes {
	HWND Console;
	HANDLE CInHandle;
	HANDLE COutHandle;
	COORD Coords;
	LPDWORD PtrCW;
} ConTypes;

typedef struct ConsoleWrapper {
	ConDimensions CD;
	ConTypes CT;
	unsigned short* buf;
} ConWrap;

int InitalizeConsole (ConWrap* CW) {

	AllocConsole();

	CW->CD.WIDTH = GetDeviceCaps(GetDC(NULL), HORZRES), CW->CD.HEIGHT = GetDeviceCaps(GetDC(NULL), VERTRES);
	CW->CD.cWIDTH = CW->CD.WIDTH, CW->CD.cHEIGHT = CW->CD.HEIGHT;									//	Console dimensions
	CW->CD.dW = DW, CW->CD.dH = DH;																	//	Size of characters
	CW->CD.bWIDTH = CW->CD.cWIDTH / CW->CD.dW, CW->CD.bHEIGHT = CW->CD.cHEIGHT / CW->CD.dH;			//	Number of characters
	CW->CD.bAREA = CW->CD.bWIDTH * CW->CD.bHEIGHT;

	CW->buf = (unsigned short*)calloc(CW->CD.bAREA, sizeof(short));
	if (CW->buf == NULL) return -1;
	
	CW->CT.Console = GetConsoleWindow();
	CW->CT.CInHandle = GetStdHandle(STD_INPUT_HANDLE);
	CW->CT.COutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CW->CT.Coords.X = 0;
	CW->CT.Coords.Y = 0;
	CW->CT.PtrCW = (LPDWORD)malloc(sizeof(DWORD));

	//	Console Font Size
	CONSOLE_FONT_INFOEX cf = { 0 };
	cf.cbSize = sizeof cf;
	cf.dwFontSize.X = DW;
	cf.dwFontSize.Y = DH;
	wcsncpy(cf.FaceName, L"Terminal", 16);

	SetConsoleTitleA("Morpheus, Dorpheus, Orpheus, Go eat some walruses");

	//	Console Screen Buffer Info
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(CW->CT.COutHandle, &csbi);
	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;

	//	Disable Cursor
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;

	SetConsoleMode(CW->CT.COutHandle, ENABLE_PROCESSED_OUTPUT);
	SetConsoleScreenBufferSize(CW->CT.COutHandle, csbi.dwSize);					//	Creates screen buffer
	SetCurrentConsoleFontEx(CW->CT.COutHandle, 0, &cf);							//	Sets font size
	SetConsoleDisplayMode(CW->CT.COutHandle, CONSOLE_FULLSCREEN_MODE, 0);		//	Go fullscreen
	SetConsoleCursorInfo(CW->CT.COutHandle, &info);								//	Hide cursor
	ShowScrollBar(CW->CT.Console, SB_BOTH, FALSE);								//	Hide scrollbar

	return 0;

}

void DestroyConsole(ConWrap* CW) {
	free(CW->CT.PtrCW);
	free(CW->buf);
}

void pushCoords(ConWrap* CW, int x, int y) {
	CW->CT.Coords.X = x;
	CW->CT.Coords.Y = y;
	SetConsoleCursorPosition(CW->CT.COutHandle, CW->CT.Coords);
}

#endif
