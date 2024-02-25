#include <iostream>
#include "Rectangulo.h"
#include "EntidadGeometrica.h"

Rectangulo::Rectangulo(int color, int Ax, int Ay, double base, double altura) : EntidadGeometrica(color) {
	this-> Ax = Ax;
	this-> Ay = Ay;
	this-> base = base;
	this->altura = altura;
}

double Rectangulo::getPerimetro() {
	double perimetro=0;
	perimetro = 2 * base + 2 * altura;
	return perimetro;
}

double Rectangulo::getArea() {
	double area=0;
	area = base * altura;
	return area;
}