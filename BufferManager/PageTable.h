#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <iostream>
#include <vector>
using namespace std;

class PageTable{
    public:
        string nameColumnaFrameId = "FrameId";
        int columnaFrameIdSize;
        string nameColumnaPageId = "PageId";
        int columnPageIdSize;
        string nameColumnaDirttyId = "DirtyId";
        int columnaDirtyIdSize;
        string nameColumnaPinCount = "PinCount";
        int columnaPinCountSize;
        string nameColumnaLastUsed = "LastUsed";
        int columnaLastUsedSize;
        int numColumnasEnPageTable=4;//aparte de frameID
        vector<vector<int>> matrizPageTableLRU;
    public:
        PageTable(/* args */);
        ~PageTable();
        void mostrarPageTableLRU();
        bool verificarExistenciaDePagina(int numPagina);
        int getNumFrameDeUnaPagina(int numPagina);
        void descontarPinCountApagina(int numPagina);
        void aumentarPinCountDePagina(int numPagina);
        void cambiarDirtyBitDePagina(int numPagina);
        void renovarLastUsedDePagina(int numPagina);
        void aumentarLastUsedDePagina(int numPagina);
        void actualizarInfoDePageTableSolictandoNuevaPagina(int numPaginaActualizar, int numFilaFrameId);
        void aumentarLastUsedDeTodasLasDemasPaginas(int numFrameAignorar);
        void aplicarLRU(int numPagina, int numFrameAignorar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco, int &numPaginaEliminada);
        string analizarPageTableParaAgregarPagina(int numPagina);
        bool verificarFrameLlenos();
        void actualizarInformacionDePaginaEliminada(int numPaginaActualizar, int nuevaPaginaActualizar);
};

#endif