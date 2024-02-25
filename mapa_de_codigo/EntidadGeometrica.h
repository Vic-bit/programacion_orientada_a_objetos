#pragma once
//using namespace std;

class EntidadGeometrica
{
private:
	char color;
public:
	double getArea();
	double getPerimetro();
	EntidadGeometrica(char color);
	~EntidadGeometrica();
};

