#include "./PageTable.h"

PageTable::PageTable(/* args */) {}

PageTable::~PageTable() {}

void PageTable::mostrarPageTableLRU() {
    int numFilas = this->matrizPageTableLRU.size();
    int numColumas = this->numColumnasEnPageTable;
    cout << "Frame id \t PageId \t DirtyBit \t Pin Count \t Last Used" << endl;
    for (int i = 0; i < numFilas; i++) {
        cout << i << "\t\t";
        for (int j = 0; j < numColumas; j++) {
            cout << this->matrizPageTableLRU[i][j] << "\t\t";
        }
        cout << endl;
    }
}

bool PageTable::verificarExistenciaDePagina(int numPagina) {
    cout << "----------------verificarExistenciaDePagina()--------------" << endl;
    int j = 0;
    for (int i = 0; i < this->columnaFrameIdSize; i++) {
        if (this->matrizPageTableLRU[i][j] == numPagina) {
            cout << "PAG " + to_string(numPagina) + " SI existe" << endl;
            return true;
        }
    }
    cout << "PAG " + to_string(numPagina) + " NO existe" << endl;
    return false;
}

int PageTable::getNumFrameDeUnaPagina(int numPagina) {
    cout << "--------------------------getNumFrameDeUnaPagina()--------------------" << endl;

    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                cout << "PAgina hallada devolviendo numero de frame: " << endl;
                return i;
            }
        }
    }
    else {
        cout << "No existe dicha Página para obtener el numero de fram" << endl;
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j]) {
                cout <<this->matrizPageTableLRU[i][j]<< "PAgina si tiene valor" << endl;
            }
            else {
                cout << "Espacio vacio page id confirmado" << endl;
                return i;
            }
        }
    }
}

void PageTable::descontarPinCountApagina(int numPagina) {
    cout << "-------------------descontarPinCountApagina()-----------.------" << endl;
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int numColumnaPinCount = 2; // 0,1,2,3

        this->matrizPageTableLRU[numFilaElegida][numColumnaPinCount] = this->matrizPageTableLRU[numFilaElegida][numColumnaPinCount] - 1;
        cout<<"Descuento aplicado a Pin Count de página: "<<numPagina<<endl;
    }
}

void PageTable::aumentarPinCountDePagina(int numPagina) {
    cout << "-------------------aumentarPinCountDePagina()-----------.------" << endl;
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true)
    {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++)
        {
            if (this->matrizPageTableLRU[i][j] == numPagina)
            {
                numFilaElegida = i;
            }
        }
        int numColumnaPinCount = 2; // 0,1,2,3

        this->matrizPageTableLRU[numFilaElegida][numColumnaPinCount] = this->matrizPageTableLRU[numFilaElegida][numColumnaPinCount] + 1;
    }
}

void PageTable::cambiarDirtyBitDePagina(int numPagina) {
    cout << "-------------------cambiarDirtyBitDePagina()-----------.------" << endl;
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true)
    {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++)
        {
            if (this->matrizPageTableLRU[i][j] == numPagina)
            {
                numFilaElegida = i;
            }
        }
        int numColumnaDirtyBit = 1; // 0,1,2,3
        if (this->matrizPageTableLRU[numFilaElegida][numColumnaDirtyBit] == 1)
        {
            cout << "DirtyBit 1 de pagina numero: " << numPagina << endl;
            this->matrizPageTableLRU[numFilaElegida][numColumnaDirtyBit] = 0;
            cout << "DirtyBit cambiado a : " << this->matrizPageTableLRU[numFilaElegida][numColumnaDirtyBit] << endl;
        }
        else
        {
            cout << "DirtyBit 0 de pagina numero: " << numPagina << endl;
            this->matrizPageTableLRU[numFilaElegida][numColumnaDirtyBit] = 1;
            cout << "DirtyBit cambiado a : " << this->matrizPageTableLRU[numFilaElegida][numColumnaDirtyBit] << endl;
        }
    }
}

void PageTable::renovarLastUsedDePagina(int numPagina) {
    cout << "-------------------renovarLastUsedDePagina()-----------.------" << endl;
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true)
    {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++)
        {
            if (this->matrizPageTableLRU[i][j] == numPagina)
            {
                numFilaElegida = i;
            }
        }
        int numColumnaLastUsed = 3; // 0,1,2,3

        this->matrizPageTableLRU[numFilaElegida][numColumnaLastUsed] = 0;
    }
}

void PageTable::aumentarLastUsedDePagina(int numPagina) {
    cout << "-------------------aumentarLastUsedDePagina()-----------.------" << endl;
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int numColumnaLastUsed = 3; // 0,1,2,3
        this->matrizPageTableLRU[numFilaElegida][numColumnaLastUsed] = this->matrizPageTableLRU[numFilaElegida][numColumnaLastUsed] + 1;
    }
}

