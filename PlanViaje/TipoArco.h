/**-------------------------------------------------------------
|   ARCHIVO: TipoArco.h                                         |
|---------------------------------------------------------------|
|   Contenido: declaración del TAD TipoArco y de los            |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
 
#ifndef __TIPOARCO_H__
#define __TIPOARCO_H__

#include "../TADsComunes/Tramo.h"

/**-------------------------------------------------------------
| Descripción: almacena los datos de un arco entre dos nodos    |
|                                                               |
| Atributos:                                                    |
| ID: identificador del tramo                                   |
| tramo: registro para el tramo                                 |
| peso: coste de utilizar este arco                             |
| dest: nodo destino del arco                                   |
--------------------------------------------------------------*/
struct sTipoArco {
        int ID; // numero de orden en la lista
        TipoTramo tramo; // registro para el tramo
        float peso; // coste de utilizar este arco
        int dest; // nodo destino del arco
};

typedef struct sTipoArco TipoArco;


#endif

/**-------------------------------------------------------------
|                 Fin del archivo Estacion.h                    |
 --------------------------------------------------------------*/
