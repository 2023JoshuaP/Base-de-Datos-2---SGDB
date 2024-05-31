#include <iostream>
#include <vector>
#include "./Disco.cpp"
#include "BufferManager/BufferManager.cpp"
using namespace std;

void convertirCSVaTxt() {
    string fileCSV;
    string ruta = "/home/josue/Base de Datos II - SGBD/Base-de-Datos-2---SGDB/";
    cout << "Debe tener el archivo que desea leer, denos el nombre ('0' para no leer CSV): " << endl;
    cin >> fileCSV;
    string rutaCSV = ruta + fileCSV;

    if (fileCSV != "0") {
        ifstream csv(rutaCSV);
        if (csv.is_open()) {
            string fileTxt;
            string fileEsquema;
            cout << "Nombre del archivo txt: " << endl;
            cin >> fileTxt;
            cout << "Nombre del archivo de esquema: " << endl;
            cin >> fileEsquema;

            ofstream fileSalida(fileTxt, ios::app);
            ofstream fileEsquemaSalida(fileEsquema, ios::app);
            string linea;
            vector<string> nombresColumnas;

            // Leer la primera línea para obtener los nombres de las columnas
            if (getline(csv, linea)) {
                istringstream ss(linea);
                string campo;

                while (getline(ss, campo, ',')) {
                    nombresColumnas.push_back(campo);
                }

                // Solicitar el nombre del esquema
                string nombreEsquema;
                cout << "Ingrese el nombre del esquema: ";
                cin >> nombreEsquema;
                fileEsquemaSalida << nombreEsquema << endl;

                // Solicitar tipo de dato para cada columna
                for (const string& nombreColumna : nombresColumnas) {
                    string tipoDato;
                    string tamaño = "4";  // Tamaño por defecto para int y float
                    bool tipoValido = false;
                    
                    while (!tipoValido) {
                        cout << "Ingrese el tipo de dato para la columna " << nombreColumna << " (int, float, str): ";
                        cin >> tipoDato;

                        if (tipoDato == "int" || tipoDato == "float" || tipoDato == "str") {
                            tipoValido = true;
                            if (tipoDato == "str") {
                                cout << "Ingrese el tamaño para la columna " << nombreColumna << ": ";
                                cin >> tamaño;
                            }
                        } else {
                            cout << "Tipo de dato inválido. Por favor ingrese 'int', 'float' o 'str'." << endl;
                        }
                    }

                    fileEsquemaSalida << nombreColumna << "#" << tipoDato << "#" << tamaño << endl;
                }
            }

            // Leer las líneas restantes para convertir el CSV a TXT
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
                        fileSalida << ",";
                    }
                    fileSalida << campo;
                    primerElemento = false;
                }
                fileSalida << endl;
            }

            fileSalida.close();
            fileEsquemaSalida.close();
            cout << "Archivo y esquema creados." << endl;
        } else {
            cout << "Error al abrir el archivo CSV." << endl;
        }
    } else {
        cout << "No se seleccionó un archivo CSV." << endl;
    }
}

bool validarNombreEsquema(const string& rutaEsquema) {
    string nombreEsquema;
    cout << "Ingrese el nombre del esquema (tabla): ";
    cin >> nombreEsquema;

    ifstream archivoEsquema(rutaEsquema);
    if (archivoEsquema.is_open()) {
        string nombreEsquemaArchivo;
        getline(archivoEsquema, nombreEsquemaArchivo);
        archivoEsquema.close();
        return nombreEsquema == nombreEsquemaArchivo;
    } else {
        cout << "Error al abrir el archivo de esquema." << endl;
        return false;
    }
}

bool existeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.good(); // Devuelve true si el archivo existe y se puede abrir
}

