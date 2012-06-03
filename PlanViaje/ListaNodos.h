/**-------------------------------------------------------------
|   ARCHIVO: ListaNodos.h                                       |
|---------------------------------------------------------------|
|   Contenido: declaraci�n del TAD ListaNodos y de los          |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
 
#ifndef __LISTANODOS_H__
#define __LISTANODOS_H__

#include "TipoNodo.h"
#define NODOS_BIN "../BaseDatos/Estaciones.dat"

/**-------------------------------------------------------------
| Descripci�n: almacena una lista de nodos                      |
|                                                               |
| Atributos:                                                    |
| num: numero de nodos almacenados                              |
| lista: vector para almacenar los datos de los nodos           |
--------------------------------------------------------------*/
struct sListaNodos {
        int numNodos;
        TipoNodo *nodo; /* Un array de nodos */
};

typedef struct sListaNodos ListaNodos;


/**-------------------------------------------------------------
|  Funciones asociadas al TAD ListaNodos                        |
 --------------------------------------------------------------*/
void cargarListaNodos(ListaNodos *nodos);


#endif


/**-------------------------------------------------------------
|                 Fin del archivo ListaNodos.h                  |
 --------------------------------------------------------------*/
