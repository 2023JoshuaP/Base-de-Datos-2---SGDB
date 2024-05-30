#include "BufferManager.h"
#include <fstream>

BufferManager::BufferManager() {}

BufferManager::~BufferManager() {}

void BufferManager::crearBufferPoolSegunFrames(int numFrames) {
    this->bufferPool.vectorFramesBufferPool.resize(numFrames);
    this->pageTable.columnaFrameIdSize = numFrames;
    this->pageTable.columnPageIdSize = 0;
    this->pageTable.columnaDirtyIdSize = 0;
    this->pageTable.columnaPinCountSize = 0;
    this->pageTable.columnaLastUsedSize = 0;


    cout << "----------------------------" << endl;
    cout << "Inicializando la Page Table." << endl;
    cout << "----------------------------" << endl;

    this->pageTable.matrizPageTableLRU.resize(numFrames);

    for (int i = 0; i < numFrames; i++) {
        for (int j = 0; j < this->pageTable.numColumnasEnPageTable; j++) {
            this->pageTable.matrizPageTableLRU[i].resize(this->pageTable.numColumnasEnPageTable);
        }
    }
}

void BufferManager::establecerLimitedeFrames(int pesoBytesBloque) {
    this->bufferPool.capacidadDeCadaFrame = pesoBytesBloque;
    for (int i = 0; i < this->bufferPool.vectorFramesBufferPool.size(); i++) {
        this->bufferPool.vectorFramesBufferPool[i].capacidadBytesDeFrame = pesoBytesBloque;
    }
}

void BufferMAnager::obtenerUnaPagina(int numPagina) {
    string resultadosParaEliminacionYCambios = this->pageTable.analizarPageTableParaAgregarPagina(numPagina);
    cout << "-----------------------------------------------" << endl;
}