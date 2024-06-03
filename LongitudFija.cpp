#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

void esquema() {
    string fileCSV;
    string ruta = "/home/josue/Pruebas Longitudes/";
    cout << "File CSV a convertir: ";
    cin >> fileCSV;
    string pathCSV = ruta + fileCSV;
    if (fileCSV != "0") {
        ifstream file(pathCSV);
        if (file.is_open()) {
            string csvTXT;
            string esquema;
            cout << "Nombre del archivo TXT: ";
            cin >> csvTXT;
            cout << "Nombre del archivo de Esquema: ";
            cin >> esquema;

            ofstream fileRegistros(csvTXT, ios::app);
            ofstream fileEsquema(esquema, ios::app);
            string linea;
            vector<string> columnas;

            if (getline(file, linea)) {
                istringstream ss(linea);
                string campo;

                while (getline(ss, campo, ',')) {
                    columnas.push_back(campo);
                }

                string nameEsquema;
                cout << "Nombre de Esquema: ";
                cin >> nameEsquema;
                fileEsquema << nameEsquema << endl;

                for (const string& nombreColumna : columnas) {
                    string tipoDato;
                    string tamanio = "4";
                    bool tipoValido = false;

                    while (!tipoValido) {
                        cout << "Ingrese el tipo de dato para la Columna " << nombreColumna << " (int, float, str): ";
                        cin >> tipoDato;

                        if (tipoDato == "int" || tipoDato == "float" || tipoDato == "str") {
                            tipoValido = true;
                            if (tipoDato == "str") {
                                cout << "Ingrese su espacio para la columna " << nombreColumna << ": ";
                                cin >> tamanio;
                            }
                        } else {
                            cout << "Tipo de dato incorrecto." << endl;
                        }
                    }
                    fileEsquema << left << setw(20) << nombreColumna << setw(10) << tipoDato << setw(5) << tamanio << endl;
                }
            }

            while (getline(file, linea)) {
                istringstream ss(linea);
                string campo;
                bool firstLine = true;

                while (getline(ss, campo, ',')) {
                    if (campo.front() == '"' && campo.back() != '"') {
                        string campoCadena = campo;
                        while (getline(ss, campo, ',') && campo.back() != '"') {
                            campoCadena += ',' + campo;
                        }
                        campoCadena += "," + campo;
                        campo = campoCadena;
                    }

                    if (!firstLine) {
                        fileRegistros << ",";
                    }
                    fileRegistros << campo;
                    firstLine = false;
                }
                fileRegistros << endl;
            }

            fileRegistros.close();
            fileEsquema.close();
            file.close();
            cout << "Esquema y Registros creados." << endl;
        } else {
            cout << "Error en el archivo CSV." << endl;
        }
    } 
}

string ajustarCampo(const string& campo, int longitud) {
    if (campo.length() < longitud) {
        return campo + string(longitud - campo.length(), ' ');
    }
    else if (campo.length() > longitud) {
        return campo.substr(0, longitud);
    }
    return campo;
}

void longitudFija(const string& fileTXT, const string& esquema) {
    ifstream fileRegistros(fileTXT);
    ifstream fileEsquema(esquema);
    ofstream fileLonFija("registrosLongitudFija.txt");

    vector<string> columnasEsquema;
    vector<int> longitudes;

    if (fileEsquema.is_open()) {
        string linea;
        getline(fileEsquema, linea);
        while (getline(fileEsquema, linea)) {
            istringstream ss(linea);
            string atributo, tipoAtributo, tamanioAtributo;
            ss >> atributo >> tipoAtributo >> tamanioAtributo;
            columnasEsquema.push_back(atributo);
            longitudes.push_back(stoi(tamanioAtributo));
        }
        fileEsquema.close();
    }
    else {
        cout << "Error al abrir el archivo del Esquema." << endl;
    }

    if (fileRegistros.is_open()) {
        string linea;
        while (getline(fileRegistros, linea)) {
            istringstream ss(linea);
            string campo;
            bool firstField = true;
            int columnaIndice = 0;

            while (getline(ss, campo, ',')) {
                if (campo.front() == '"' && campo.back() != '"') {
                    string campoCadena = campo;
                    while (getline(ss, campo, ',') && campo.back() != '"') {
                        campoCadena += ',' + campo;
                    }
                    campoCadena += ',' + campo;
                    campo = campoCadena;
                }
                campo = ajustarCampo(campo, longitudes[columnaIndice]);

                if (!firstField) {
                    fileLonFija << "|";
                }
                fileLonFija << campo;
                firstField = false;
                columnaIndice++;
            }
            fileLonFija << endl;
        }
        fileRegistros.close();
        fileLonFija.close();
    }
    else {
        cerr << "Error en el archivo de Registros." << endl;
    }
}

int main() {
    esquema();
    string fileTXT;
    string esquema;
    cout << "Nombre de archivo Registros: ";
    cin >> fileTXT;
    cout << "Nombre de Esquema: ";
    cin >> esquema;

    longitudFija(fileTXT, esquema);
}