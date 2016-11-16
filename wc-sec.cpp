#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, int> cantidades;

int main(int argc, char* argv[])
{
    //esto es para validar que se haya especificado al menos un archivo
    if (argc <= 1) {
      cout << "Uso: wc-sec archivo1 archivo2 archivo3 archivoN" << '\n';
      return 1;
    }

    auto inicio = chrono::high_resolution_clock::now();

    for(int i = 1; i < argc; ++i) {
        ifstream archivo(argv[i]);
        int cantidad = 0;
        string palabra;
        while(!archivo.eof() and archivo >> palabra)
            ++cantidad;
        cantidades[argv[i]] = cantidad;
    }

    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    int total = 0;
    for (auto & info : cantidades) {
        cout << info.second << " " << info.first << endl;
        total += info.second;
    }
    cout << total << " total" << endl;
    cout << "Tiempo: " << duracion << " ms" << endl;
}
