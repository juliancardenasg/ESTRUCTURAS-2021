#include "funciones.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <string.h>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;



struct frecuencia
{
    char letra;
    int frecuencia;
};

struct histograma {

    frecuencia codigos[18];

};

vector<string> cargar(string archivo)
{
    stringstream auxiliar;
    string linea;
    ifstream entrada;
    vector<string> destino;
    int cont = 0;

    entrada.open(archivo);

    while (!entrada.eof())
    {
        getline(entrada, linea);

        if (linea.find(">") != std::string::npos && cont != 0)
        {
            destino.push_back(auxiliar.str());
            auxiliar.str(std::string());
        }
        auxiliar << linea + "\n";
        cont++;
    }

    destino.push_back(auxiliar.str());
    entrada.close();
    return destino;
}

vector<string> enmascarar(vector<string> secuencias, string mascara, int *total)
{

    char *aux = new char[mascara.length()];
    int cont = 0;

    for (int j = 0; j < mascara.length(); j++)
    {
        aux[j] = 'X';
    }

    for (int i = 0; i < secuencias.size(); i++)
    {
        if (secuencias[i].find(mascara) <= secuencias[i].length())
        {
            cont++;
        }

        while (secuencias[i].find(mascara) <= secuencias[i].length())
        {
            secuencias[i].replace(secuencias[i].find(mascara), mascara.length(), aux);
        }
    }
    *total = cont;
    return secuencias;
}

vector<string> es_subsecuencia(vector<string> secuencias, string secuencia, int *numSec)
{

    int cont = 0;

    for (int i = 0; i < secuencias.size(); i++)
    {
        if (secuencias[i].find(secuencia) <= secuencias[i].length())
        {
            cont++;
        }
    }

    *numSec = cont;
    return secuencias;
}

void listar_secuencia(vector<string> secuencias)
{
    int cont = 0;
    char *aux;
    bool completa;

    for (int i = 0; i < secuencias.size(); i++)
    {
        completa = true;
        cont = 0;

        if (secuencias[i].find("-") <= secuencias[i].length())
        {
            completa = false;
        }

        if (secuencias[i].find("A") <= secuencias[i].length())
        {
            cont++;
        }
        if (secuencias[i].find("C") <= secuencias[i].length())
        {
            cont++;
        }
        if (secuencias[i].find("G") <= secuencias[i].length())
        {
            cont++;
        }
        if (secuencias[i].find("T") <= secuencias[i].length())
        {
            cont++;
        }
        if (secuencias[i].find("U") <= secuencias[i].length())
        {
            cont++;
        }

        if (completa)
        {
            cout << "Secuencia " << secuencias[i].substr(0, secuencias[i].find("\n")) << " contiene " << cont << " bases" << endl;
        }

        else
        {

            cout << "Secuencia " << secuencias[i].substr(0, secuencias[i].find("\n")) << " contiene al menos " << cont << " bases" << endl;
        }
    }
}

void historgrama(vector<string> secuencias, string secuencia)
{

    char codigos[18] = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
    int cont = 0;
    bool existe = false;

    for (int i = 0; i < secuencias.size(); i++)
    {
        if (secuencias[i].find(secuencia) <= secuencias[i].length())
        {
            existe = true;

            for (int k = 0; k < 18; k++)
            {
                cont = 0;

                for (int j = 0; j < secuencias[i].length(); j++)
                {

                    if (secuencias[i].at(j) == codigos[k])
                    {

                        cont++;
                    }
                }

                cout << codigos[k] << " : " << cont << endl;
            }
        }
    }

    if (existe == false)
    {
        cout << "Secuencia invalida " << endl;
    }
}

int guardar(vector<string> secuencias, string destino)
{

    ofstream salida;
    salida.open(destino);

    if (salida.is_open())
    {

        for (int i = 0; i < secuencias.size(); i++)
        {

            salida << secuencias[i];
        }

        salida.close();
        return 0;
    }

    return -1;
}

void imprimirAyuda()
{

    cout << "\nMENU DE AYUDA:" << endl;
    cout << "**cargar (-nombre del archivo)" << endl;
    cout << "  Para cargar un archivo ya existente ingrese\n  el comando como se indica en pantalla seguido\n  del nombre del archivo.\n"
         << endl;
    cout << "**conteo" << endl;
    cout << "  El comando conteo no posee argumentos, se usa\n  con el fin de contar las secuencias cargadas\n  en el sistema.\n"
         << endl;
    cout << "**listar_secuencias" << endl;
    cout << "  El comando listar_secuencias no posee argumentos\n  se usa con el fin de listar las bases que posee\n  cada secuencia y se escribe como se indica en\n  pantalla.\n"
         << endl;
    cout << "**Histograma (-descripcion de la secuencia)" << endl;
    cout << "  El comando Histograma recibe como parametro la\n  descripcion de una secuencia (se recomienda utilizar\n  listar_secuencias previamente), mostrara un conteo\n  de cada codigo presente en la secuencia seleccionada.\n"
         << endl;
    cout << "**es_subsecuencia (-subsecuencia a buscar)" << endl;
    cout << "  Este comando recibe como unico parametro una\n  subsecuencia a buscar dentro de todas las secuencias\n  cargadas, posterior a esto se indica en cuantas secuencias\n  existe la subsecuencia dada.\n"
         << endl;
    cout << "**enmascarar (-subsecuencia a enmascarar)" << endl;
    cout << "  Este comando recibe como unico parametro una\n  subsecuencia o serie de codigos a enmascarar en todas\n  las secuencias cargadas en memoria, posteriomente indicara\n  cuantas secuencias fueron enmascaradas.\n"
         << endl;
    cout << "**guardar (-nombre del archivo)" << endl;
    cout << "  El comando guardar recibe como unico parametro el\n  nombre del archivo en el que se guardaran las secuencias\n  existentes en memoria, usualmente despues de modificaciones.\n"
         << endl;
    cout << "**salir" << endl;
    cout << "  Este comando lo sacara del sistema inmediatamente." << endl;
}

vector<histograma> contarFrecuencias(vector<string> secuencias)
{

    char codigos[18] = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
    int cont = 0;    
    vector<histograma> histogramas;
    histograma haux;

    for (int i = 0; i < secuencias.size(); i++)
    {

        for (int k = 0; k < 18; k++)
        {
            cont = 0;

            for (int j = 0; j < secuencias[i].length(); j++)
            {

                if (secuencias[i].at(j) == codigos[k])
                {
                    
                    cont++;
                }
            }
            
            haux.codigos[k].frecuencia = cont;
            haux.codigos[k].letra = codigos[k];                        
        }

        histogramas.push_back(haux);
    }
   

    return histogramas;
}
