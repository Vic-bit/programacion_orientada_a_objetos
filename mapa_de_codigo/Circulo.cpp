#include <string>
#include <sstream>
#include "Circulo.h"
#include "EntidadGeometrica.h"

Circulo::Circulo(int color, int Cx, int Cy, double radio) :EntidadGeometrica(color) {
	this->Cx = Cx;
	this->Cy = Cy;
	this->radio = radio;
}

double Circulo::getPerimetro() {
	double perimetro=0;
	perimetro = 2 * 3.14 * radio;
	double &peri = perimetro;
	return perimetro;
}

double Circulo::getArea() {
	double area=0;
	area = 3.14 * radio * radio;
	return area;
}

string Circulo::toString() {
	stringstream ss;
	ss << "Circulo	"<< Cx << ", " << Cy<<"	"<< radio<<"	" << endl;
	return ss.str();
}
