/**-------------------------------------------------------------
|   ARCHIVO: Tramo.h                                            |
|---------------------------------------------------------------|
|   Contenido: declaración del TAD Tramo y de los               |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
#ifndef __TRAMO_H__
#define __TRAMO_H__

#define FMT_TRAMOX2	"%c%-6s%-25s%-25s%-8s%-7s%s%c\n"
#define FMT_TRAMO2	"%c%-6s%-25s%-25s%02d:%02d   %02d:%02d  %5.2f %c\n"

#define FMT_TRAMO	"%c%-5s %-25s %-25s %02d:%02d       %02d:%02d    %-13d %-10.2f %8.2f %c\n"
#define FMT_TRAMOX	"%c%-5s %-25s %-25s %-11s %-8s %-13s %-12s %8s%c\n"
#include "Hora.h"
/**-------------------------------------------------------------
|  TAD:   sTramo                                                |
|  Alias: Tramo                                                 |
|---------------------------------------------------------------|
|  Descripción: almacena los datos de la ruta                   |
|                                                               |
| Constantes asociadas:                                         |
|     FMT_TRAMO: formato de impresión en pantalla               |
|     FMT_TRAMOX: formato de cabecera de impresión  pantalla    |
|                                                               |
|  Atributos:                                                   |
|     ID: código de identificación de etapa                     |
|     IDorigen: identificacion estacion de origen               |
|     IDdestino: identificacion estacion destino                |
|     inicio: hora de inicio de la etapa                        |
|     fin: hora de fin de la etapa                              |
|     precio: precio de la etapa                                |
|     distancia: kilometros de la etapa                         |
|     duracion: duracion en minutos de la etapa                 |
|     tramos: tramos de la ruta                                 |
|                                                               |
|--------------------------------------------------------------*/
struct sTramo {
    char ID[10];
	char IDorigen[10];           // identificacion estacion de origen
	char IDdestino[10];          // identificacion estacion de destino
	Hora inicio;                 // hora de inicio del tramo
	Hora fin;                    // hora de fin del tramo
	float precio;                // precio del tramo
	float distancia;             // kilometros del tramo
	int duracion;                // duracion en minutos del tramo    
};
typedef struct sTramo TipoTramo;

#endif
/**-------------------------------------------------------------
|                 Fin del archivo Tramo.h                       |
 --------------------------------------------------------------*/