void PageTable::aumentarLastUsedDeTodasLasDemasPaginas(int numFrameAignorar) {
    cout << ".-----------------------aumentarLastUsedDeTodasLasDemasPaginas() ----------------------" << endl;
    cout << ">>> Actualizando PageTAble" << endl;
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
                    cout << "frame id: " << i << " - Aumento dado en LastUsed" << endl;
                    cout << "Agregando +1 a Last Used de todos los demás Pages" << endl;
                }
            }
        }
    }
    cout << "aumentarLastUsedDeTodasLasDemasPaginas terminado" << endl;
}

void PageTable::actualizarInfoDePageTableSolictandoNuevaPagina(int numPaginaActualizar, int numFilaFrameId) {
    cout << ".-----------------------actualizarInfoDePageTableSolictandoNuevaPagina() ----------------------" << endl;
    cout << ">>> Actualizando PageTAble" << endl;
    for (int j = 0; j < this->numColumnasEnPageTable; j++) {
        if (j == 0) {
            this->matrizPageTableLRU[numFilaFrameId][j] = numPaginaActualizar;
            cout << "frame id: " << numFilaFrameId << " - Page id establecida: " << numPaginaActualizar << endl;
        }
        else if (j == 1) {
            if (this->matrizPageTableLRU[numFilaFrameId][j] == 1) {
                cout << "frame id: " << numFilaFrameId << " - No se cambió el DirtyBit=1" << endl;
            }
            else {
                this->matrizPageTableLRU[numFilaFrameId][j] = 0;
                cout << "frame id: " << numFilaFrameId << " - DirtyBit=0" << endl;
            }
        }
        else if (j == 2) {
            this->aumentarPinCountDePagina(numPaginaActualizar);
            cout << "frame id: " << numFilaFrameId << " - Pin Count establecida: " << endl;
        }
        else if (j == 3) {
            this->renovarLastUsedDePagina(numPaginaActualizar);
            cout << "frame id: " << numFilaFrameId << " - Aumento dado en LastUsed" << endl;
            cout << "Agregando +1 a Last Used de todos los demás Pages" << endl;
            int numFrameAignorar = this->getNumFrameDeUnaPagina(numPaginaActualizar);
            this->aumentarLastUsedDeTodasLasDemasPaginas(numFrameAignorar);
        }
    }
    cout << "Datos de Page Table actualizado" << endl;
}

void PageTable::aplicarLRU(int numPagina, int numFrameAignorar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco, int &numPaginaEliminada) {
    cout << "---------------------aplicarLRU()------------------" << endl;
    int numColLastUsed = 3;
    int numColPinCount = 2;
    int numColDirtyBit = 1;
    int numColPageId = 0;

    int acumuladorMayorLastUsed = 0;
    int numFrameDelMayorLastUsed = 0;
    int numPagDelMayorLastUsed = 0;
    for (int i = 0; i < this->columnaFrameIdSize; i++) {
        if (i == numFrameAignorar) {
            continue;
        }
        else {
            if(acumuladorMayorLastUsed < this->matrizPageTableLRU[i][numColLastUsed]) {
                acumuladorMayorLastUsed = this->matrizPageTableLRU[i][numColLastUsed];
                numFrameDelMayorLastUsed = i;
                numPagDelMayorLastUsed = this->matrizPageTableLRU[i][numColPageId];
            }
        }         
    }
    cout << "Revisando Pin Count" << endl;
    if (this->matrizPageTableLRU[numFrameDelMayorLastUsed][numColPinCount]==0) {
        cout << "Que bien, pin count libre" << endl;
        cout << "Antes de eliminar, revisaremos dirty bit" << endl;
        if (this->matrizPageTableLRU[numFrameDelMayorLastUsed][numColDirtyBit]==0) {
            cout << "Dirty Bit = 0" << endl;
            cout<<" Solo se eliminará la PAGINA, sin escribir en Disco"<<endl;
            actualizarInformacionDePaginaEliminada(numPagDelMayorLastUsed,numPagina);
            eliminarPageSinEscrituraEnDisco = true;
            eliminarPageConEscrituraEnDisco = false;
        }
        else {
            cout << "Dirty Bit = 1" << endl;
            cout << " Se eliminará la PAGINA, PERO SE ESCRIBIRÁ CAMBIOS EN DISCO" << endl;
            actualizarInformacionDePaginaEliminada(numPagDelMayorLastUsed,numPagina);
            numPaginaEliminada=numPagDelMayorLastUsed;
            eliminarPageConEscrituraEnDisco = true;
            eliminarPageSinEscrituraEnDisco = false;
        }  
        
    }
    else {
        cout << "Que MAL, pin count NO LIBRE" << endl;
        aplicarLRU(numPagina, numFrameDelMayorLastUsed, eliminarPageSinEscrituraEnDisco, eliminarPageConEscrituraEnDisco,numPaginaEliminada);
    }
    
}

