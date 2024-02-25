#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <math.h>
#include <sstream>
#include <ctime>
using namespace std;
#include "Trayectoria.h"
#include "Movimiento.h"


Trayectoria::Trayectoria(string ordenActual, list<string> Ordenes, float distanciaTotal, int tiempoTotal, unsigned int tiempoInicial){
	this->ordenActual = ordenActual;
	this->Ordenes = Ordenes;
	this->distanciaTotal = distanciaTotal;
	this->tiempoTotal = tiempoTotal;
	this->tiempoInicial = tiempoInicial;
}


Trayectoria::~Trayectoria() {
	cout << calcularTiempoVida(tiempoInicial);
}


bool Trayectoria::esOrdenValida(string cadena) {
	
	if (((cadena[0] == AVANZAR || cadena[0] == RETROCEDER || cadena[0] == DERECHA ||
		cadena[0] == IZQUIERDA) && (cadena[1]>='0' && cadena[1]<='9')) || (cadena[0] == GIRAR && (cadena[1] == 'H' || cadena[1] == 'A')) || cadena[0]== REPORTE)		//Agregar del 0 al 9
	{
		ordenActual = cadena;
		setOrdenActual(ordenActual);
		return true;
	}
	else {
		return false;
	}
}


void Trayectoria::setOrdenActual(string ordenActual)
{
	this->ordenActual = ordenActual;
}


void Trayectoria::ejecutarOrden() {
	float cantidad;
	cantidad = ordenActual[1] - '0';
	switch (ordenActual[0]) {
	case AVANZAR:
		if (orientacion == "1000") { y = y + 4.25 * cantidad; 	break; }
		if (orientacion == "0100") { y = y - 4.25 * cantidad; 	break; }
		if (orientacion == "0010") { x = x + 4.25 * cantidad;	break; }
		if (orientacion == "0001") { x = x - 4.25 * cantidad; 	break; }
	case RETROCEDER:
		if (orientacion == "1000") { y = y - 4.25 * cantidad; 	break; }
		if (orientacion == "0100") { y = y + 4.25 * cantidad; 	break; }
		if (orientacion == "0010") { x = x - 4.25 * cantidad; 	break; }
		if (orientacion == "0001") { x = x + 4.25 * cantidad; 	break; }
	case DERECHA:		
		if (orientacion == "1000") { orientacion = "0010";	x = x + 4.25 * cantidad; 	break; }
		if (orientacion == "0100") { orientacion = "0001";	x = x - 4.25 * cantidad; 	break; }
		if (orientacion == "0010") { orientacion = "0100";	y = y - 4.25 * cantidad; 	break; }
		if (orientacion == "0001") { orientacion = "1000";	y = y + 4.25 * cantidad; 	break; }
	case IZQUIERDA:
		if (orientacion == "1000") { orientacion = "0001";	x = x - 4.25 * cantidad; 	break; }
		if (orientacion == "0100") { orientacion = "0010";	x = x + 4.25 * cantidad; 	break; }
		if (orientacion == "0010") { orientacion = "1000";	y = y + 4.25 * cantidad; 	break; }
		if (orientacion == "0001") { orientacion = "0100";	y = y - 4.25 * cantidad; 	break; }
	case GIRAR:
		if (orientacion == "1000" ) { orientacion = "0100";	break; }
		if (orientacion == "0100" ) { orientacion = "1000";	break; }
		if (orientacion == "0010" ) { orientacion = "0001";	break;}
		if (orientacion == "0001" ) { orientacion = "0010";	break; }
	}

	if (ordenActual[0]!=REPORTE)
	{
		tiempoTotal = tiempoTotal + 2;
		cout << "La orientacion es: " << orientacion <<endl;
		actualizarEstado();
		cout << "Estado actualizado" << endl;
	}
	
	if (ordenActual[0]==REPORTE)
	{
		cout << "La lista de Ordenes es: " << endl;
		getOrdenes();
		cout << "La distancia total es: " << this->getDistanciaTotal() << endl;
		cout << "El tiempo total es: " <<this->getTiempoTotal()<<endl;
		getOrdenes(AVANZAR);
		getOrdenes(RETROCEDER);
		getOrdenes(DERECHA);
		getOrdenes(IZQUIERDA);
		getOrdenes(GIRAR);
	}
}


