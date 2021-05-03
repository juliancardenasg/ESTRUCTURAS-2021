#ifndef  FUNCIONES__H__
#define  FUNCIONES__H__

#include <iostream>
#include <cstring>
#include <vector>
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;


vector<string> cargar(string archivo);
vector<string> enmascarar(vector<string> secuencias, string mascara, int *total);
vector<string> es_subsecuencia(vector<string> secuencias, string secuencia, int *numSec);
void listar_secuencia(vector<string> secuencias);
void historgrama(vector<string> secuencias, string secuencia);
int guardar(vector<string> secuencias, string destino);

#include "funciones.hxx"
#endif 