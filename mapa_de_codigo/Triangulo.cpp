#include <cmath>
#include "Triangulo.h"
#include "EntidadGeometrica.h"

Triangulo::Triangulo(int color, int Ax, int Ay, int Bx, int By, int Cx, int Cy) : EntidadGeometrica(color) {
	this->Ax = Ax;
	this->Ay = Ay;
	this->Bx = Bx;
	this->By = By;
	this->Cx = Cx;
	this->Cy = Cy;
}

double Triangulo::getPerimetro() {
	double perimetro=0;
	float a = pow((Bx - Ax) * (Bx - Ax) + (By - Ay) * (By - Ay), 0.5);
	float b = pow((Cx - Bx) * (Cx - Bx) + (Cy - By) * (Cy - By), 0.5);
	float c = pow((Ax - Cx) * (Ax - Cx) + (Ay - Cy) * (Ay - Cy), 0.5);
	perimetro = a + b + c;
	return perimetro;
}

double Triangulo::getArea() {
	double area=0;
	double a = pow((Bx - Ax) * (Bx - Ax) + (By - Ay) * (By - Ay), 0.5);
	double b = pow((Cx - Bx) * (Cx - Bx) + (Cy - By) * (Cy - By), 0.5);
	double c = pow((Ax - Cx) * (Ax - Cx) + (Ay - Cy) * (Ay - Cy), 0.5);
	double s = (a+b+c)/2;
	area = pow(s * (s - a) * (s - b) * (s - c), 0.5);
	return area;
}
