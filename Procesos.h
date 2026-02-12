#ifndef PROCESOS_H
#define PROCESOS_H

#include <string>

struct Proceso {
    int pid;
    std::string nombre;
    double memoriaMB;
    bool sospechoso;
    std::string razon;
    std::string nivelRiesgo;
};

Proceso* obtenerProcesos(int& cantidad);

#endif
