#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <vector>
#include <sstream>
#include <string>
#include "./PageTable.cpp"
#include "./BufferPool.cpp"
using namespace std;

class BufferManager {
    public:
        BufferPool bufferPool;
        PageTable pageTable;
    public:
        BufferManager();
        ~BufferManager();
        void crearBufferPoolSegunFrames(int numFrames);
        void establecerLimitedeFrames(int pesoBytesBloques);
        void obtenerUnaPagina(int numPagina);
        void mostrarUnaPagina(int numPagina);
        void mostrarPageTable();
        void dejarDeUsarPagina(int numPagina);
};

#endif