void Trayectoria::actualizarEstado() {
		Ordenes.push_back(ordenActual);
		if (ordenActual[0] == AVANZAR) { cantidadOrdenesAvanzar.push_back(AVANZAR); }
		if (ordenActual[0] == RETROCEDER) { cantidadOrdenesRetroceder.push_back(RETROCEDER); }
		if (ordenActual[0] == IZQUIERDA) { cantidadOrdenesIzquierda.push_back(IZQUIERDA); }
		if (ordenActual[0] == DERECHA) { cantidadOrdenesDerecha.push_back(DERECHA); }
		if (ordenActual[0] == GIRAR) { cantidadOrdenesGirar.push_back(GIRAR); }
}


list<string> Trayectoria::getOrdenes()
{
	list<string>::iterator it = Ordenes.begin();
	while (it != Ordenes.end())
	{
		cout << "\t" << *it++ << endl;
	}
	return Ordenes;
}


float Trayectoria::getDistanciaTotal()
{
	distanciaTotal = pow(x * x + y * y, 0.5);
	return distanciaTotal;
}


list<char> Trayectoria::getOrdenes(char Mov)
{
	int cont = 0;
	if (Mov==AVANZAR) { 
		list<char>::iterator it = cantidadOrdenesAvanzar.begin();
		while (it != cantidadOrdenesAvanzar.end())
		{
			if (*it==AVANZAR)
			{
				cont = cont + 1;
				*it++;
			}
		}
		cout << "La cantidad de veces que ha avanzado es: "<< cont << endl;
		return cantidadOrdenesAvanzar;
	}
	cont = 0;
	if (Mov == RETROCEDER) {
		list<char>::iterator it = cantidadOrdenesRetroceder.begin();
		while (it != cantidadOrdenesRetroceder.end())
		{
			if (*it == RETROCEDER)
			{
				cont = cont + 1;
				*it++;
			}
		}
		cout << "La cantidad de veces que ha retrocedido es: " << cont << endl;
		return cantidadOrdenesRetroceder;
	}
	cont = 0;
	if (Mov == IZQUIERDA) {
		list<char>::iterator it = cantidadOrdenesIzquierda.begin();
		while (it != cantidadOrdenesIzquierda.end())
		{
			if (*it == IZQUIERDA)
			{
				cont = cont + 1;
				*it++;
			}
		}
		cout << "La cantidad de veces que ha ido hacia la izquierda es: " << cont << endl;
		return cantidadOrdenesIzquierda;
	}
	cont = 0;
	if (Mov == DERECHA) {
		list<char>::iterator it = cantidadOrdenesDerecha.begin();
		while (it != cantidadOrdenesDerecha.end())
		{
			if (*it == DERECHA)
			{
				cont = cont + 1;
				*it++;
			}
		}
		cout << "La cantidad de veces que ha ido hacia la derecha es: " << cont << endl;
		return cantidadOrdenesDerecha;
	}
	cont = 0;
	if (Mov == GIRAR) {
		list<char>::iterator it = cantidadOrdenesGirar.begin();
		while (it != cantidadOrdenesGirar.end())
		{
			if (*it == GIRAR)
			{
				cont = cont + 1;
				*it++;
			}
		}
		cout << "La cantidad de veces que ha girado es: " << cont << endl;
		return cantidadOrdenesGirar;
	}
}


string Trayectoria::calcularTiempoVida(unsigned int tiempoInicial) {
	ostringstream aux;
	unsigned t1;
	t1 = clock();
	double time = (double(t1 - tiempoInicial) / CLOCKS_PER_SEC);
	aux << "Tiempo de ejecucion desde la instanciacion es de: " << time << " segundos" << endl;
	return aux.str();
}


int Trayectoria::getTiempoTotal()
{
    return tiempoTotal;
}