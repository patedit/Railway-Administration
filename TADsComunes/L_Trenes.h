/**-------------------------------------------------------------
|   ARCHIVO: L_Trenes.h                                         |
 ---------------------------------------------------------------
|   Contenido: declaración del TAD L_Trenes y de los            |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/

#ifndef __L_TRENES_H__
#define __L_TRENES_H__

#define MAX_TREN 40

#include "Tren.h"

/**-------------------------------------------------------------
|  TAD:   sL_Trenes                                             |
|  Alias: L_Trenes                                              |
 ---------------------------------------------------------------
|  Descripción: almacena una lista de trenes                    |
|                                                               |
| Constantes asociadas:                                         |
|     MAX_TREN: número máximo de trenes que se pueden           |
|              almacenar                                        |
|                                                               |
|  Atributos:                                                   |
|     num: numero de trenes almacenados                         |
|     lista: vector para almacenar los datos de los trenes      |
|                                                               |
|  Funciones asociadas: ver prototipos                          |
 --------------------------------------------------------------*/
struct sL_Trenes {
	int num;        // numero de trenes almacenadas 
	Tren *lista;  // puntero a lista de trenes
};

typedef struct sL_Trenes L_Trenes;

/**-------------------------------------------------------------
|  Funciones asociadas al TAD L_Trenes                          |
 --------------------------------------------------------------*/
void abrirArchivoTrenes(L_Trenes *Trenes);
void imprimirTrenes(void);
int  menuMantenimientoTrenes(void);
void mantenimientoTrenes(void);
void grabarArchivoTrenes(L_Trenes Trenes);
void eliminarTren(void);
void modificarUnTren();
void anadirUnTren(void);
void mostrarTodosTrenes(void); 


#endif

/**-------------------------------------------------------------
|                 Fin del archivo L_Trenes.h                    |
 --------------------------------------------------------------*/
 
 
