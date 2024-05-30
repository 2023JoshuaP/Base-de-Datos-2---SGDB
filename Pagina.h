#ifndef PAGINA_H
#define PAGINA_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class Pagina {
    public:
        vector<string> vectorRegistrosEnPagina;
    public:
        Pagina();
        ~Pagina();
        void recogerRegistros(int numPagina);
        void mostrarContenidoPagina();
        bool verificarPaginaVacia();
        void leerOescribirPAgina();
        void agregarContenido(int numPaginaEliminada);
};

#endif