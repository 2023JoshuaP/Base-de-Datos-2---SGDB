#include <iostream>
#include "./Disco.cpp"
using namespace std;

int main() {
    bool discoCreado = false;
    Disco discoSimulado;
    int opcion;
    while (true) {
        cout << "---------- MENU DE DISCO ----------" << endl;
        cout << "1. Crear Disco por defecto - (2 platos, 2 superficies, 2 pistas, 4 sectores, 512 bytes por Sector, 1024 bytes por Bloque)" << endl;
        cout << "2. Crear Disco manualmente." << endl;
        cout << "3. Ver capacidad del Disco." << endl;
        cout << "4. Eliminar Disco." << endl;
        cout << "5. Terminar Simulacion del disco" << endl;
        cin >> opcion;
        switch (opcion) {
            case 1: {
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
                }
                else {
                    cout << "Ya hay un Disco creado anteriormente, eliminelo para crear uno nuevo." << endl;
                }
                break;
            }

            case 2: {
                if (!discoCreado) {
                    int platos;
                    int pistas;
                    int sectores;
                    int bytesPorSector;
                    int capacidadBloque;
                    
                    cout << "Danos los datos necesarios para crear el Disco: " << endl << endl;
                    cout << "Cantidad de Platos: ";
                    cin >> platos;
                    cout << "Cantidad de Pistas por Superficie: ";
                    cin >> pistas;
                    cout << "Cantidad de Sectores por Pista: ";
                    cin >> sectores;
                    cout << "Cantidad de Bytes que habrá por Sector: ";
                    cin >> bytesPorSector;
                    
                    discoSimulado.setNumPlatos(platos);
                    discoSimulado.setPistasPorSuperficie(pistas);
                    discoSimulado.setSectorPorPista(sectores);
                    discoSimulado.setBytesPorSector(bytesPorSector);
                    
                    cout << "Datos recibidos, se procede a crear el Disco." << endl << endl;

                    discoSimulado.crear();

                    cout << "Disco creado correctamente." << endl << endl;

                    cout << "------------------ Creando Bloques del Disco ------------------" << endl << endl;
                    cout << "Capacidad del bloque: " << endl;
                    cin >> capacidadBloque;

                    if (capacidadBloque <= 0 && capacidadBloque > bytesPorSector) {
                        cout << "No se puede crear los bloques." << endl;
                    }
                    else {
                        discoSimulado.crearBloques(capacidadBloque, bytesPorSector, sectores);
                    }
                }
                else {
                    cout << "Ya hay un disco creando anteriormente, eliminelo para poder crear un nuevo Disco" << endl;
                }
                break;
            }

            case 3: {
                if (discoCreado) {
                    cout << "------------------ Capacidad del Disco ------------------" << endl << endl;
                    discoSimulado.capacidad();
                }
                else {
                    cout << "No hay un Disco creado, debe crear uno primero." << endl;
                }
                break;
            }

            case 4: {
                cout << "------------------ Eliminacion del Disco ------------------" << endl << endl;
                discoSimulado.eliminarDisco();
                discoCreado = false;
                break;
            }

            case 5: {
                cout << "------------------ Finalizando la Simulación del Disco ------------------" << endl << endl;
                cout << "Saliendo del programa de Disco." << endl;
                return 0;
            }

            default: {
                cout << "La opcion que ingreso no esta disponible, intente de nuevo." << endl << endl;
                break;
            }
        }
    }
    return 0;
}