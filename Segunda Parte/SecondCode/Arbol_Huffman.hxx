#include "Arbol_Huffman.h"
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <string.h>
#include <bits/stdc++.h>

void Arbolhuffman::create_node_array()
{//crea la tabla ascii
    for (int i = 0; i < 128; i++)
    {
        tabla_As[i] = new nodo_huff;
        tabla_As[i]->identificador = i;
        tabla_As[i]->frecuencia = 0;
    }
}

int Arbolhuffman::binary_to_decimal(string &in)
{
    int result = 0;
    for (int i = 0; i < in.size(); i++)
        result = result * 2 + in[i] - '0';
    return result;
}

string Arbolhuffman::decimal_to_binary(int in)
{
    string temp = "";
    string result = "";
    while (in)
    {
        temp += ('0' + in % 2);
        in /= 2;
    }
    result.append(8 - temp.size(), '0'); // añadir '0' adelante para permitir que el resultado se convierta en una longitud fija de 8
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        result += temp[i];
    }
    return result;
}

inline void Arbolhuffman::build_tree(string &path, char a_codigo)
{ // construye una nueva rama de acuerdo con el código de entrada e ignora las ramas ya existentes
    node_ptr actu = raiz;
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == '0')
        {
            if (actu->izq == NULL)
                actu->izq = new nodo_huff;
            actu = actu->izq;
        }
        else if (path[i] == '1')
        {
            if (actu->der == NULL)
                actu->der = new nodo_huff;
            actu = actu->der;
        }
    }
    actu->identificador = a_codigo; // adjuntar id a la hoja
}

Arbolhuffman::Arbolhuffman(string in, string out)
{
    nombre_Fin = in;
    nombre_Fout = out;
    create_node_array();
}

void Arbolhuffman::create_pq()
{
    in_file.open(nombre_Fin, ios::in);
    in_file.get(id);
    while (!in_file.eof())
    {
        tabla_As[id]->frecuencia++;
        in_file.get(id);
    }
    in_file.close();
    for (int i = 0; i < 128; i++)
    {
        if (tabla_As[i]->frecuencia)
        {
            pq.push(tabla_As[i]);
        }
    }
}

void Arbolhuffman::create_huffman_tree()
{
    priority_queue<node_ptr, vector<node_ptr>, comparacion> temp(pq);
    while (temp.size() > 1)
    { // crea el árbol Arbol Huffman con el carácter de mayor frecuencia siendo hoja de abajo hacia arriba
        raiz = new nodo_huff;
        raiz->frecuencia = 0;
        raiz->izq = temp.top();
        raiz->frecuencia += temp.top()->frecuencia;
        temp.pop();
        raiz->der = temp.top();
        raiz->frecuencia += temp.top()->frecuencia;
        temp.pop();
        temp.push(raiz);
    }
}

void Arbolhuffman::coding_save()
{
    in_file.open(nombre_Fin, ios::in);
    out_file.open(nombre_Fout, ios::out | ios::binary);
    string in = "", s = "";

    in += (char)pq.size(); // el primer byte guarda el tamaño de la cola de prioridad
    priority_queue<node_ptr, vector<node_ptr>, comparacion> temp(pq);
    while (!temp.empty())
    { // obtener todos los personajes y sus códigos Arbol Huffman para la salida
        node_ptr actu = temp.top();
        in += actu->identificador;
        s.assign(127 - actu->codigo.size(), '0'); // establece los códigos con un formato de cadena fijo de 128 bits [000¡¡1 + código real]
        s += '1';                                  // '1' indica el inicio del código de Arbol Huffman
        s.append(actu->codigo);
        in += (char)binary_to_decimal(s.substr(0,8));
        for (int i = 0; i < 15; i++)
        { // cortar en códigos binarios de 8 bits que se pueden convertir en caracteres de ahorro necesarios para el archivo binario
            s = s.substr(8);
            in += (char)binary_to_decimal(s.substr(0, 8));
        }
        temp.pop();
    }
    s.clear();

    in_file.get(id);
    while (!in_file.eof())
    { // obtener el código de Arbol Huffman
        s += tabla_As[id]->codigo;
        while (s.size() > 8)
        { // cortar en códigos binarios de 8 bits que se pueden convertir en caracteres de ahorro necesarios para el archivo binario
            in += (char)binary_to_decimal(s.substr(0, 8));
            s = s.substr(8);
        }
        in_file.get(id);
    }
    int count = 8 - s.size();
    if (s.size() < 8)
    { // agrega el número de 'count' '0' a los últimos códigos para crear el último byte de texto
        s.append(count, '0');
    }
    in += (char)binary_to_decimal(s); // guardar el número de 'recuento' por fin
    in += (char)count;

    out_file.write(in.c_str(), in.size());
    in_file.close();
    out_file.close();
}

void Arbolhuffman::recreate_huffman_tree()
{
    in_file.open(nombre_Fin, ios::in | ios::binary);
    unsigned char size; // carácter sin firmar para obtener el número de nodo del árbol humano
    in_file.read(reinterpret_cast<char *>(&size), 1);
    raiz = new nodo_huff;
    for (int i = 0; i < size; i++)
    {
        char a_codigo;
        unsigned char h_codigo_c[16]; // 16 caracteres sin firmar para obtener el código binario
        in_file.read(&a_codigo, 1);
        in_file.read(reinterpret_cast<char *>(h_codigo_c), 16);
        string h_codigo_s = "";
        for (int i = 0; i < 16; i++)
        { // obtener la cadena binaria original de 128 bits
            h_codigo_s += decimal_to_binary(h_codigo_c[i]);
        }
        int j = 0;
        while (h_codigo_s[j] == '0')
        { // eliminar el '000¡¡1' agregado para obtener el código real de Arbol Huffman
            j++;
        }
        h_codigo_s = h_codigo_s.substr(j + 1);
        build_tree(h_codigo_s, a_codigo);
    }
    in_file.close();
}

void Arbolhuffman::decoding_save()
{
    in_file.open(nombre_Fin, ios::in | ios::binary);
    out_file.open(nombre_Fout, ios::out);
    unsigned char size; // obtener el tamaño del árbol Arbol Huffman
    in_file.read(reinterpret_cast<char *>(&size), 1);
    in_file.seekg(-1, ios::end); // salta al último byte para obtener el número de '0' adjunto a la cadena al final
    char count0;
    in_file.read(&count0, 1);
    in_file.seekg(1 + 17 * size, ios::beg); // salta a la posición donde comienza el texto

    vector<unsigned char> text;
    unsigned char textseg;
    in_file.read(reinterpret_cast<char *>(&textseg), 1);
    while (!in_file.eof())
    { // obtener el texto byte por byte usando un carácter sin firmar
        text.push_back(textseg);
        in_file.read(reinterpret_cast<char *>(&textseg), 1);
    }
    node_ptr actu = raiz;
    string path;
    for (int i = 0; i < text.size() - 1; i++)
    { // traducir el código de Arbol Huffman
        path = decimal_to_binary(text[i]);
        if (i == text.size() - 2)
            path = path.substr(0, 8 - count0);
        for (int j = 0; j < path.size(); j++)
        {
            if (path[j] == '0')
                actu = actu->izq;
            else
                actu = actu->der;
            if (actu->izq == NULL && actu->der == NULL)
            {
                out_file.put(actu->identificador);
                actu = raiz;
            }
        }
    }
    in_file.close();
    out_file.close();
}