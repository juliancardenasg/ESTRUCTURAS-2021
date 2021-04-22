#include <iostream>
#include <cstring>
#include <vector>
#include <string.h>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
#include "funciones.h"

using namespace std;

// comando 1 - se cargan las secuencias en el vector de strings "destino"

int main()
{
  string comando;
  string intermedio;
  vector<string> split;
  vector<string> secuencias;
  stringstream chek1;
  int sec_enmascaradas;
  int sec_subsecuencias;
  cout << "--------MANIPULACION DE ARCHIVOS FASTA--------\n";
  while (1)
    {
        split.clear();
        chek1.clear();
        cout << "$ ";
        getline(cin, comando);
        chek1 << comando;

        while (getline(chek1, intermedio, ' '))
        {
            split.push_back(intermedio);
        }

        //COMANDO 1

        if (split[0].compare("cargar") == 0)
        {

            secuencias = cargar((split[1]));

            if (secuencias.size() == 1 && secuencias[0].find(">") == std::string::npos)
            {

                cout << split[1] << " No contiene ninguna secuencia " << endl;
                secuencias.clear();
            }
            else
            {

                cout << secuencias.size() << " Secuencias cargadas desde el archivo " << split[1] << endl;
            }
        }

        //COMANDO 2

        if (split[0].compare("conteo") == 0)
        {
            cout << secuencias.size() << " secuencia(s) cargadas en memoria" << endl;
        }

        //COMANDO 3

        if (split[0].compare("listar_secuencias") == 0)
        {
            if (secuencias.empty())
            {
                cout << "No hay secuencias cargadas en memoria." << endl;
            }
            else
            {

                listar_secuencia(secuencias);
            }
        }

        //COMANDO 4

        if (split[0].compare("histograma") == 0)
        {

            historgrama(secuencias, split[1]);
        }

        //COMANDO 5

        if (split[0].compare("es_subsecuencia") == 0)
        {
            sec_subsecuencias = 0;

            if (secuencias.empty())
            {

                cout << "No hay secuencias cargadas en memoria." << endl;
            }
            else
            {
                secuencias = es_subsecuencia(secuencias, split[1], &sec_subsecuencias);

                if (sec_subsecuencias == 0)
                {
                    cout << "La secuencia no existe." << endl;
                }
                else
                {
                    cout << "se encontraron " << sec_subsecuencias << " Secuencias." << endl;
                }
            }
        }

        //COMANDO 6

        if (split[0].compare("enmascarar") == 0)
        {
            sec_enmascaradas = 0;

            if (secuencias.empty())
            {

                cout << "No hay secuencias cargadas en memoria." << endl;
            }
            else
            {
                secuencias = enmascarar(secuencias, split[1], &sec_enmascaradas);

                if (sec_enmascaradas == 0)
                {
                    cout << "La secuencia no existe." << endl;
                }
                else
                {
                    cout << "se enmascararon " << sec_enmascaradas << " Secuencias." << endl;
                }
            }
        }

        //COMANDO 7

        if (split[0].compare("guardar") == 0)
        {
            int validacion = guardar(secuencias, split[1]);
            if (secuencias.empty())
            {

                cout << "No hay secuencias cargadas en memoria." << endl;
            }
            else
            {
                if (validacion != 0)
                {
                    cout << "Error guardando en " << split[1] << endl;
                }
                else
                {
                    cout << "Las secuencias han sido guardadas en " << split[1] << endl;
                }
            }
        }

        //COMANDO 8
        if (split[0].compare("salir") == 0)
        {
            cout << endl;
            exit(0);
        }

        //COMANDO AYUDA
        if (split[0].compare("ayuda") == 0)
        {
            imprimirAyuda();   

        }

        cout << endl;
    }

    return 0;
};