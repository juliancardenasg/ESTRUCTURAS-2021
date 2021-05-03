#ifndef  ARBOL_HUFFMAN__H__
#define  ARBOL_HUFFMAN__H__

#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

struct nodo_huff
{
	char identificador;																				
	int frecuencia;																				
	string codigo;																			
	nodo_huff* izq;
	nodo_huff* der;
	nodo_huff()
	{//constructor nullo para el primer nodo y para crearlo
		izq = der = NULL;
	}
};

typedef nodo_huff* node_ptr;

class comparacion
{//una función de objeto para establecer la regla de comparación de la cola de prioridad 
public:
bool operator()(const node_ptr& c1, const node_ptr& c2) const
	{
		return c1->frecuencia > c2->frecuencia;
	}
};

class Arbolhuffman
{
protected:
	fstream in_file, out_file;
	node_ptr tabla_As[128];		//matriz para 128 caracteres en la tabla Ascii 												
	node_ptr hijo, padre, raiz;
	char id;
	string nombre_Fin, nombre_Fout;
	
	priority_queue<node_ptr, vector<node_ptr>, comparacion> pq;			//cola de prioridad de frecuencia de mayor a menor
	void create_node_array();																
	int binary_to_decimal(string&);				//convertir una cadena 0/1 de 8 bits de código binario en un entero decimal
	string decimal_to_binary(int);				//convertir un entero decimal en una cadena 0/1 de 8 bits de código binario
	inline void build_tree(string&, char);		// construya el árbol huffman de acuerdo con la información del archivo 

public:
	Arbolhuffman(string, string);
	void create_pq();
	void create_huffman_tree();
	void coding_save();
	void decoding_save();
	void recreate_huffman_tree();
};

#include "Arbol_Huffman.hxx"
#endif