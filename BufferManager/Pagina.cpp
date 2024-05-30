#include "./Pagina.h"

Pagina::Pagina() {}

Pagina::~Pagina() {}

int tamanioString = 0;
string rutaCompleta = "";

bool isNumber(const std::string &s) {
    for (char const &ch : s)
    {
        if (std::isdigit(ch) == 0 && ch != '.')
            return false;
    }
    return true;
}

/* Funcion modificada por Piero*/
void Pagina::recogerRegistros(int numPagina)
{
    string numPaginaString = to_string(numPagina);
    string nameBloque = "Bloque";
    rutaCompleta = "../Bloques/" + nameBloque+numPaginaString + ".txt";
    cout << "Intentando abrir el archivo en: " << rutaCompleta << endl;
    ifstream fileReadBloques(rutaCompleta);

    if (!fileReadBloques.is_open()) {
        cout << "Error t5656: no se pudo abrir " + rutaCompleta << endl;
    }
    else {
        cout << "EXITO t5656: SI se pudo abrir" + rutaCompleta << endl;
        string lineaDeRegistroAux;
        string valor;
        this->vectorRegistrosEnPagina.clear();
        cout << "tamanio string: " << endl;
        cin >> tamanioString;
        while (getline(fileReadBloques,lineaDeRegistroAux)) {
            string linea_registro;
            stringstream ss(lineaDeRegistroAux);
            bool primerValor = true;
            while (getline(ss,valor,',')) {
                if (!primerValor) {
                    linea_registro += ',';
                }
                else {
                    primerValor = false;
                }
                int peso = valor.size();
                if (isNumber(valor)) {
                    linea_registro += valor;
                    continue;
                }
                else {
                    while (peso < tamanioString) {
                        valor += ' ';
                        peso += 1;
                    }
                    linea_registro += valor;
                }
            }
            this->vectorRegistrosEnPagina.push_back(linea_registro);
        }
        cout << "Recogida de datos terminado" << endl;
    }
    
}

void Pagina::mostrarContenidoDePagina() {
    cout << "-------------------PAgina: mostrarContenidoDePagina()-------------------" << endl;
    for (size_t i =0 ; i < this->vectorRegistrosEnPagina.size(); i++) {
        cout << this->vectorRegistrosEnPagina[i] << endl;
    }
    cout << "------------------------------------------------------------------------" << endl;
    
}

void Pagina::leerOescribirEnPagina() {
    int filaAencontrar;
    string registroNuevo;
    string cadenaFinal = "";
    
    cout << "-------------------PAgina: leerOescribirEnPagina()----------------------" << endl;
    cout << "Fila a editar: ";
    cin >> filaAencontrar;
    cin.ignore();
    
    string& registro = this->vectorRegistrosEnPagina[filaAencontrar];
    
    cout << "Registro actual: " << registro << endl;
    
    vector<string> valoresRegistroNuevo;
    stringstream ss(registro);
    string valor;
    
    cout << "Registro nuevo: ";
    getline(cin, registroNuevo);
    stringstream ssNuevo(registroNuevo);

    while (getline(ssNuevo, valor, ',')) {
        valoresRegistroNuevo.push_back(valor);
    }

    for (size_t i = 0; i < valoresRegistroNuevo.size();++i) {
        if (isNumber(valoresRegistroNuevo[i]) == true) {
            cadenaFinal += valoresRegistroNuevo[i] + ',';
        }
        if (isNumber(valoresRegistroNuevo[i]) == false) {
            cadenaFinal += valoresRegistroNuevo[i];
            int pesoValor = valoresRegistroNuevo[i].size();
            do {
                cadenaFinal += " ";
                pesoValor += 1;
            } while (pesoValor < tamanioString);
            
            if (i < valoresRegistroNuevo.size() - 1) {
                cadenaFinal += ',';
            }
        }
    }
    this->vectorRegistrosEnPagina[filaAencontrar] = cadenaFinal;
    cout << "Guardado" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    
}

bool Pagina::verificarPaginaVacia() {
    if (this->vectorRegistrosEnPagina.empty()) {
        return true;
    }
    else {
        return false;
    }    
}

void Pagina::agregarContenido(int numPaginaEliminada) {
    cout << "-------------------PAgina: agregarContenido()----------------------" << endl;
    string rutaBloqueEscribir="./Bloques/Bloque"+to_string(numPaginaEliminada)+".txt";
    ofstream rutaBloque(rutaBloqueEscribir, ios::trunc);
    if (!rutaBloque.is_open()) {
        cout<<"No abrio correctamente: "<<rutaBloqueEscribir<<endl;
    }
    else {
        for (size_t i = 0; i <= this->vectorRegistrosEnPagina.size(); ++i) {
            rutaBloque << this->vectorRegistrosEnPagina[i] << endl;
        }
        cout << "Contenido de pagina en memoria mandado a bloque correctamente" << endl;
    }
    
}

