#include "Registro.h"
#include <fstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>

// ===== Función para obtener fecha y hora actual =====
static std::string fechaHora() {
    std::time_t t = std::time(nullptr);
    std::tm* tmv = std::localtime(&t);
    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tmv);
    return std::string(buffer);
}

// ===== Función principal de guardado =====
void guardarResultados(const std::string& archivo,
                       const Proceso* lista,
                       int cantidad,
                       int modo) {

    std::ofstream out(archivo);

    if (!out.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de salida.");
    }

    // ===== ENCABEZADO =====
    out << "===========================================\n";
    out << "        MONITOR DE PROCESOS C++\n";
    out << "===========================================\n";
    out << "Fecha y hora: " << fechaHora() << "\n";
    out << "Modo de analisis: " 
        << (modo == 1 ? "Basico" : "Estricto") << "\n";
    out << "Total de procesos detectados: " << cantidad << "\n\n";

    // ===== LISTA COMPLETA =====
    out << "========== LISTA COMPLETA ==========\n\n";

    out << std::left
        << std::setw(8)  << "PID"
        << std::setw(25) << "NOMBRE"
        << std::setw(12) << "MEMORIA(MB)"
        << std::setw(12) << "SOSPECHOSO"
        << "\n";

    out << "---------------------------------------------------------------\n";

    for (int i = 0; i < cantidad; ++i) {
        out << std::setw(8)  << lista[i].pid
            << std::setw(25) << lista[i].nombre
            << std::setw(12) << std::fixed << std::setprecision(2)
            << lista[i].memoriaMB
            << std::setw(12)
            << (lista[i].sospechoso ? "SI" : "NO")
            << "\n";
    }

    // ===== PROCESOS SOSPECHOSOS =====
    out << "\n\n========== PROCESOS SOSPECHOSOS ==========\n\n";

    bool alguno = false;
    int totalSospechosos = 0;

    for (int i = 0; i < cantidad; ++i) {

        if (!lista[i].sospechoso)
            continue;

        alguno = true;
        totalSospechosos++;

        out << "PID: " << lista[i].pid << "\n";
        out << "Nombre: " << lista[i].nombre << "\n";
        out << "Memoria: " << std::fixed << std::setprecision(2)
            << lista[i].memoriaMB << " MB\n";
        out << "Razon: " << lista[i].razon << "\n";
        out << "Nivel de riesgo: " << lista[i].nivelRiesgo << "\n";
        out << "-------------------------------------------\n";
    }

    if (!alguno) {
        out << "No se detectaron procesos sospechosos.\n";
    }

    out << "\nTotal de procesos sospechosos: "
        << totalSospechosos << "\n";

    out.close();
}
