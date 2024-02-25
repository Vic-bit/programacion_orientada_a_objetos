#pragma once
#include <string>
#include <list>
using namespace std;

class Generador
{
private:
	string nombreArchivo;
	bool coloresDiferentes;
	char** mapa;
	int resol_x;
	int resol_y;
	list <string> listaArchivo;
public:
	Generador(string Datos, bool coloresDiferentes, char** mapa, int resol_x, int resol_y);
	bool generarMapa();
	list<string> analizarArchivo();
};