/**-------------------------------------------------------------
|   ARCHIVO: ListaArcos.h                                       |
|---------------------------------------------------------------|
|   Contenido: declaración del TAD ListaArcos y de los          |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
 
#ifndef __LISTAARCOS_H__
#define __LISTAARCOS_H__

#include "TipoArco.h"

/**-------------------------------------------------------------
| Descripción: almacena una lista de arcos (tramos)            |
|                                                              |
| Atributos:                                                   |
| num: numero de arcos almacenados                             |
| lista: vector para almacenar los arcos adyacentes            |
--------------------------------------------------------------*/
struct sListaArcos {
        int numArcos;
        TipoArco *arco; // Un array de arcos que SALEN del nodo 
};

typedef struct sListaArcos ListaArcos;


/**-------------------------------------------------------------
|  Funciones asociadas al TAD ListaArcos                        |
 --------------------------------------------------------------*/
void cargarListaTramos(ListaArcos *arcos, int opc);


#endif

/**-------------------------------------------------------------
|                 Fin del archivo ListaArcos.h                  |
 --------------------------------------------------------------*/
