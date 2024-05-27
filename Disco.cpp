#include "Disco.h"
#include <filesystem>
namespace fs = std::filesystem;

void Disco::setNumPlatos(int platos) {
    this->numPlatos = platos;
    return;
}

void Disco::setPistasPorSuperficie(int superficie) {
    this->pistasPorSuperficie = superficie;
    return;
}

void Disco::setSectorPorPista(int sector) {
    this->sectorPorPista = sector;
    return;
}

void Disco::setBytesPorSector(int bytes) {
    this->bytesPorSector = bytes;
    return;
}

void Disco::crearCarpeta(const string& rutaCarpeta) {
    fs::create_directories
}