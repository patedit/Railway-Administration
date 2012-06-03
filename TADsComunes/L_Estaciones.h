/**-------------------------------------------------------------
|   ARCHIVO: L_Estaciones.h                                     |
 ---------------------------------------------------------------
|   Contenido: declaración del TAD L_Estaciones y de los        |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/

#ifndef __L_ESTACIONES_H__
#define __L_ESTACIONES_H__

#define MAX_EST 40

#include "Estacion.h"

/**-------------------------------------------------------------
|  TAD:   sL_Estaciones                                         |
|  Alias: L_Estaciones                                          |
 ---------------------------------------------------------------
|  Descripción: almacena una lista de estaciones                |
|                                                               |
| Constantes asociadas:                                         |
|     MAX_EST: número máximo de estaciones que se pueden        |
|              almacenar                                        |
|                                                               |
|  Atributos:                                                   |
|     num: numero de estaciones almacenadas                     |
|     lista: vector para almacenar los datos de las estaciones  |
|                                                               |
|  Funciones asociadas: ver prototipos                          |
 --------------------------------------------------------------*/
struct sL_Estaciones {
	int num;        // numero de estaciones almacenadas 
	Estacion *lista;  // puntero a lista de estaciones
};

typedef struct sL_Estaciones L_Estaciones;

/**-------------------------------------------------------------
|  Funciones asociadas al TAD L_Estaciones                      |
 --------------------------------------------------------------*/
void abrirArchivoEstaciones(L_Estaciones *Estaciones);
void imprimirEstaciones(void);
int  menuMantenimientoEstaciones(void);
void mantenimientoEstaciones(void);
void grabarArchivoEstaciones(L_Estaciones Estaciones);
void eliminarEstacion(void);
void modificarUnaEstacion();
void anadirUnaEstacion(void);
void mostrarTodasEstaciones(void);


#endif

/**-------------------------------------------------------------
|                 Fin del archivo L_Estaciones.h                |
 --------------------------------------------------------------*/
 
 
