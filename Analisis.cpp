#include "Analisis.h"
#include <unordered_set>

static const std::unordered_set<std::string> nombresRiesgo = {
    "cmd.exe",
    "powershell.exe",
    "wscript.exe"
};

void marcarSospechosos(Proceso* lista, int cantidad, int modo) {

    for (int i = 0; i < cantidad; ++i) {

        lista[i].sospechoso = false;
        lista[i].razon = "";
        lista[i].nivelRiesgo = "Bajo";

        bool altoConsumo = lista[i].memoriaMB > (modo == 1 ? 300 : 150);
        bool nombreRiesgoso = nombresRiesgo.count(lista[i].nombre) > 0;
        bool pidBajo = lista[i].pid < 100;

        if (altoConsumo) {
            lista[i].sospechoso = true;
            lista[i].razon = "Uso elevado de memoria";
            lista[i].nivelRiesgo = (modo == 1) ? "Medio" : "Alto";
        }

        if (nombreRiesgoso) {
            lista[i].sospechoso = true;
            lista[i].razon = "Proceso con nombre potencialmente riesgoso";
            lista[i].nivelRiesgo = "Alto";
        }

        if (modo == 2 && pidBajo) {
            lista[i].sospechoso = true;
            lista[i].razon = "PID muy bajo (posible proceso del sistema)";
            lista[i].nivelRiesgo = "Medio";
        }
    }
}
