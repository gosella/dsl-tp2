#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

using namespace std;

map<string, int> cantidades;

void contar_palabras(const char *nombre_archivo)
{
    ifstream archivo(nombre_archivo);
    string palabra;
    int cantidad = 0;
    while(!archivo.eof() and archivo >> palabra)
        ++cantidad;
    cantidades[nombre_archivo] = cantidad;
}

int main(int argc, char* argv[])
{
    auto inicio = chrono::high_resolution_clock::now();

    vector<thread> hilos;

    for(int i = 0; i < argc-1; ++i) {
        cantidades[argv[i+1]] = 0;
        hilos.push_back(thread(contar_palabras, argv[i+1]));
    }

    for(auto & hilo : hilos)
        hilo.join();

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
