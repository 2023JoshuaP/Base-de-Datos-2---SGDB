#include <iostream>
#include "./BufferManager.cpp"

using namespace std;

void menuBufferManager(BufferManager &bufferManagerPrincipal) {
    cout << "Bienvenido a implementación de BUFFER" << endl;
    int pesoBytesBLoque;
    cout << "Ingrese el peso de su bloque de Disco: " << endl;
    cin >> pesoBytesBLoque;
    int numFrames;
    cout << "Ingrese la cantidad de Frames a tener en el Buffer Pool: " << endl;
    cin >> numFrames;

    bufferManagerPrincipal.crearBufferPoolSegunNumFrames(numFrames);
    bufferManagerPrincipal.establecerLimiteDeFrames(pesoBytesBLoque);
    cout << "----------- Creación de estructura Básica de BufferManager implementado" << endl;

}

void menu() {      
    BufferManager bufferManagerPrincipal;
    int opcion = 0;
    int numPagina;
    int numFrame;
    while (opcion!=6) {
        cout << "Menú Principal Programa Buffer MAnager:" << endl;
        cout << "1. Crear Buffer Pool" << endl;
        cout << "2. Obtener Una Página" << endl;
        cout << "3. Mostrar Page Table" << endl;
        cout << "4. Mostrar Una Página" << endl;
        cout << "5. Liberar uso de Página" << endl;
        cout << "6. SALIR del programa principal" << endl;
        cout << ">>>Ingrese el numero de opcion" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                menuBufferManager(bufferManagerPrincipal);
                break;
            case 2:       
                cout << "Ingrese el numero de pagina que desea OBTENER (Modo Prueba 1 - 6): "<< endl;
                cin >> numPagina;        
                bufferManagerPrincipal.obtenerUnaPagina(numPagina);
                break;
            case 3:
                bufferManagerPrincipal.mostrarPageTAble();
                break;
            case 4:
                cout << "Ingrese el numero de la pagina a mostrale"<<endl;
                cin >> numPagina;
                numFrame=bufferManagerPrincipal.pageTable.getNumFrameDeUnaPagina(numPagina);
            
                char accionEnPagina;
                cout << "Leer (L/l) o Escribir (W/w) en pagina?: ";
                cin >> accionEnPagina;
                if (accionEnPagina == 'L' || accionEnPagina == 'l') {
                    bufferManagerPrincipal.bufferPool.mostrarFramePagina(numFrame);//leer
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
                
            case 5:
                cout<<"Ingrese el numero de la pagina a liberar (descontar PinCount)"<<endl;
                cin>>numPagina;
                bufferManagerPrincipal.pageTable.descontarPinCountApagina(numPagina);
                break;
            default:
                break;
        }  
    }
}

int main() {
    menu();
    return 0;
}