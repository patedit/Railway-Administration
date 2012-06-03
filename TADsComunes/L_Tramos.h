#ifndef __L_TRAMOS_H__
#define __L_TRAMOS_H__


#include "Tramo.h"
#include "Tren.h"


/**-------------------------------------------------------------
|  TAD:   sL_Tramos                                             |
|  Alias: L_Tramos                                               |
 ---------------------------------------------------------------
|  Descripción: almacena una lista de rutas                     |
|                                                               |
|                                                               |
|  Atributos:                                                   |
|     num: numero de rutas almacenadas                          |
|     lista: vector para almacenar los datos de las rutas       |
|                                                               |
|  Funciones asociadas: ver prototipos                          |
 --------------------------------------------------------------*/
struct sL_Tramos 
{
       int num; // numero de rutas
       TipoTramo *lista;  // puntero a lista de tramos
};
typedef struct sL_Tramos L_Tramos;



#endif
void imprimirTramos(Tren tren);
void mostrarTramo(Tren ID);
void eliminarUnTramo(Tren tren);
void mostrarTramoConID(Tren ID);

/**-------------------------------------------------------------
|                 Fin del archivo L_Tramos.h                    |
 --------------------------------------------------------------*/
