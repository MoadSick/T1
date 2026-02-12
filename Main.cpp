#include <iostream>
#include "Procesos.h"
#include "Analisis.h"
#include "Registro.h"

int main() {
    try {
        int modo;
        std::cout << "Modo de Analisis (1 = Basico, 2 = Estricto): ";
        std::cin >> modo;

        if (modo != 1 && modo != 2)
            throw std::invalid_argument("Modo invalido.");

        std::string archivo;
        std::cout << "Archivo de salida (sin extension): ";
        std::cin >> archivo;

        // Agregar .txt automaticamente
        if (archivo.find(".txt") == std::string::npos) {
            archivo += ".txt";
        }

        int cantidad;
        Proceso* lista = obtenerProcesos(cantidad);

        marcarSospechosos(lista, cantidad, modo);

        for (int i = 0; i < cantidad; ++i) {
            std::cout << lista[i].pid << " "
                      << lista[i].nombre << " "
                      << lista[i].memoriaMB << "MB "
                      << (lista[i].sospechoso ? "[Sospechoso]" : "")
                      << "\n";
        }

        guardarResultados(archivo, lista, cantidad, modo);

        delete[] lista;

        std::cout << "\nAnalisis completado.\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
