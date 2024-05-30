#include "./BufferManager.h"
#include <fstream>
using namespace std;

BufferManager::BufferManager(){}

BufferManager::~BufferManager(){}

void BufferManager::crearBufferPoolSegunNumFrames(int numFrames) {
    this->bufferPool.vectorFramesBufferPool.resize(numFrames);

    this->pageTable.columnaFrameIdSize = numFrames;
    this->pageTable.columnPageIdSize = 0;
    this->pageTable.columnaDirtyIdSize = 0;
    this->pageTable.columnaPinCountSize = 0;
    this->pageTable.columnaLastUsedSize = 0;

    cout<<"inicializando pageTable"<<endl;
    this->pageTable.matrizPageTableLRU.resize(numFrames);

    for (int i = 0; i < numFrames; i++) {
        for (int j = 0; j < this->pageTable.numColumnasEnPageTable; j++) {
            this->pageTable.matrizPageTableLRU[i].resize(this->pageTable.numColumnasEnPageTable);
        }
    }
}

void BufferManager::establecerLimiteDeFrames(int pesoBytesBLoque) {
    this->bufferPool.capacidadDeCadaFrame = pesoBytesBLoque;
    for (size_t i = 0; i < this->bufferPool.vectorFramesBufferPool.size(); i++) {
        this->bufferPool.vectorFramesBufferPool[i].capacidadBytesDeFrame = pesoBytesBLoque;
    }
}

void BufferManager::obtenerUnaPagina(int numPagina)
{
    cout<<"----------------obtenerUnaPagina()-------------------"<<endl;
    
    string resultadosParaEliminacionYCambios=this->pageTable.analizarPageTableParaAgregarPagina(numPagina);
    cout<<"::::::::::::::::::::::::::DAME RESULTADOOOOO::::::"<<resultadosParaEliminacionYCambios<<endl;
    istringstream iss(resultadosParaEliminacionYCambios);
    string resultado;
    string paginaEliminada;
    getline(iss,resultado,',');
    getline(iss,paginaEliminada,',');

    if (resultado=="eliminarPageSinEscrituraEnDisco") {
        //eliminarPageSinEscrituraEnDisco
        cout<<">>>>>>>> eliminarPageSinEscrituraEnDisco"<<endl;
        cout << "Datos cambiados segun LRU en Page Table" << endl;
        this->pageTable.mostrarPageTableLRU();


        cout << "Aplicando cambios en Buffer Pool segun Page Table" << endl;
        cout << "Mandando a agregar la nueva Pagina" << endl;
        int numFrameDePagina = this->pageTable.getNumFrameDeUnaPagina(numPagina);

        cout<<"Ingresando Página al BufferPoll dentro vector de Frames...."<<endl;
        this->bufferPool.agregarNuevaPaginaBufferPool(numFrameDePagina,numPagina);
        this->bufferPool.mostrarFramePagina(numFrameDePagina);
        /*Falta hacer esto:*/
    }
    else if(resultado=="eliminarPageConEscrituraEnDisco") {
        //eliminarPageConEscrituraEnDisco
        cout<<">>>>>>>> eliminarPageConEscrituraEnDisco"<<endl;
        cout << "Datos cambiados segun LRU en Page Table" << endl;
        this->pageTable.mostrarPageTableLRU();

        cout << "Aplicando cambios en Buffer Pool segun Page Table" << endl;
        cout << "Mandando a agregar la nueva Pagina" << endl;
        int numFrameDePagina = this->pageTable.getNumFrameDeUnaPagina(numPagina);

        int numFrameDePaginaEliminada = this->pageTable.getNumFrameDeUnaPagina(numPagina);
        int numPaginaEliminada=stoi(paginaEliminada);
        

        cout<<"Ingresando Página al BufferPoll dentro vector de Frames...."<<endl;
        this->bufferPool.agregarContenidoPaginaAbloque(numFrameDePaginaEliminada, numPaginaEliminada);
        this->bufferPool.agregarNuevaPaginaBufferPool(numFrameDePagina,numPagina);
        this->bufferPool.mostrarFramePagina(numFrameDePagina);
        //this->bufferPool.agregarNuevaPaginaBufferPool(numFrameDePagina,numPagina);
        //this->bufferPool.mostrarFramePagina(numFrameDePagina);
    }
    else {
        cout<<">>>>>>>> normal NO hay eliminacion"<<endl;
        this->pageTable.mostrarPageTableLRU();

        cout << "Aplicando cambios en Buffer Pool segun Page Table" << endl;
        cout << "Mandando a agregar la nueva Pagina" << endl;

        int numFrameDePagina = this->pageTable.getNumFrameDeUnaPagina(numPagina);

        cout<<"Ingresando Página al BufferPoll dentro vector de Frames...."<<endl;
        this->bufferPool.agregarNuevaPaginaBufferPool(numFrameDePagina,numPagina);
        this->bufferPool.mostrarFramePagina(numFrameDePagina);
    }
    
}

void BufferManager::mostrarUnaPagina(int numPagina) {
    cout<<"----------------------- mostrarUnaPagina -------------------------"<<endl;
    if (this->pageTable.verificarExistenciaDePagina(numPagina) == true) {
        cout << "Existencia de pàgina verificada Verificada" << endl;
        cout << "MOstrandoDichaPAgina" << endl;
        int numFrameDePagina = this->pageTable.getNumFrameDeUnaPagina(numPagina);
        this->bufferPool.vectorFramesBufferPool[numFrameDePagina].paginaEnFrame.mostrarContenidoDePagina();
    }
    else {
        cout << "NO EXISTE DICHA PÀGINA" << endl;
        cout << "Procediendo a pedido de nueva pàgina..." << endl;
    }
    
    
}

void BufferManager::mostrarPageTAble() {
    cout << "--------------------Bloque mostrarPageTAble() -------------------------" << endl;
    this->pageTable.mostrarPageTableLRU();
}


void BufferManager::dejarDeUsarUnaPagina(int numPagina) {
    this->pageTable.descontarPinCountApagina(numPagina);
}
