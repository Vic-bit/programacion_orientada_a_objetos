#pragma once
#include "EntidadGeometrica.h"
class Triangulo: public EntidadGeometrica
{
private:
	int Ax;
	int Ay;
	int Bx;
	int By;
	int Cx;
	int Cy;
public:
	Triangulo(int color, int Ax, int Ay, int Bx, int By, int Cx, int Cy);
	double getPerimetro();
	double getArea();
	~Triangulo();
};

