#pragma once
#include <string>
#include <list>
#include <vector>
using namespace std;
#include "Movimiento.h"

class Trayectoria
{
private:
	string ordenActual;
	list<string> Ordenes;
	float distanciaTotal;
	int tiempoTotal;
	unsigned int tiempoInicial;
	string orientacion = "1000";	//"Norte, Sur, Oeste, Este
	float x=0;
	float y=0;
	list<char> cantidadOrdenesAvanzar;
	list<char> cantidadOrdenesRetroceder;
	list<char> cantidadOrdenesIzquierda;
	list<char> cantidadOrdenesDerecha;
	list<char> cantidadOrdenesGirar;
public:
	Trayectoria(string ordenActual, list<string> Ordenes, float distanciaTotal, int tiempoTotal, unsigned int tiempoInicial);
	~Trayectoria();
	void actualizarEstado();	//No sé aún
	string calcularTiempoVida(unsigned t0);
	void ejecutarOrden();
	bool esOrdenValida(string cadena);
	float getDistanciaTotal();
	void setOrdenActual(string ordenActual);
	list<string> getOrdenes();
	list<char> getOrdenes(char Mov);
	int getTiempoTotal();
};