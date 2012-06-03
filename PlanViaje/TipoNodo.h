/**-------------------------------------------------------------
|   ARCHIVO: TipoNodo.h                                         |
|---------------------------------------------------------------|
|   Contenido: declaraci�n del TAD TipoNodo y de los            |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/

#ifndef __TIPONODO_H__
#define __TIPONODO_H__

#include "../TADsComunes/Estacion.h"
#include "ListaArcos.h"

/**-------------------------------------------------------------
| Descripci�n: almacena los datos de un nodo                    |
|                                                               |
| Atributos:                                                    |
| ID: identificador del nodo                                    |
| estacion: registro para datos de la estacion asociada         |
| arcos: lista de arcos adyacentes                              |
| coste: coste de la ruta hasta el nodo origen                  |
| isDead: indica si el nodo ya ha sido analizado                |
| nodo_prec: nodo precedente en la ruta �ptima                  |
| arc_prec: arco al nodo precedente                             |
---------------------------------------------------------------*/

struct sTipoNodo {
        int ID;
        Estacion estacion; // registro para datos del nodo
        ListaArcos arcos;
        float distancia;
        int isDead; // indica si el nodo ya ha sido analizado
        int nodo_prec; // nodo precedente en la ruta m�nima
        int arc_prec; // arco al nodo precedente
};

typedef struct sTipoNodo TipoNodo;

#endif


/**-------------------------------------------------------------
|                 Fin del archivo TipoNodo.h                    |
 --------------------------------------------------------------*/
