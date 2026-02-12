#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include "Procesos.h"

void guardarResultados(const std::string& archivo,
                       const Proceso* lista,
                       int cantidad,
                       int modo);

#endif
