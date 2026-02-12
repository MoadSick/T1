# Proyecto: Monitor de Procesos en C++

## Descripción general
Este proyecto implementa un monitor real de procesos del sistema en C++.
El programa obtiene la lista de procesos activos en Windows utilizando el comando del sistema tasklist, analiza cuáles podrían representar un riesgo según criterios definidos y registra los resultados en un archivo de texto estructurado.

## Integrantes del equipo
Marco Antonio Guadalupe Vargas Ruiz

## Instrucciones de compilacion y ejecucion 

### Requisitos
- Sistema operativo: Windows
- Compilador: g++ (MinGW) o MSVC
- Librerías utilizadas: Biblioteca estándar de C++ y comando del sistema tasklist

### Compilacion
Desde la consola, ubicarse en la carpeta del proyecto y ejecutar:
g++ main.cpp Procesos.cpp Analisis.cpp Registro.cpp -o MonitorProcesos.exe -static -static-libgcc -static-libstdc++

Ejecucion
MonitorProcesos.exe

### Entrada esperada
El programa solicita al usuario:
- Modo de análisis (1 = básico, 2 = estricto)
- Nombre del archivo de salida (sin extensión, el programa agrega automáticamente .txt)

Ejemplo:
Modo de análisis: 2
Nombre del archivo: reporte
Genera: reporte.txt

### Enfoque tecnico
Este proyecto utiliza el comando del sistema [tasklist /FO CSV] para obtener procesos reales activos en Windows.

La salida del comando se captura mediante _popen() y se procesa línea por línea para extraer:
- PID
- Nombre del proceso
- Uso de memoria

La información se almacena dinámicamente en un arreglo de estructuras Proceso utilizando memoria dinámica (new[] y delete[]).

El sistema está dividido en tres módulos principales:

- Procesos.cpp / Procesos.h → Obtención real de procesos del sistema
- Analisis.cpp / Analisis.h → Criterios de riesgo y clasificación
- Registro.cpp / Registro.h → Escritura en archivo y manejo de errores

### Criterios para procesos sospechosos
Los procesos se analizan según el modo seleccionado:

Modo 1 – Análisis básico
- Uso elevado de memoria (> 300 MB)
- Nombre potencialmente riesgoso (cmd.exe, powershell.exe, wscript.exe)

Modo 2 – Análisis estricto
- Uso elevado de memoria (> 150 MB)
- Nombre potencialmente riesgoso
- PID menor a 100 (posibles procesos sensibles del sistema)

Cada proceso marcado como sospechoso incluye:
- Razón por la que fue clasificado
- Nivel de riesgo asignado (Bajo, Medio o Alto)

### Salida generada
El archivo de salida incluye:
- Fecha y hora del análisis
- Total de procesos detectados
- Lista completa de procesos con:
 - PID
 - Nombre
 - Uso de memoria
 - Indicador de sospecha
- Lista detallada de procesos sospechosos con:
 - Razón
 - Nivel de riesgo asignado
