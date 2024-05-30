#include <iostream>
#include "./BufferManager.cpp"
using namespace std;

void menuBufferManager(BufferManager bufferManagerPrincipal) {
    int pesoBytesBloque;
    int numFrames;
    cout << "---------------- Bienvenido a implementacion del BUFFER ----------------" << endl;
    cout << "Ingresar el peso de los bloques en el Disco: " << endl;
    cin >> pesoBytesBloque;
    cout << "Ingresar la cantidad de Frames a tener el Buffer Pool: " << endl;
    cin >> numFrames;

    cout << "----------------------- Creando el Buffer Manager -----------------------" << endl;
    bufferManagerPrincipal.crearBufferPoolSegunFrames(numFrames);
    bufferManagerPrincipal.establecerLimitedeFrames(pesoBytesBloque);
    cout << "---------------------- Buffer Manager se ha creado ----------------------" << endl;
}

void menuPrincipal() {
    BufferManager bufferManagerPrincipal;
    int opcion = 0;
    int numPagina;
    int numFrame;
    while (opcion != 6) {
        cout << "----------------------- Menu Principal de Buffer Manager -----------------------" << endl;
        cout << "1. Crear el Buffer Pool." << endl;
        cout << "2. Obtener una Pagina." << endl;
        cout << "3. Mostrar la Page Table." << endl;
        cout << "4. Mostrar una Pagina." << endl;
        cout << "5. Liberar uso de la Pagina." << endl;
        cout << "6. Finalizar Buffer Manager." << endl;
        cout << "Elige una de las opciones:";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                menuBufferManager(bufferManagerPrincipal);
                break;
            }

            case 2: {
                cout << "Seleccione la pagina que desee obtener: ";
                cin >> numPagina;
                bufferManagerPrincipal.obtenerUnaPagina(numPagina);
                break;
            }

            case 3: {
                bufferManagerPrincipal.mostrarPageTable();
                break;
            }

            case 4: {
                cout << "Pagina que sera mostrada: ";
                cin >> numPagina;

                numFrame = bufferManagerPrincipal.pageTable.getNumFrameDeUnaPagina(numPagina);
                char accionEnPagina;
                cout << "Leer (L/l) o Escribir (W/w) en la Pagina?: ";
                cin >> accionEnPagina;

                if (accionEnPagina == 'L' || accionEnPagina == 'l') {
                    bufferManagerPrincipal.bufferPool.mostrarFramePagina(numFrame); //leer
                    bufferManagerPrincipal.pageTable.aumentarPinCountDePagina(numPagina);
                    break;
                }
                else if (accionEnPagina == 'W' || accionEnPagina == 'w') {
                    bufferManagerPrincipal.bufferPool.lecturaOescrituraPagina(numFrame); //escribir
                    bufferManagerPrincipal.pageTable.aumentarPinCountDePagina(numPagina);
                    bufferManagerPrincipal.pageTable.cambiarDirtyBitDePagina(numPagina);
                    break;
                }
                break;
            }

            case 5: {
                cout << "Numero de Pagina que sera liberada (descontara el Pin Count): ";
                cin >> numPagina;
                bufferManagerPrincipal.pageTable.descontarPinCountApagina(numPagina);
                break;
            }

            case 6: {
                cout << "Finalizando..." << endl;
                break;
            }

            default:
                break;
        }
    }
}