string PageTable::analizarPageTableParaAgregarPagina(int numPagina) {
    cout << "---------------------analizarPageTableParaAgregarPagina()----------------" << endl;
    if (this->verificarExistenciaDePagina(numPagina) == true) {
        cout << "Pagina ya encontrada" << endl;
        int numFrame = this->getNumFrameDeUnaPagina(numPagina);
        this->actualizarInfoDePageTableSolictandoNuevaPagina(numPagina, numFrame);
        string normal="normal";
        normal=normal+","+to_string(INT16_MAX);
        return normal;
    }
    else {
        bool eliminarPageSinEscrituraEnDisco = false;
        bool eliminarPageConEscrituraEnDisco = false;
        cout << "$$$$$Pagina NO ESTA EN PAGE TABLE" << endl;
        if (this->verificarFrameLlenos()==true) {
            cout<<"Frames llenos"<<endl;
            int numPaginaEliminada=INT16_MAX;
            aplicarLRU(numPagina,INT16_MAX, eliminarPageSinEscrituraEnDisco, eliminarPageConEscrituraEnDisco, numPaginaEliminada);
            if (eliminarPageSinEscrituraEnDisco==true && eliminarPageConEscrituraEnDisco==false) {

                string primerBool="eliminarPageSinEscrituraEnDisco";
                primerBool=primerBool+","+to_string(numPaginaEliminada);
                return primerBool;
            }
            else if(eliminarPageConEscrituraEnDisco==true && eliminarPageSinEscrituraEnDisco==false) {
                string segundoBool="eliminarPageConEscrituraEnDisco";
                segundoBool=segundoBool+","+to_string(numPaginaEliminada);
                return segundoBool;
            }
        }
        else {
            cout<<"/////////Frames no llenos (Aun hay space)"<<endl;
            int numFrame = this->getNumFrameDeUnaPagina(numPagina);
            this->actualizarInfoDePageTableSolictandoNuevaPagina(numPagina, numFrame);
            string normal="normal";
            normal=normal+","+to_string(INT16_MAX);
            return normal;
        }

    }
}

bool PageTable::verificarFrameLlenos() {
    cout<<"--------------verificarFrameLlenos()--------------"<<endl;
    int acumulador = 0;
    int j = 0;
    for (int i = 0; i < this->columnaFrameIdSize; i++) {
        if (this->matrizPageTableLRU[i][j]) {
            continue;
        }
        else {
            acumulador++;
        }
        
    }
    if (acumulador != 0) {
        return false;
    }
    else {
        return true;
    }
}


void PageTable::actualizarInformacionDePaginaEliminada(int numPaginaEliminar, int nuevaPaginaIngresar) {
    cout << "-------------------actualizarInformacionDePaginaEliminada()-----------.------" << endl;
    int numFilaElegida;
    if (this->verificarExistenciaDePagina(numPaginaEliminar) == true) {
        int j = 0;
        for (int i = 0; i < this->columnaFrameIdSize; i++) {
            if (this->matrizPageTableLRU[i][j] == numPaginaEliminar) {
                cout<<"&&&&&&& numPaginaEliminar: "<<numPaginaEliminar<<endl;
                numFilaElegida = i;
            }
        }
        for (int j = 0; j < this->numColumnasEnPageTable; j++) {
            this->matrizPageTableLRU[numFilaElegida][j] = 0;
        }
    }
    cout << "Agregando Datos de nuevo registro" << endl;

    cout << ".-----------------------actualizarInformacionDePaginaEliminada PARTE 2() ----------------------" << endl;
    cout << ">>> Actualizando PageTAble" << endl;
    for (int j = 0; j < this->numColumnasEnPageTable; j++) {
        if (j == 0) {
            this->matrizPageTableLRU[numFilaElegida][j] = nuevaPaginaIngresar;
            cout << "frame id: " << numFilaElegida << " - Page id establecida: " << nuevaPaginaIngresar << endl;
        }
        else if (j == 1) {
            this->matrizPageTableLRU[numFilaElegida][j] = 0;
            cout << "frame id: " << numFilaElegida << " - DirtyBit=0" << endl;
        }
        else if (j == 2) {
            this->aumentarPinCountDePagina(nuevaPaginaIngresar);
            cout << "frame id: " << numFilaElegida << " - Pin Count establecida: " << nuevaPaginaIngresar << endl;
        }
        else if (j == 3) {
            this->renovarLastUsedDePagina(nuevaPaginaIngresar);
            cout << "frame id: " << numFilaElegida << " - Aumento dado en LastUsed" << endl;
            cout << "Agregando +1 a Last Used de todos los demás Pages" << endl;
            int numFilaElegida = this->getNumFrameDeUnaPagina(nuevaPaginaIngresar);
            this->aumentarLastUsedDeTodasLasDemasPaginas(numFilaElegida);
        }
    }
    cout << "Datos de Page Table actualizado" << endl;
}