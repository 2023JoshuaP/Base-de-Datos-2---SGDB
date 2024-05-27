#ifndef DISCO_H
#define DISCO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int calcularTamRegistro(const string& linea);

class Disco {
    public:
        int numPlatos;
        int pistasPorSuperficie;
        int sectorPorPista;
        int bytesPorSector;
    private:
        Disco(int platos, int pistas, int sectores, int bytes) : 
            numPlatos(platos), pistasPorSuperficie(pistas), sectorPorPista(sectores), bytesPorSector(bytes) {}

        /* Funciones para obtener los Platos, Pistas, Sectores y Bytes de cada Sector */
        void setNumPlatos(int platos);
        void setPistasPorSuperficie(int pistas);
        void setSectorPorPista(int sector);
        void setBytesPorSector(int bytes);

        /*Funciones para la Estructura del Disco */
        void crearCarpeta(const string& rutaCarpeta);
        void crearArchivo(const string& rutaArchivo);

        /* Funcion para crear el Disco */
        void crear();
        
        /* Funcion para calcular la capacidad del disco en su totalidad */

        void capacidad();

        /* Funcion para eliminar el Disco */
        void eliminarDisco();

        /* Funciones para Registros en los sectores */
        void insertarRegistrosEnSector(ofstream& archivoSector, ifstream& archivoTexto, int registrosSector);
        void llenarRegistrosEnSector(const string& archivo);

        /* Funciones para los Bloques del Disco */
        void crearBloques(int tamanoBloque, int tamanoSector, int cantidadDeSectores);
        bool validarDireccion(int plato, int superficie, int pista, int bloque);
        void mostrarContenidoBloque(const string& direccionBloque);
};

#endif