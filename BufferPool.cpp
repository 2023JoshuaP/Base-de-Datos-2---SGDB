#include "BufferPool.h"

BufferPool::BufferPool() {}

BufferPool::~BufferPool() {}

void BufferPool::agregarNuevaPaginaBufferPool(int numFrame, int numPagina) {
    if (this->vectorFramesBufferPool[numFrame].paginaEnFrame.vectorRegistrosEnPagina.empty()) {
        this->vectorFramesBufferPool[numFrame].leerDatosEnPaginaDeFrame(numPagina);
    }
    else {
        this->vectorFramesBufferPool[numFrame].paginaEnFrame.vectorRegistrosEnPagina.clear();
        this->vectorFramesBufferPool[numFrame].leerDatosEnPaginaDeFrame(numPagina);
    }
}

void BufferPool::mostrarFramePagina(int numFrame) {
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.mostrarContenidoPagina();
}

void BufferPool::lecturaOescrituraPagina(int numFrame) {
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.leerOescribirPAgina();
}

void BufferPool::agregarContenidoPaginaABloque(int numFrame, int numPaginaEliminada) {
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.agregarContenido(numPaginaEliminada);
}