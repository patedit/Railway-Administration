/**-------------------------------------------------------------
|   ARCHIVO: Tren.h                                             |
|---------------------------------------------------------------|
|   Contenido: declaración del TAD Tren y de los                |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
#ifndef __TREN_H__
#define __TREN_H__


#include "Hora.h"

#define FMT_TREN	"%c%-5s %-15s %-10s %-6s %-8s %02d:%02d     %02d:%02d %12.2f%c\n"
#define FMT_TRENX	"%c%-5s %-15s %-10s %-6s %-8s %-9s %-9s%8s%c\n"
#define TRENES_BIN "../BaseDatos/Trenes.dat"
#define TRENES_TXT "../BaseDatos/Trenes.txt"

/**-------------------------------------------------------------
|  TAD:   sTren                                                 |
|  Alias: Tren                                                  |
|---------------------------------------------------------------|
|  Descripción: almacena los datos de un tren                   |
|                                                               |
| Constantes asociadas:                                         |
|     FMT_TREN: formato de impresión en pantalla                |
|     FMT_TRENX: formato de cabecera de impresión  pantalla     |
|     TRENES_BIN: nombre del archivo binario de trenes          |
|     TRENES_TXT: nombre del archivo de texto de trenes         |
|                                                               |
|  Atributos:                                                   |
|     ID: código de identificación del tren                     |
|     nombre: nombre del tren                                   |
|     tipo: tipo de tren:TALGO, ESTRELLA...                     |
|     origen: codigo de la estacion de origen                   |
|     destino: codigo de la estacion de destino                 |
|     salida: hora de la salida <hh:mm>                         |
|     llegada: hora de la llegada <hh:mm>                       |
|     precio: precio total del trayecto                         |
|                                                               |
|  Funciones asociadas: ver prototipos                          |
|--------------------------------------------------------------*/
struct sTren {
	char ID[10];                 // codigo de identificacion
	char nombre[40];             // nombre del tren
	char tipo[40];               // tipo de tren: TALGO, ESTRELLA...
    char origen[10];             // codigo de la estacion de origen
    char destino[10];            // codigo de la estacion de destino
    Hora salida;                 // TAD Hora->salida
    Hora llegada;                // TAD Hora->llegada
    float precio;                // precio total recorrido tren
};

typedef struct sTren Tren;


/**-------------------------------------------------------------
|  Funciones asociadas al TAD Tren                              |
 --------------------------------------------------------------*/



#endif

/**-------------------------------------------------------------
|                 Fin del archivo Tren.h                        |
 --------------------------------------------------------------*/
 
