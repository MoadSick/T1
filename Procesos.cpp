#include "Procesos.h"
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cctype>

Proceso* obtenerProcesos(int& cantidad) {
    FILE* pipe = _popen("tasklist /FO CSV", "r");
    if (!pipe) {
        throw std::runtime_error("No se pudo ejecutar tasklist.");
    }

    std::vector<Proceso> temp;
    char buffer[1024];

    // Saltar encabezado
    fgets(buffer, sizeof(buffer), pipe);

    while (fgets(buffer, sizeof(buffer), pipe)) {
        std::string linea(buffer);
        std::stringstream ss(linea);
        std::string campo;

        Proceso p;
        p.sospechoso = false;

        // ===== NOMBRE =====
        getline(ss, campo, ',');
        if (campo.size() >= 2)
            p.nombre = campo.substr(1, campo.length() - 2);
        else
            p.nombre = campo;

        // ===== PID =====
        getline(ss, campo, ',');
        if (campo.size() >= 2)
            campo = campo.substr(1, campo.length() - 2);

        try {
            p.pid = std::stoi(campo);
        } catch (...) {
            p.pid = 0;
        }

        // Saltar sesión
        getline(ss, campo, ',');

        // Saltar número de sesión
        getline(ss, campo, ',');

        // ===== MEMORIA =====
        getline(ss, campo, ',');

        if (campo.size() >= 2)
            campo = campo.substr(1, campo.length() - 2);

        // Limpiar todo lo que no sea número
        std::string limpio;
        for (char c : campo) {
            if (std::isdigit(static_cast<unsigned char>(c)))
                limpio += c;
        }

        try {
            if (!limpio.empty())
                p.memoriaMB = std::stod(limpio) / 1024.0;
            else
                p.memoriaMB = 0.0;
        } catch (...) {
            p.memoriaMB = 0.0;
        }

        temp.push_back(p);
    }

    _pclose(pipe);

    cantidad = static_cast<int>(temp.size());

    // Memoria dinámica obligatoria
    Proceso* lista = new Proceso[cantidad];

    for (int i = 0; i < cantidad; ++i)
        lista[i] = temp[i];

    return lista;
}
