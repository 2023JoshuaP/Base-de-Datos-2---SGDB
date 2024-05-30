#include <iostream>
#include "./Disco.cpp"
//#include "./BufferManager.cpp"
using namespace std;

void convertirCSVaTxt() {
    string fileCSV;
    string ruta = "/home/josue/Base de Datos II - SGBD/Base-de-Datos-2---SGDB/";
    cout << "Debe tener el archivo que desea leer, denos el nombre ('0' para no leer CSV): " << endl;
    cin >> fileCSV;
    string rutaCSV = ruta + fileCSV;

    if (fileCSV != "0"){
        ifstream csv(rutaCSV);
        if (csv.is_open()) {
            string fileTxt;
            cout << "Nombre del archivo txt: " << endl;
            cin >> fileTxt;

            ofstream fileSalida(fileTxt, ios::app);
            string linea;
            //bool primerCampo = true;
            
            while (getline(csv, linea)) {
                istringstream ss(linea);
                string campo;
                bool primerElemento = true;
                
                while (getline(ss, campo, ',')) {
                    if (campo.empty()) {
                        campo = "NULL";
                    }
                    if (campo.front() == '"' && campo.back() != '"') {
                        string campoCompleto = campo;
                        while (getline(ss, campo, ',') && campo.back() != '"') {
                            campoCompleto += "," + campo;
                        }
                        campoCompleto += "," + campo;
                        campo = campoCompleto;
                    }
                    if (!primerElemento) {
                        fileSalida << "#";
                    }
                    fileSalida << campo;
                    primerElemento = false;
                }
                fileSalida << endl;
            }
            fileSalida.close();
            cout << "Archivo creado." << endl;
        }
        else {
            cout << "Error al abrir el archivo CSV." << endl;
        }
    }
    else {
        cout << "No se seleccionó un archivo CSV." << endl;
    }
}

int main() {
    bool discoCreado = false;
    Disco discoSimulado;
    int opcion;
    while (true) {
        cout << "---------- MENU DE DISCO ----------" << endl;
        cout << "1. Convertir un CSV a archivo TXT." << endl;
        cout << "2. Crear Disco por defecto - (2 platos, 2 superficies, 2 pistas, 4 sectores, 512 bytes por Sector, 1024 bytes por Bloque)" << endl;
        cout << "3. Crear Disco manualmente." << endl;
        cout << "4. Ver capacidad del Disco." << endl;
        cout << "5. Eliminar Disco." << endl;
        cout << "6. Terminar Simulacion del disco" << endl;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

        switch (opcion) {
            case 1: {
                convertirCSVaTxt();
                break;
            }

            case 2: {
                if (!discoCreado) {
                    int platos = 2;
                    int pistas = 2;
                    int sectores = 4;
                    int bytesPorSector = 512;
                    int capacidadBloque = 1024;

                    discoSimulado.setNumPlatos(platos);
                    discoSimulado.setPistasPorSuperficie(pistas);
                    discoSimulado.setSectorPorPista(sectores);
                    discoSimulado.setBytesPorSector(bytesPorSector);

                    discoSimulado.crear();
                    discoCreado = true;
                    cout << "Disco creado correctamente." << endl << endl;
                    
                    cout << "------------------ Creando Bloques del Disco ------------------" << endl;
                    discoSimulado.crearBloques(capacidadBloque, bytesPorSector, sectores);
                } else {
                    cout << "Ya hay un Disco creado anteriormente, elimínelo para crear uno nuevo." << endl;
                }
                break;
            }

            case 3: {
                if (!discoCreado) {
                    int platos;
                    int pistas;
                    int sectores;
                    int bytesPorSector;
                    int capacidadBloque;
                    
                    cout << "Danos los datos necesarios para crear el Disco: " << endl << endl;
                    cout << "Cantidad de Platos: ";
                    cin >> platos;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
                    cout << "Cantidad de Pistas por Superficie: ";
                    cin >> pistas;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
                    cout << "Cantidad de Sectores por Pista: ";
                    cin >> sectores;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
                    cout << "Cantidad de Bytes que habrá por Sector: ";
                    cin >> bytesPorSector;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
                    
                    discoSimulado.setNumPlatos(platos);
                    discoSimulado.setPistasPorSuperficie(pistas);
                    discoSimulado.setSectorPorPista(sectores);
                    discoSimulado.setBytesPorSector(bytesPorSector);
                    
                    cout << "Datos recibidos, se procede a crear el Disco." << endl << endl;

                    discoSimulado.crear();

                    cout << "Disco creado correctamente." << endl << endl;

                    cout << "------------------ Creando Bloques del Disco ------------------" << endl << endl;
                    cout << "Capacidad del bloque: ";
                    cin >> capacidadBloque;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

                    if (capacidadBloque <= 0 || capacidadBloque > bytesPorSector) {
                        cout << "No se puede crear los bloques." << endl;
                    } else {
                        discoSimulado.crearBloques(capacidadBloque, bytesPorSector, sectores);
                    }
                } else {
                    cout << "Ya hay un Disco creado anteriormente, elimínelo para crear uno nuevo." << endl;
                }
                break;
            }

            case 4: {
                if (discoCreado) {
                    discoSimulado.capacidad();
                }
                else {
                    cout << "No hay un disco creado." << endl;
                }
                break;
            }

            case 5: {
                cout << "------------------ Eliminacion del Disco ------------------" << endl << endl;
                discoSimulado.eliminarDisco();
                discoCreado = false;
                break;
            }

            case 6: {
                cout << "Simulación del disco terminada." << endl;
                return 0;
            }

            default: {
                cout << "Opción no válida, intente de nuevo." << endl;
                break;
            }
        }
    }
}
