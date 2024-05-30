#include "PageTable.h"

PageTable::PageTable() {}

PageTable::~PageTable() {}

void PageTable::mostrarPageTableLRU() {
    int numFila = this->matrizPageTableLRU.size();
    int numColumna = this->numColumnasEnPageTable;
    cout << "Frame Id \t Page Id \t Dirty Bit \t Pin Count \t Last Used" << endl;
    for (int i = 0; i < numFila; i++) {
        cout << i << "\t\t";
        for (int j = 0; j < numColumna; j++) {
            cout << this->matrizPageTableLRU[i][j] << "\t\t";
        }
        cout << endl;
    }
}

bool PageTable::verificarExistenciaDePagina(int numPagina) {
    int j = 0;
    for (int i = 0; i < this->columnaFrameIdSize; i++) {
        if (this->matrizPageTableLRU[i][j] == numPagina) {
            cout << "Pagina " + to_string(numPagina) + " si existe." << endl;
            return true;
        }
    }
    cout << "Pagina " + to_string(numPagina) + " no existe." << endl;
    return false;
}

int PageTable::getNumFrameDeUnaPagina(int numPagina) {
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                cout << "La Pagina ha sido hallada, devolviendo el frame: " << endl;
                return i;
            }
        }
    }
    else {
        cout << "No existe dicha Pagina para obtener el Frame." << endl;
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j]) {
                cout << this->matrizPageTableLRU[i][j] << " si tiene valor." << endl;
            }
            else {
                cout << "Espacio vacio, Page Id confirmado." << endl;
                return i;
            }
        }
    }
}

void PageTable::descontarPinCountApagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int  i = 0; i < columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                numFilaElegida = 1;
            }
        }
        int numColumnaPinCount = 2;
        this->matrizPageTableLRU[numFilaElegida][numColumnaPinCount] = this->matrizPageTableLRU[numFilaElegida][numColumnaPinCount] - 1;
        cout << "Pin Cont descontando para la Pagina " << numPagina << endl;
    }
}

void PageTable::aumentarPinCountDePagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int  i = 0; i < columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                numFilaElegida = 1;
            }
        }
        int numColumnaPinCount = 2;
        this->matrizPageTableLRU[numFilaElegida][numColumnaPinCount] = this->matrizPageTableLRU[numFilaElegida][numColumnaPinCount] + 1;
        cout << "Pin Cont descontando para la Pagina " << numPagina << endl;
    }
}

void PageTable::cambiarDirtyBitDePagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int numColumnaDirty = 1;
        if (this->matrizPageTableLRU[numFilaElegida][numColumnaDirty] == 1) {
            cout << "Dirty Bit 1 de la Pagina " << numPagina << endl;
            this->matrizPageTableLRU[numFilaElegida][numColumnaDirty] = 0;
            cout << "Dirty Bit camviado a " << this->matrizPageTableLRU[numFilaElegida][numColumnaDirty] << endl;
        }
        else {
            cout << "Dirty Bit 0 de la Pagina " << numPagina << endl;
            this->matrizPageTableLRU[numFilaElegida][numColumnaDirty] = 1;
            cout << "Dirty Bit camviado a " << this->matrizPageTableLRU[numFilaElegida][numColumnaDirty] << endl;
        }
    }
}

void PageTable::renovarLastUsedDePagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int numColumnaLastUsed = 3;
        this->matrizPageTableLRU[numFilaElegida][numColumnaLastUsed] = 0;
    }
}

void PageTable::aumentarLastUsedDePagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int numColumnaLastUsed = 3;
        this->matrizPageTableLRU[numFilaElegida][numColumnaLastUsed] = this->matrizPageTableLRU[numFilaElegida][numColumnaLastUsed] + 1;
    }
}

void PageTable::aumentarLastUsedDeTodasLasDemasPaginas(int numFrameAignorar) {
    cout << "---------- Actualizando la Page Table ----------" << endl;
    int numIdPaginaAux;
    for (int i = 0; i < this->columnaFrameIdSize; i++) {
        for (int j = 0; j < this->numColumnasEnPageTable; j++) {
            if (i == numFrameAignorar) {
                continue;
            }
            else {
                if (j == 3) {
                    numIdPaginaAux = this->matrizPageTableLRU[i][0];
                    this->aumentarLastUsedDePagina(numIdPaginaAux);
                    cout << "Frame Id: " << i << " - Aumento dado en LastUsed" << endl;
                    cout << "Agregando +1 a Last Used de todos los demás Pages" << endl;
                }
            }
        }
    }
    cout << "El aumento del Last Used a terminado." << endl;
}