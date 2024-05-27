#include "Disco.h"
#include <filesystem>
namespace fs = std::filesystem;

int calcularTamRegistro(const string& linea) {
    int tamanio = 0;
    stringstream ss(linea);
    string campo;
    while (getline(ss, campo, '#')) {
        if (campo != "NULL") {
            if (isdigit(campo[0])) {
                size_t posPunto = campo.find('.');
                if (posPunto != string::npos) {
                    tamanio += 4;
                }
                else {
                    tamanio += 4;
                }
            }
            else {
                tamanio += campo.length();
            }
        }
    }
    return tamanio;
}

void Disco::setNumPlatos(int platos) {
    this->numPlatos = platos;
    return;
}

void Disco::setPistasPorSuperficie(int superficie) {
    this->pistasPorSuperficie = superficie;
    return;
}

void Disco::setSectorPorPista(int sector) {
    this->sectorPorPista = sector;
    return;
}

void Disco::setBytesPorSector(int bytes) {
    this->bytesPorSector = bytes;
    return;
}

void Disco::crearCarpeta(const string& rutaCarpeta) {
    fs::create_directories(rutaCarpeta);
}

void Disco::crearArchivo(const string& rutaArchivo) {
    ofstream file(rutaArchivo);
}

void Disco::crear() {
    cout << "--------------- Creacion del Disco ---------------" << endl;
    string carpeta = "Disco";
    crearCarpeta(carpeta);

    for (int platos = 1; platos <= numPlatos; numPlatos++) {
        string carpetaPlato = carpeta + "/Plato " + to_string(platos);
        crearCarpeta(carpetaPlato);
        for (int superficies = 1; superficies <= 2; superficies++) {
            string carpetaSuperficie = carpetaPlato + "/Superficie " + to_string(superficies);
            crearCarpeta(carpetaSuperficie);
            for (int pistas = 1; pistas <= pistasPorSuperficie; pistas++) {
                string carpetaPista = carpetaSuperficie + "/Pista " + to_string(pistas);
                crearCarpeta(carpetaPista);
                for (int sectores = 1; sectores <= sectorPorPista; sectores++) {
                    string archivoSector = carpetaPista + "/" + to_string(sectores) + ".txt";
                    crearArchivo(archivoSector);
                }
            }
        }
    }
}

void Disco::capacidad() {
    cout << "--------------- Capacidad del Disco Creado ---------------" << endl;
    cout << endl;
    cout << "Capacidad: " << this->bytesPorSector * this->sectorPorPista * this->pistasPorSuperficie * 2 * this->numPlatos
    << " bytes en total."<< endl; 
}

void Disco::eliminarDisco() {
    string carpeta = "Disco";
    if (fs::exists(carpeta)) {
        fs::remove_all(carpeta);
        cout << "Disco eliminado correctamente." << endl;
    }
    else {
        cout << "No existe un Disco creado, debe crear el disco primero." << endl;
    }
}

void Disco::insertarRegistrosEnSector(ofstream& archivoSector, ifstream& archivoTexto, int registrosPorSector) {
    for (int i = 0; i < registrosPorSector; i++) {
        string linea;
        if (getline(archivoTexto, linea)) {
            archivoSector << linea << endl;
        }
    }
    cout << endl;
}

void Disco::llenarRegistrosEnSector(const string& archivo) {
    string path = "/home/josue/Base de Datos II - SGBD/Base-de-Datos-2---SGDB/" + archivo;
    ifstream archivoTxt(path);

    string linea;
    while (getline(archivoTxt, linea)) {
        int tamRegistro = calcularTamRegistro(linea);
        int bytes = this->bytesPorSector;
        int registrosSector = bytes / tamRegistro;

        for (int platos = 1; platos <= this->numPlatos; numPlatos++) {
            for (int superficies = 1; superficies <= 2; superficies++) {
                for (int pistas = 1; pistas <= this->pistasPorSuperficie; pistas++) {
                    for (int sectores = 1; sectores <= this->sectorPorPista; sectores++) {
                        string archivoSector = "Disco/Plato " + to_string(platos) + "/Superficie " + to_string(superficies) +
                                            "/Pista " + to_string(pistas) + "/" + to_string(sectores) + ".txt";
                        ofstream archivoSectorEscritura(archivoSector, ios::app);
                        insertarRegistrosEnSector(archivoSectorEscritura, archivoTxt, registrosSector);
                        archivoSectorEscritura.close();
                    }
                }
            }
        }
    }
    archivoTxt.close();
}

void Disco::crearBloques(int tamanoBloque, int tamanoSector, int cantidadDeSectores) {
    if (tamanoSector <= tamanoBloque) {
        cout << "El tamanio del sector no debe ser mayor al del bloque" << endl;
        return;
    }
    int sectoresPorBloque = tamanoBloque / tamanoSector;
    cout << "Cantidad de Sectores por Bloque: " << sectoresPorBloque << endl;
    int cantidadBloques = (cantidadDeSectores + sectoresPorBloque - 1) / sectoresPorBloque;
    cout << "Cantidad de Bloques a crear: " << cantidadBloques;
    for (int platos = 1; platos <= numPlatos; platos++) {
        for (int superficies = 1; superficies <= 2; superficies++) {
            for (int pistas = 1; pistas <= pistasPorSuperficie; pistas++) {
                string carpetaPista = "Disco/Plato " + to_string(platos) + "/Superficie " +
                                    to_string(superficies) + "/Pista " + to_string(pistas);

                for (int bloque = 1; bloque <= cantidadBloques; bloque++) {
                    string nombreBloque = carpetaPista + "/Bloque " + to_string(bloque) + ".txt";
                    ofstream archivoBloque(nombreBloque, ios::app);
                    if (archivoBloque.is_open()) {
                        int primerSector = (bloque - 1) * sectoresPorBloque + 1;
                        int ultimoSector = min(bloque * sectoresPorBloque, cantidadDeSectores);
                        for (int sector = primerSector; sector <= ultimoSector; sector++) {
                            string archivoSector = carpetaPista + "/" + to_string(sector) + ".txt";
                            archivoBloque << archivoSector << endl;
                        }
                        archivoBloque.close();
                        cout << "Bloque creado: " << nombreBloque << endl;
                    } else {
                        cout << "Error al crear el archivo del bloque: " << nombreBloque << endl;
                    }
                }
            }
        }
    }
}

bool Disco::validarDireccion(int plato, int superficie, int pista, int bloque) {
    string pathBloque = "Disco/Plato " + to_string(plato) + "/Superficie " + to_string(superficie) +
                        "/Pista " + to_string(pista) + "/Bloque " + to_string(bloque) + ".txt";
    return fs::exists(pathBloque);
}

void Disco::mostrarContenidoBloque(const string& direccionBloque) {
    ifstream archivo(direccionBloque);
    cout << "Contenido del Bloque " << direccionBloque << ": " << endl;
    string linea;
    while (getline(archivo,linea)) {
        cout << linea << endl;
    }
    archivo.close();
}