#pragma once
#include <string>
using namespace std;
#include "EntidadGeometrica.h"
class Circulo: public EntidadGeometrica
{
private:
	int Cx;
	int Cy;
	double radio;
public:
	Circulo(int color, int Cx, int Cy, double radio);
	double getPerimetro();
	double getArea();
	string toString();
	~Circulo();		
};

