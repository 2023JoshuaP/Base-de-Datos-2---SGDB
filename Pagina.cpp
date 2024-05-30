#include "./Pagina.h"

int tamString = 0;
string rutaCompleta = "";

bool isNumber(const string& s) {
    for (char const &ch : s) {
        if (isdigit(ch) == 0 && ch != '.') {
            return false;
        }
    }
    return true;
}

Pagina::Pagina() {}

void Pagina::recogerRegistros(int numPagina) {
    int plato, superficie, pista, bloque;
    
    string numPaginaString = "Bloque";
    rutaCompleta = "/home/josue/Base de Datos II - SGBD/Base-de-Datos-2---SGDB/output/Disco/Plato " + to_string(plato) + 
                   "/Superficie " + to_string(superficie) + "/Pista " + to_string(pista) + "/" + numPaginaString + " " + to_string(bloque) + ".txt";
    
    cout << "Intentando abrir el archivo." << endl;
    ifstream fileReadBloques(rutaCompleta);

    if (!fileReadBloques.is_open()) {
        cout << "No se puede abrir el archivo." << endl;
    }
    else {
        cout << "Archivo abierto." << endl;
        string lineaRegistroAux;
        string valor;

        this->vectorRegistrosEnPagina.clear();

        cout << "Longitud de String: ";
        cin >> tamString;

        while (getline(fileReadBloques, lineaRegistroAux)) {
            string lineaRegistro;
            stringstream ss(lineaRegistroAux);
            bool primerValor = true;
            while (getline(ss, valor, '#')) {
                if (!primerValor) {
                    lineaRegistro += '#';
                }
                else {
                    primerValor = false;
                }

                int peso = valor.size();
                if (isNumber(valor)) {
                    lineaRegistro += valor;
                    continue;
                }
                else {
                    while (peso < tamString) {
                        valor += ' ';
                        peso += 1;
                    }
                    lineaRegistro += valor;
                }
            }
            this->vectorRegistrosEnPagina.push_back(lineaRegistro);
        }
        cout << "Regogida de Datos terminada." << endl;
    }
}

void Pagina::mostrarContenidoPagina() {
    for (size_t i = 0; i < this->vectorRegistrosEnPagina.size(); i++) {
        cout << this->vectorRegistrosEnPagina[i] << endl;
    }
}

void Pagina::leerOescribirPAgina() {
    int fila;
    string registroNuevo;
    string cadenaFinal = "";
    cout << "Fila que se va a editar: ";
    cin >> fila;
    cin.ignore();

    string& registro = this->vectorRegistrosEnPagina[fila];
    cout << "Registro actual: " << registro << endl;
    vector<string> valoresRegistroNuevo;
    stringstream ss(registro);
    string valor;

    cout << "Registro nuevo: ";
    getline(cin, registroNuevo);
    stringstream ssNuevo(registroNuevo);

    while (getline(ssNuevo, valor, '#')) {
        valoresRegistroNuevo.push_back(valor);
    }

    for (int i = 0; i < valoresRegistroNuevo.size(); i++) {
        if (isNumber(valoresRegistroNuevo[i]) == true) {
            cadenaFinal += valoresRegistroNuevo[i] + '#';
        }
        if (isNumber(valoresRegistroNuevo[i]) == false) {
            cadenaFinal += valoresRegistroNuevo[i];
            int pesoValor = valoresRegistroNuevo[i].size();

            do {
                cadenaFinal += " ";
                pesoValor += 1;
            } while (pesoValor < tamString);

            if (i < valoresRegistroNuevo.size() - 1) {
                cadenaFinal += '#';
            }
        }
    }
    this->vectorRegistrosEnPagina[fila] = cadenaFinal;
    cout << "Guardado exitoso." << endl;
}

Pagina::~Pagina() {}