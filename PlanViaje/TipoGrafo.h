/**-------------------------------------------------------------
|   ARCHIVO: TipoGrafo.h                                        |
|---------------------------------------------------------------|
|   Contenido: declaración del TAD TipoGrafo y de los           |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
 
#ifndef __TIPOGRAFO_H__
#define __TIPOGRAFO_H__

#include "ListaNodos.h"

/**-------------------------------------------------------------
| Descripción: almacena los datos de un grafo                  |
|                                                              |
| Atributos:                                                   |
| nodos: lista de nodos del grafo                              |
--------------------------------------------------------------*/
struct sTipoGrafo {
        ListaNodos nodos;
};

typedef struct sTipoGrafo TipoGrafo;


/**-------------------------------------------------------------
|  Funciones asociadas al TAD TipoGrafo                         |
 --------------------------------------------------------------*/
void mainCrearGrafo(int opc);
void crearGrafo(ListaNodos nodos, ListaArcos arcos, TipoGrafo *Grafo);
void mainDijkstra(TipoGrafo *Grafo, ListaArcos arcos, int opc);
void Dijkstra(TipoGrafo *Grafo, int source, int destino, ListaArcos Arcos, int opc);
void mostrarRutaDuracion(TipoGrafo *Grafo, int source, int destino, ListaArcos Arcos);
void mostrarRutaDistancia(TipoGrafo *Grafo, int source, int destino, ListaArcos Arcos);
void mostrarRutaPrecio(TipoGrafo *Grafo, int source, int destino, ListaArcos Arcos);
void funcionAmpliacion(int opc);
void muestraEstacionesCercanas(TipoGrafo grafo, int ID_origen);

#endif

/**-------------------------------------------------------------
|                 Fin del archivo TipoGrafo.h                   |
 --------------------------------------------------------------*/