int main() {
    bool discoCreado = false;
    Disco discoSimulado;
    int opcionPrincipal;
    do {
        cout << "-------------- Principal --------------" << endl;
        cout << "1. Simulacion de Disco." << endl;
        cout << "2. Buffer Manager." << endl;
        cout << "3. Finalizar Programa." << endl;
        cout << "Opcion a escoger: ";
        cin >> opcionPrincipal;
        switch (opcionPrincipal) {
            case 1: {
                int opcion;
                do {
                    cout << "---------- MENU DE DISCO ----------" << endl;
                    cout << "1. Convertir un CSV a archivo TXT." << endl;
                    cout << "2. Crear Disco por defecto - (2 platos, 2 superficies, 2 pistas, 4 sectores, 512 bytes por Sector, 1024 bytes por Bloque)" << endl;
                    cout << "3. Crear Disco manualmente." << endl;
                    cout << "4. Ver capacidad del Disco." << endl;
                    cout << "5. Llenar los sectores." << endl;
                    cout << "6. Eliminar Disco." << endl;
                    cout << "7. Terminar Simulacion del disco" << endl;
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
                                //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
                                cout << "Cantidad de Pistas por Superficie: ";
                                cin >> pistas;
                                //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
                                cout << "Cantidad de Sectores por Pista: ";
                                cin >> sectores;
                                //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
                                cout << "Cantidad de Bytes que habrá por Sector: ";
                                cin >> bytesPorSector;
                                //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
                                
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
                            string rutaEsquema = "/home/josue/Base de Datos II - SGBD/Base-de-Datos-2---SGDB/output/esquema.txt";
                            if (validarNombreEsquema(rutaEsquema)) {
                                string archivo;
                                cout << "Archivo que sera usado: ";
                                cin >> archivo;
                                discoSimulado.llenarRegistrosEnSector(archivo);
                            }
                            break;
                        }

                        case 6: {
                            cout << "------------------ Eliminacion del Disco ------------------" << endl << endl;
                            discoSimulado.eliminarDisco();
                            discoCreado = false;
                            break;
                        }

                        case 7: {
                            cout << "Simulación del disco terminada." << endl;
                            break;
                        }

                        default: {
                            cout << "Opción no válida, intente de nuevo." << endl;
                            break;
                        }
                    }
                    cout << endl;
                }while (opcion != 7);
                break;
            }

            case 2: {
                BufferManager bufferManager;
                int numPagina;
                int numFrame;
                int opcion;
                do {
                    cout << "------------- Menu BufferManager -------------" << endl;
                    cout << "1. Crear Buffer Pool." << endl;
                    cout << "2. Obtener Pagina." << endl;
                    cout << "3. Mostrar la Page Table." << endl;
                    cout << "4. Liberar Pagina." << endl;
                    cout << "5. Mostrar Pagina." << endl;
                    cout << "6. Salir del Buffer." << endl;
                    cout << "Opcion a elegir: ";
                    cin >> opcion;
                    switch (opcion) {
                        case 1: {
                            int pesoBytesBloque;
                            int numFrames;
                            cout << "Peso del Bloque del Disco: ";
                            cin >> pesoBytesBloque;
                            cout << "Cantidad de Frames: ";
                            cin >> numFrames;

                            bufferManager.crearBufferPoolSegunNumFrames(numFrames);
                            bufferManager.establecerLimiteDeFrames(pesoBytesBloque);
                            break;
                        }

                        case 2: {
                            cout << "Ingrese el numero de Pagina que se va a obtener: ";
                            cin >> numPagina;
                            bufferManager.obtenerUnaPagina(numPagina);
                            break;
                        }

                        case 3: {
                            bufferManager.mostrarPageTAble();
                            break;
                        }

                        case 4: {
                            cout << "Indicar que Pagina se va a liberar (Pin Count descontara): ";
                            cin >> numPagina;
                            bufferManager.pageTable.descontarPinCountApagina(numPagina);
                            break;
                        }

                        case 5: {
                            cout << "Ingrese el numero de la pagina a mostrale"<<endl;
                            cin >> numPagina;
                            numFrame=bufferManager.pageTable.getNumFrameDeUnaPagina(numPagina);
                        
                            char accionEnPagina;
                            cout << "Leer (L/l) o Escribir (W/w) en pagina?: ";
                            cin >> accionEnPagina;
                            if (accionEnPagina == 'L' || accionEnPagina == 'l') {
                                bufferManager.bufferPool.mostrarFramePagina(numFrame);//leer
                                bufferManager.pageTable.aumentarPinCountDePagina(numPagina);
                                break;
                            }
                            else if (accionEnPagina == 'W' || accionEnPagina == 'w') {
                                bufferManager.bufferPool.lecturaOescrituraPagina(numFrame); //escribir
                                bufferManager.pageTable.aumentarPinCountDePagina(numPagina);
                                bufferManager.pageTable.cambiarDirtyBitDePagina(numPagina);
                                break;
                            }
                            break;
                        }
                    }
                } while (opcion != 6);
                break;
            }
            
            case 3: {
                cout << "Saliendo del Buffer Manager." << endl;
                break;
            }
        }
    } while (opcionPrincipal != 3);
    return 0;
}
