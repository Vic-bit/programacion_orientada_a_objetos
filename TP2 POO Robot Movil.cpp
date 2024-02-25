//Trabajo Práctico 2a 
//1 - Robot Móvil
//Alumnos:	Araujo, Juan Ingnacio	10649
//		Silva, Víctor	10988

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <ctime>
using namespace std;
#include "Trayectoria.h"
#include "Movimiento.h"


int main()
{
	char elegir;
	cout << "C: Comenzar" << endl;
	cout << "P: Parar" << endl;
	cout << "M: Reporte" << endl;
	cout << "A: Avanzar" << endl;
	cout << "R: Retroceder" << endl;
	cout << "I: Izquierda" << endl;
	cout << "D: Derecha" << endl;
	cout << "G: Girar" << endl;
	cin >> elegir;

	if (elegir==COMENZAR)
	{
		cout << "Se encendio el robot" << endl;
		list <string> Ordenes;

		Trayectoria* trayecto;
		trayecto = new Trayectoria("", Ordenes, 0, 0, 0);

		string cadena;

		while (cadena[0] !=PARAR) {
			cout << "Ingrese el comando: " << endl;
			cin >> cadena;
			if (trayecto->esOrdenValida(cadena) == true)
			{
				cout << "OK" << endl;
				trayecto->ejecutarOrden();
			}
		}
		delete trayecto;
	}
	return 0;
}