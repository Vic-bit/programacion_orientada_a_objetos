#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <list>
#include <sstream>
using namespace std;
#include "Generador.h"
#include "Rectangulo.h"
#include "Circulo.h"
#include "Triangulo.h"

Generador::Generador(string nombreArchivo, bool coloresDiferentes, char** mapa, int resol_x, int resol_y) {
	this->nombreArchivo = nombreArchivo;
	this->coloresDiferentes = coloresDiferentes;
	this->mapa = mapa;
	this->resol_x = resol_x;
	this->resol_y = resol_y;
}

bool Generador::generarMapa() {

	ostringstream archivo;
	archivo << nombreArchivo << ".txt";
	fstream archivoEntrada;
	archivoEntrada.open(archivo.str(), ios::in);

	archivo.str("");
	archivo << nombreArchivo << "mapa" << ".txt";
	ofstream archivoGenerado;
	archivoGenerado.open(archivo.str());

	bool mapaValido = false;
	char letra;
	char relleno;
	int salto = 0;
	int linea = 0;	
	bool figuraValida=true;
	bool colorValido=false;

	string figura;
	int errores = 0;
	string colorAnterior = "000000000";

	int color = 0;
	int Ax = 0;
	int Ay = 0;
	int Bx = 0;
	int By = 0;
	int Cx = 0;
	int Cy = 0;
	int base = 0;
	int altura = 0;
	int radio = 0;
	int rect=0;
	int triangulo=0;
	int rectangulo=0;
	int circulo=0;
	float areaOcupada = 0;
	ostringstream aux;
//---------------------------------	Leo el archivo------------------------------------------------------------
	if (archivoEntrada.is_open()) {
		while (!archivoEntrada.eof()) {
			archivoEntrada.get(letra);

			if (figuraValida == false) {
				if (letra == '\n') {
					linea = linea + 1;
					figuraValida = true;
					salto = 0;
				}
				continue;
			}

			if (letra == ' ') {
				continue;
			}


			if (letra == '\n' && figuraValida==true)
			{	
				if (linea==0) {
					aux.str("");
					aux << "Resolucion: " << resol_x << "x" << resol_y << " puntos";
					listaArchivo.push_back(aux.str());
					aux.str("");
					if (relleno == '!' || relleno == '"' || relleno == '#' || relleno == '$' || relleno == '%' || relleno == '&' || relleno == '(' ||
						relleno == ')' || relleno == '*' || relleno == '+' || relleno == ',' || relleno == '-' || relleno == '.' || relleno == '/') {
						aux.str("");
						aux << "Relleno personalizado: " << relleno;
						listaArchivo.push_back(aux.str());
					}
					else {
						aux.str("");
						aux << "Relleno personalizado: default(0)";
						listaArchivo.push_back(aux.str());
					}
					aux.str("");
					listaArchivo.push_back(aux.str());					
					aux.str("");
					aux << "Figura		" << "Color		" << "A/Centro	" << "B/radio/base	" << "C/altura	" << "Perimetro	" << "Superficie";
					listaArchivo.push_back(aux.str());
					aux.str("");
					listaArchivo.push_back(aux.str());
					salto = 0;
					linea = linea + 1;
					continue;
				}

				if (figura == "Rectangulo" && linea != 0)
				{
					linea = linea + 1;
					if (salto != 5) {
						errores = errores + 1;
						aux.str("");
						listaArchivo.push_back("Error (parametros invalidos)");
						Ax = 0;
						Ay = 0;
						base = 0;
						altura = 0;
						salto = 0;
						continue;
					}
					if (Ax > resol_x || Ax+ base > resol_x || Ay > resol_y || Ay+altura > resol_y) {
						errores = errores + 1;
						aux.str("");
						listaArchivo.push_back("Error (fuera de rango)");
						Ax = 0;
						Ay = 0;
						base = 0;
						altura=0;
						salto = 0;
						continue;
					}
					Rectangulo * objetoRectangulo;
					objetoRectangulo = new Rectangulo(color, Ax, Ay, base, altura);
					double perimetro = objetoRectangulo->getPerimetro();
					double area = objetoRectangulo->getArea();
					aux.str("");
					aux << "Rectangulo	" << color << "		" << Ax << ", " << Ay << "		" << base << "		" <<
						altura << "		" << objetoRectangulo->getPerimetro() << "		" << objetoRectangulo->getArea();
					listaArchivo.push_back(aux.str());


					for (int i = Ax; i <= base + Ax; i++)
					{
						*(*(mapa + i) + Ay) = color + '0';
					}
					for (int j = Ay; j <= altura + Ay; j++)
					{
						*(*(mapa + Ax) + j) = color + '0';
					}
					for (int i = Ax; i <= base + Ax; i++)
					{
						*(*(mapa + i) + (Ay+altura)) = color + '0';
					}
					for (int j = Ay; j <= altura + Ay; j++)
					{
						*(*(mapa + (Ax+base)) + j) = color + '0';
					}
		
					areaOcupada = areaOcupada + objetoRectangulo->getArea();
					rectangulo = rectangulo + 1;
					Ax = 0;
					Ay = 0;
					base = 0;
					altura = 0;
					salto = 0;
					colorValido = false;
				}

				if (figura == "Circulo" && linea != 0)
				{
					linea = linea + 1;
					if (salto != 4) {
						errores = errores + 1;
						aux.str("");
						listaArchivo.push_back("Error (parametros invalidos)");
						Cx = 0;
						Cy = 0;
						radio = 0;
						salto = 0;
						continue;
					}
					if (Cx+radio > resol_x || Cx-radio < 0 || Cy+radio > resol_y || Cy-radio < 0) {
						errores = errores + 1;
						aux.str("");
						listaArchivo.push_back("Error (fuera de rango)");
						Cx = 0;
						Cy = 0;
						radio = 0;
						salto = 0;
						continue;
					}
					Circulo* objetoCirculo;
					objetoCirculo = new Circulo(color, Cx, Cy, radio);
					double perimetro = objetoCirculo->getPerimetro() ;
					double area = objetoCirculo->getArea();
					aux.str("");
					aux << "Circulo		" << color << "				" << radio <<"		"<< Cx << ", " << Cy << "		" << perimetro << "		" << area;
					listaArchivo.push_back(aux.str());

					for (int i = Cx-radio; i <= Cx+radio; i++)
					{
						float f = (pow(radio * radio - ((i - Cx) * (i - Cx)), 0.5) + Cy);
						int j = (int)f;
						float decimal = f - j;
						if (decimal > 0.5) {
							j = j + 1;
						}
						*(*(mapa + i) + j) = color + '0';
					}
					for (int i = Cx - radio; i <= Cx + radio; i++)
					{
						float f = (-pow(radio * radio - ((i - Cx) * (i - Cx)), 0.5) + Cy);
						int j = (int)f;
						float decimal = f - j;
						if (decimal > 0.5) {
							j = j + 1;
						}
						*(*(mapa + i) + j) = color + '0';
					}
					areaOcupada = areaOcupada + objetoCirculo->getArea();
					circulo = circulo + 1;
					Cx = 0;
					Cy = 0;
					radio = 0;
					salto = 0;
					colorValido = false;
				}

				if (figura == "Triangulo" && linea != 0)
				{
					linea = linea + 1;
					if (salto != 7) {
						errores = errores + 1;
						aux.str("");
						listaArchivo.push_back("Error (parametros invalidos)");
						Ax = 0;
						Ay = 0;
						Bx = 0;
						By = 0;
						Cx = 0;
						Cy = 0;
						salto = 0;
						continue;
					}

					if (Ax > resol_x || Bx > resol_x || Cx > resol_x || Ay > resol_y || By > resol_y || Cy > resol_y) {
						errores = errores + 1;
						aux.str("");
						listaArchivo.push_back("Error (fuera de rango)");
						Ax = 0;
						Ay = 0;
						Bx = 0;
						By = 0;
						Cx = 0;
						Cy = 0;
						salto = 0;
						continue;
					}
					Triangulo* objetoTriangulo;
					objetoTriangulo = new Triangulo(color, Ax, Ay, Bx, By, Cx, Cy);
					double perimetro = objetoTriangulo->getPerimetro();
					double area = objetoTriangulo->getArea();
					aux.str("");
					aux << "Triangulo	" << color << "		" << Ax << ", " << Ay << "		" << Bx << ", " << By
						<< "		" << Cx << ", " << Cy << "		" << perimetro << "		" << area;
					listaArchivo.push_back(aux.str());

					if (Bx >= Ax) {
						for (int i = Ax; i <= Bx; i++)
						{
							float f = ((float)(By - Ay) / (Bx - Ax)) * (i - Ax) + Ay;
							int j = (int)f;
							float decimal = f - j;
							if (decimal > 0.5) {
								j = j + 1;
							}
							*(*(mapa + i) + j) = color + '0';
						}
					}
					else if (Ax > Bx) {
						for (int i = Bx; i <= Ax; i++)
						{
							float f = ((float)(By - Ay) / (Bx - Ax)) * (i - Ax) + Ay;
							int j = (int)f;
							float decimal = f - j;
							if (decimal > 0.5) {
								j = j + 1;
							}
							*(*(mapa + i) + j) = color + '0';
						}
					}
					if (Cx >= Bx) {
						for (int i = Bx; i <= Cx; i++)
						{
							float f = ((float)(Cy - By) / (Cx - Bx)) * (i - Bx) + By;
							int j = (int)f;
							float decimal = f - j;
							if (decimal > 0.5) {
								j = j + 1;
							}
							*(*(mapa + i) + j) = color + '0';
						}
					}
					else if (Bx > Cx) {
						for (int i = Cx; i <= Bx; i++)
						{
							float f = ((float)(Cy - By) / (Cx - Bx)) * (i - Bx) + By;
							int j = (int)f;
							float decimal = f - j;
							if (decimal > 0.5) {
								j = j + 1;
							}
							*(*(mapa + i) + j) = color + '0';
						}
					}
					if (Cx >= Ax) {
						for (int i = Ax; i <= Cx; i++)
						{
							float f = ((float)(Cy - Ay) / (Cx - Ax)) * (i - Ax) + Ay;
							int j = (int)f;
							float decimal = f - j;
							if (decimal > 0.5) {
								j = j + 1;
							}
							*(*(mapa + i) + j) = color + '0';
						}
					}
					else if (Ax>Cx) {
						for (int i = Cx; i <= Ax; i++)
						{
							float f = ((float)(Cy - Ay) / (Cx - Ax)) * (i - Ax) + Ay;
							int j = (int)f;
							float decimal = f - j;
							if (decimal > 0.5) {
								j = j + 1;
							}
							*(*(mapa + i) + j) = color + '0';
						}
					}
					areaOcupada = areaOcupada + objetoTriangulo->getArea();
					triangulo = triangulo + 1;
					Ax = 0;
					Ay = 0;
					Bx = 0;
					By = 0;
					Cx = 0;
					Cy = 0;
					salto = 0;
					colorValido = false;
				}
				continue;
			}
//---------------------------------	Leo la primera línea------------------------------------------------------------
			if (linea == 0)
			{
				if (letra == ',')
				{
					salto = salto + 1;
					continue;
				}
				if (letra >= '0' && letra <= '9' && salto == 0)
				{
					resol_x = resol_x * 10 + (letra - '0');
					continue;
				}
				if (letra >= '0' && letra <= '9' && salto == 1)
				{
					resol_y = resol_y * 10 + (letra - '0');
					continue;
				}if (salto == 2)
				{
					mapa = new char* [resol_x+1];				
					for (int i = 0; i < resol_x+1; i++) {
						mapa[i] = new char[resol_y+1];
					}
					if (letra == '!' || letra == '"' || letra == '#' || letra == '$' || letra == '%' || letra == '&' || letra == '(' ||
						letra == ')' || letra == '*' || letra == '+' || letra == ',' || letra == '-' || letra == '.' || letra == '/') {
						relleno = letra;
						for (int i = 0; i < resol_x+1 ; i++)
						{
							for (int j = 0; j < resol_y+1 ; j++)
							{
								*(*(mapa + i) + j) = relleno;
							}
						}
					}
					else {
						relleno = '0';
						for (int i = 0; i < resol_x+1; i++)
						{
							for (int j = 0; j < resol_y+1; j++)
							{
								*(*(mapa + i) + j) = relleno;
							}
						}
						if (letra == '1') {
							coloresDiferentes = true;
						}
					}
					continue;
				}
				if (salto == 3) {
					if (letra == '1') {
						coloresDiferentes = true;
					}
					continue;
				}
			}
//---------------------------------	Leo las demás líneas ------------------------------------------------------------
			if (linea != 0)
			{
				if (letra == ',')
				{
					salto = salto + 1;
					continue;
				}
				if ((letra == 't' || letra == 'r' || letra == 'c') && salto == 0)
				{
					if (letra == 't') { figura = "Triangulo"; }
					if (letra == 'r') { figura = "Rectangulo"; }
					if (letra == 'c') { figura = "Circulo"; }
					continue;
				}
				else if ((letra != 't' || letra != 'r' || letra != 'c') && salto == 0)
				{
					errores = errores + 1;
					aux.str("");
					listaArchivo.push_back("Error (fig. no existe)");
					figuraValida = false;
					continue;
				}
				if (letra == '#' && salto == 1) {
					colorValido = true;
					continue;
				}

				if (letra > '0' && letra < '9' && salto == 1 && colorValido == true)	
				{
					if (coloresDiferentes == true) {
						if (letra - '0' != colorAnterior[letra - '0'])
						{
							colorAnterior[letra - '0'] = letra - '0';
							color = letra - '0';
							continue;
						}
						else {
							errores = errores + 1;
							figuraValida = false;
							aux.str("");
							listaArchivo.push_back("Error (color repetido)");
							continue;
						}
					}
					else {
						color = letra - '0';
					}
					continue;
				}
				else if (colorValido == false && (salto==1 || salto==2)) {
					if (color != 9) {
						salto = salto + 1;
					}
					color = 9;

					if (figura == "Triangulo" && letra >= '0' && letra <= '9')
					{
						Ax = Ax * 10 + (letra - '0');
						continue;
					}
					if (figura == "Rectangulo" && letra >= '0' && letra <= '9')
					{
						Ax = Ax * 10 + (letra - '0');
						continue;
					}
					if (figura == "Circulo" && letra >= '0' && letra <= '9')
					{
						Cx = Cx * 10 + (letra - '0');
						continue;
					}
					continue;
				}
//---------------------------------Parámetros de las figuras------------------------------------------------------------
				if (figura=="Triangulo")
				{
					if (letra >= '0' && letra <= '9' && salto == 2)
					{
						Ax = Ax * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 3)
					{
						Ay = Ay * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 4)
					{
						Bx = Bx * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 5)
					{
						By =By * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 6)
					{
						Cx = Cx * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 7)
					{
						Cy = Cy * 10 + (letra - '0');
						continue;
					}
				}
				
				if (figura == "Rectangulo")
				{
					if (letra >= '0' && letra <= '9' && salto == 2)
					{
						Ax = Ax * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 3)
					{
						Ay = Ay * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 4)
					{
						base = base * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 5)
					{
						altura = altura * 10 + (letra - '0');
						continue;
					}
				}

				if (figura == "Circulo")
				{
					if (letra >= '0' && letra <= '9' && salto == 2)
					{
						Cx = Cx * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 3)
					{
						Cy = Cy * 10 + (letra - '0');
						continue;
					}
					if (letra >= '0' && letra <= '9' && salto == 4)
					{
						radio = radio * 10 + (letra - '0');
						continue;
					}
				}	
			}
		}
//---------------------------------Mostrar figuras------------------------------------------------------------

		for (int i = resol_y; i >=0; i--)
		{
			for (int j = 0; j < resol_x + 1; j++)
			{
				archivoGenerado << *(*(mapa + j) + i);
			}
			archivoGenerado << "\n";
		}

		archivoEntrada.close();
	}
	else
	{
		cout << "Fichero inexistente" << endl;
	}
	archivoGenerado.close();

	float areas = 100 * (float) areaOcupada / (resol_x * resol_y);

	for (int i = 0; i < resol_x+1; i++) {	
		delete[] mapa[i];
	}
	delete[] mapa;

	aux.str("");
	listaArchivo.push_back(aux.str());
	aux.str("");
	aux << "Lineas de entidad en el archivo: " << linea-1;
	listaArchivo.push_back(aux.str());
	aux.str("");
	aux << "Errores: " << errores;
	listaArchivo.push_back(aux.str());
	aux.str("");
	aux << "Triangulos: " << triangulo;
	listaArchivo.push_back(aux.str());
	aux.str("");
	aux << "Rectangulo: " << rectangulo;
	listaArchivo.push_back(aux.str());
	aux.str("");
	aux << "Circulo: " << circulo;
	listaArchivo.push_back(aux.str());
	aux.str("");
	aux << "%Areas: " << areas;
	listaArchivo.push_back(aux.str());
	mapaValido = true;
	return mapaValido;
}

list<string> Generador::analizarArchivo() {
	ostringstream archivo;
	archivo << nombreArchivo << "reporte" << ".txt";
	ofstream archivoReporte;
	archivoReporte.open(archivo.str());
	for (auto it = listaArchivo.begin(); it != listaArchivo.end(); it++) {
		 archivoReporte<< *it << endl;
	}
	archivoReporte.close();

	return listaArchivo;
}