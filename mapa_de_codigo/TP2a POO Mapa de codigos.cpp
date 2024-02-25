//Trabajo Práctico 2a 
//2 - Robot Móvil
//Alumnos:	Araujo, Juan Ingnacio	10649
//		Silva, Víctor	10988

#include <iostream>
#include <string>
#include <list>
#include <stdlib.h>
#include <fstream>
using namespace std;
#include "Generador.h"
#include "EntidadGeometrica.h"
#include "Triangulo.h"
#include "Rectangulo.h"
#include "Circulo.h"

int main()
{
	cout << "Ingrese el nombre del archivo a leer sin el .txt: " << endl;
	cout << "Ejemplos: " << endl;
	cout << "	Caso 1 : Datos1" << endl;
	cout << "	Caso 2 : Datos2" << endl;
	cout << "	Caso 3 : Datos3 (ejemplo propuesto en la consigna)" << endl;

	string nombreArchivo;
	cin >> nombreArchivo;

	Generador* generar;
	generar = new Generador(nombreArchivo, false, 0, 0, 0);

	if (generar->generarMapa() == true) {
		cout << "Mapa valido!" << endl;
		generar->analizarArchivo();
	}

	delete generar;

	return 0;
}