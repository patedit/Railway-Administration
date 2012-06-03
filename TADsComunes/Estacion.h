/**-------------------------------------------------------------
|   ARCHIVO: Estacion.h                                         |
|---------------------------------------------------------------|
|   Contenido: declaración del TAD Estacion y de los            |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
#ifndef __ESTACION_H__
#define __ESTACION_H__

#include "PosGeo.h"

#define FMT_ESTACION	"%c%-5s %-25s %-24s %9.3lf %9.3lf %c\n"
#define FMT_ESTACIONX	"%c%-5s %-25s %-24s %9s %9s %c\n"
#define ESTACIONES_BIN "../BaseDatos/Estaciones.dat"
#define ESTACIONES_TXT "../BaseDatos/Estaciones.txt"

/**-------------------------------------------------------------
|  TAD:   sEstacion                                             |
|  Alias: Estacion                                              |
|---------------------------------------------------------------|
|  Descripción: almacena los datos de una estación de tren      |
|                                                               |
| Constantes asociadas:                                         |
|     FMT_ESTACION: formato de impresión en pantalla            |
|     FMT_ESTACIONX: formato de cabecera de impresión  pantalla |
|     ESTACIONES_BIN: nombre del archivo binario de estaciones  |
|     ESTACIONES_TXT: nombre del archivo de texto de estaciones |
|                                                               |
|  Atributos:                                                   |
|     ID: código de identificación de la estación               |
|     nombre: nombre de la estación                             |
|     localidad: localidad donde se encuentra la estación       |
|     pos: coordenadas de la estacion en grados decimales       |
|                                                               |
|  Funciones asociadas: ver prototipos                          |
|--------------------------------------------------------------*/
struct sEstacion {
	char ID[10];         // identificador
	char nombre[100];    // nombre de la estacion
	char localidad[100]; // poblacion donde esta la estacion
	PosGeo pos;          // Coordenadas de la estacion en grados decimales
};

typedef struct sEstacion Estacion;

/**-------------------------------------------------------------
|  Funciones asociadas al TAD Estacion                          |
 --------------------------------------------------------------*/
void mostrarEstacion(Estacion estacion);
void validarEstacion(char *ID);
void modificarEstacion(Estacion *estacion);
void anadirEstacion(Estacion *estacion);

#endif

/**-------------------------------------------------------------
|                 Fin del archivo Estacion.h                    |
 --------------------------------------------------------------*/
 
