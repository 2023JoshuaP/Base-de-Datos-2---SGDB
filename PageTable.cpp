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

void PageTable::actualizarInfoDePageTableSolictandoNuevaPagina(int numPaginaActualizar, int numFilaFrameId) {
    cout << "---------- Actualizando la Page Table ----------" << endl;
    for (int j = 0; j < this->numColumnasEnPageTable; j++) {
        if (j == 0) {
            this->matrizPageTableLRU[numFilaFrameId][j] =numPaginaActualizar;
            cout << "-----------------------------------" << endl;
            cout << "Frame Id: " << numFilaFrameId << endl;
            cout << "Page Id: " << numPaginaActualizar << endl;
            cout << "-----------------------------------" << endl;
        }
        else if (j == 1) {
            if (this->matrizPageTableLRU[numFilaFrameId][j] == 1) {
                cout << "-----------------------------------" << endl;
                cout << "Frame Id: " << numFilaFrameId << endl;
                cout << "No se cambio el DirtyBit = 1" << endl;
                cout << "-----------------------------------" << endl;
            }
            else {
                this->matrizPageTableLRU[numFilaFrameId][j] = 0;
                cout << "-----------------------------------" << endl;
                cout << "Frame Id: " << numFilaFrameId << endl;
                cout << "Dirty Bit = 0" << endl;
                cout << "-----------------------------------" << endl;
            }
        }
        else if (j == 2) {
            this->aumentarPinCountDePagina(numPaginaActualizar);
            cout << "-----------------------------------" << endl;
            cout << "Frame id: " << numFilaFrameId << endl;
            cout << "Aumento dado en Last Used." << endl;
            cout << "Agregando +1 a los Last Used de las demas Paginas." << endl;
            cout << "-----------------------------------" << endl;
            int numFrameAignorar = this->getNumFrameDeUnaPagina(numPaginaActualizar);
            this->aumentarLastUsedDeTodasLasDemasPaginas(numFrameAignorar);
        }
    }
    cout << "Datos de la Page Table actualizados correctamente." << endl;
}

void PageTable::aplicarLRU(int numPagina, int numFrameAignorar, bool& eliminarPageSinEscrituraEnDisco, bool& eliminarPageConEscrituraEnDisco, int& numPaginaEliminada) {
    cout << "---------- Aplicando el LRU ----------" << endl;
    int numColLastUsed = 3;
    int numColPinCount = 2;
    int numColDirtyBit = 1;
    int numColPageId = 0;

    int acumuladorLastUsed = 0;
    int numFrameDelMayorLastUsed = 0;
    int numPagDelMayorLastUsed = 0;

    for (int i = 0; i < this->columnaFrameIdSize; i++) {
        if (i == numFrameAignorar) {
            continue;
        }
        else {
            if (acumuladorLastUsed < this->matrizPageTableLRU[i][numColLastUsed]) {
                acumuladorLastUsed = this->matrizPageTableLRU[i][numColLastUsed];
                numFrameDelMayorLastUsed = 1;
                numPagDelMayorLastUsed = this->matrizPageTableLRU[i][numColPageId];
            }
        }
    }
    cout << "-----------------------------------" << endl;
    cout << "Revisando el Pin Count" << endl;
    cout << "-----------------------------------" << endl;

    if (this->matrizPageTableLRU[numFrameDelMayorLastUsed][numColPinCount] == 0) {
        cout << "-----------------------------------" << endl;
        cout << "Pin Count se encuentra libre." << endl;
        cout << "Antes de que se elimine se revisara el Dirty Bit" << endl;
        cout << "-----------------------------------" << endl;
        if (this->matrizPageTableLRU[numFrameDelMayorLastUsed][numColDirtyBit] == 0) {
            cout << endl;
            cout << "-----------------------------------" << endl;
            cout << "Dirty Bit = 0." << endl;
            cout << "Se procede a eliminar la Pagina, mas no escribira en el Disco." << endl;
            cout << "-----------------------------------" << endl;
            eliminarPageSinEscrituraEnDisco = true;
            eliminarPageConEscrituraEnDisco = false;
        }
        else {
            cout << endl;
            cout << "-----------------------------------" << endl;
            cout << "Dirty Bit = 1." << endl;
            cout << "Se procede a eliminar la Pagina, se escribira con cambios en el disco." << endl;
            cout << "-----------------------------------" << endl;
            eliminarPageConEscrituraEnDisco = true;
            eliminarPageSinEscrituraEnDisco = false;
        }
    }
    else {
        cout << endl;
        cout << "-----------------------------------" << endl;
        cout << "El Pin Count no se encuentra libre." << endl;
        cout << "-----------------------------------" << endl;

        aplicarLRU(numPagina, numFrameDelMayorLastUsed, eliminarPageSinEscrituraEnDisco, eliminarPageConEscrituraEnDisco, numPaginaEliminada);
    }
}