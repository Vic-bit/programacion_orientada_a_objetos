#pragma once
#include "EntidadGeometrica.h"

class Rectangulo: public EntidadGeometrica
{
private:
	int Ax;
	int Ay;
	double base=0;
	double altura=0;
public:
	Rectangulo(int color, int Ax, int Ay, double base, double altura);
	double getPerimetro();
	double getArea();
	~Rectangulo();
};

