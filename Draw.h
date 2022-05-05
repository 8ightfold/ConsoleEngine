#ifndef DRAW_H
#define DRAW_H

#include <Windows.h>

typedef struct Vertex {
    int X;
    int Y;
} Vert;

typedef struct Line {
    Vert A;
    Vert B;
} L;

typedef struct Vector {
    double X;
    double Y;
    double Z;
} V;

typedef struct Face {
    V A;
    V B;
    V C;
} F;

typedef struct Object {
    F* Mesh;
    long nFaces;
    V Rotation;
    V Translation;
    V Scale;
} Obj;

typedef struct DrawWrapper {
    Obj* Objects;
    int nObjects;
    L* Lines;
    int nLines;
} DrawWrap;

int InitalizeDraw(struct DrawWrapper* DWr) {
    DWr->Objects = (Obj*)calloc(16, sizeof(Obj));
    if (DWr->Objects == NULL) return -1;
    DWr->nObjects = 0;
    DWr->Lines = (L*)calloc(16, sizeof(L));
    if (DWr->Lines == NULL) return -2;
    DWr->nLines = 0;

    return 0;
}

int DestroyDraw(struct DrawWrapper* DWr) {
    free(DWr->Objects);
    free(DWr->Lines);
}

#endif
