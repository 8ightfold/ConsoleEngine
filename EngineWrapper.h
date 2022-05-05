#ifndef ENGINEWRAPPER_H
#define ENGINEWRAPPER_H

#include <Windows.h>
#include "Console.h"
#include "Draw.h"

typedef struct Engine {
	struct ConsoleWrapper* CWr;
	struct DrawWrapper* DWr;
} EFgen;

int Initalize(EFgen** eng) {
	
	if (eng == NULL) return -1;
	int ret = 0;

	*eng = (EFgen*)malloc(sizeof(EFgen));
	if (*eng == NULL) return -1;

	(*eng)->CWr = (struct ConsoleWrapper*) malloc(sizeof(struct ConsoleWrapper));
	if ((*eng)->CWr == NULL) return -1;
	ret = ret + InitalizeConsole((*eng)->CWr);

	(*eng)->DWr = (struct DrawWrapper*) malloc(sizeof(struct DrawWrapper));
	if ((*eng)->DWr == NULL) return -2;
	ret = ret + InitalizeDraw((*eng)->DWr);

	return ret;
}

void Execute(EFgen* eng, void(*func)(EFgen*)) { func(eng); }

void Draw(EFgen* eng) {
	WriteConsoleOutputCharacter(eng->CWr->CT.COutHandle, (LPCSTR)eng->CWr->buf, 
		eng->CWr->CD.bAREA, eng->CWr->CT.Coords, eng->CWr->CT.PtrCW);
}


void Destroy(EFgen** eng) {
	DestroyConsole((*eng)->CWr);
	free((*eng)->CWr);
	DestroyDraw((*eng)->DWr);
	free((*eng)->DWr);
	free(*eng);
}


#endif