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

/*
int toStrCoords(int& x, int& y) {
    if (y != 0) return x + ((y - 1) * sW);
    return x + (y * sW);
}

void drawPoint(std::string& s, int& x, int& y, char c) {
    if (x < 0 || y < 0 || y > 180 || x > 480) return;
    s[toStrCoords(x, y)] = c;
}

void plotLineLow(std::string& s, int& x0, int& y0, int& x1, int& y1, char& c) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = ~dy + 1;
    }
    int D = (2 * dy) - dx;
    int y = y0;
    for (int i = x0; i < x1; i++) {
        drawPoint(s, i, y, c);
        if (D > 0) {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else {
            D = D + 2 * dy;
        }
    }
}

void plotLineHigh(std::string& s, int& x0, int& y0, int& x1, int& y1, char& c) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = ~dx + 1;
    }
    int D = (2 * dx) - dy;
    int x = x0;
    for (int i = y0; i < y1; i++) {
        drawPoint(s, x, i, c);
        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else {
            D = D + 2 * dx;
        }
    }
}

//dW = 480, dH = 180
//bresenham's algorithm
void drawLine(std::string& s, int x1, int y1, int x2, int y2, char c) {

    //reverse values if needed
    if (x1 > x2) {
        int tmp;
        tmp = x1;
        x1 = x2;
        x2 = tmp;

        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    if (abs(y2 - y1) < abs(x2 - x1)) {
        plotLineLow(s, x1, y1, x2, y2, c);
        return;
    }
    if (y1 > y2) {
        plotLineHigh(s, x2, y2, x1, y1, c);
        return;
    }
    plotLineHigh(s, x1, y1, x2, y2, c);
}
*/

#endif