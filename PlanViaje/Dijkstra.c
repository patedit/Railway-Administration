/**------------------------------------------------------------- 
|   ARCHIVO: Dijkstra.c                                         |
|---------------------------------------------------------------|
|   Contenido: Algoritmo de Dijkstra para el calculo de ruta    |
|               mas barata, mas rapida y mas corta              |
 --------------------------------------------------------------*/
 
#define INFINITY 9999 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TipoGrafo.h"

/**-------------------------------------------------------------
|  Funcion: mainDijkstra                                        |
|---------------------------------------------------------------|
|  Descripción: Pide informacion del trayecto y comprueba que   |
|           la informacion este bien, mostrando por pantalla    |
|           la estacion correspondiente.                        |
|  Entradas: registro TipoGrafo, ListaArcos y la opcion (1,2,3) |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
 
void mainDijkstra(TipoGrafo *Grafo, ListaArcos arcos, int opc)
{
     int destino,n,source,a,b,var;
     char IDorigen[10];
     char IDdestino[10];
     
     // Pide el ID origen hasta que el ID origen exista, previa comprobacion con validarEstacionViaje 
     do {
        printf("Introduce ID origen: "); gets(IDorigen);
        a = validarEstacionViaje(IDorigen);
     } while (a!=-1);
     
     //Busca el nodo cuya estacion sea la de IDorigen para luego devolver la informacion
     for(n=0;n<Grafo->nodos.numNodos;n++)
     {
                if(strcmp(IDorigen, Grafo->nodos.nodo[n].estacion.ID) ==0) var=n;
     }
     
     // Imprime en una tabla la estacion seleccionada
     comienzoTabla();
     mostrarUnaEstacion(Grafo->nodos.nodo[var].estacion); 
     finTabla();
     fflush(stdin);
     
     // Pide el ID destino hasta que el ID destino exista, previa comproacion con validarEstacionViaje
     do {
        printf("Introduce ID destino: "); gets(IDdestino);
        if(strcmp(IDorigen, IDdestino) ==0)
        {
                          printf("No puede ser el mismo ID que el de origen\n"); // En el caso de que IDorigen e IDdestino sean el mismo
                          b=0; 
        }
        else b = validarEstacionViaje(IDdestino);
     } while (b!=-1);
     
     // Busca la estacion para imprimirla por pantalla
     for(n=0;n<Grafo->nodos.numNodos;n++)
     {
             if(strcmp(IDdestino, Grafo->nodos.nodo[n].estacion.ID) ==0) var=n;
     }
     
     comienzoTabla();
     mostrarUnaEstacion(Grafo->nodos.nodo[var].estacion); 
     finTabla();
     fflush(stdin); getchar();
     
     // Iguala source y destino con la estacion origen y destino que le hemos dado, para pasarla a Dijsktra luego           
     for(n=0;n<Grafo->nodos.numNodos;n++)
     {
             if(strcmp(Grafo->nodos.nodo[n].estacion.ID, IDorigen) ==0)
             {
                      source = n;
             }
             if(strcmp(Grafo->nodos.nodo[n].estacion.ID, IDdestino) ==0)
             {
                      destino = n;
             }
     }
     Dijkstra(Grafo, source, destino, arcos, opc);
}


/**-------------------------------------------------------------
|  Funcion: Dijkstra                                            |
|---------------------------------------------------------------|
|  Descripción: Pide informacion del trayecto y comprueba que   |
|           la informacion este bien, mostrando por pantalla    |
|           la estacion correspondiente.                        |
|  Entradas: registro TipoGrafo, un origen, un destino,         |
|            ListaArcos y la opcion (1,2,3)                     |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
 
void Dijkstra(TipoGrafo *Grafo, int source, int destino, ListaArcos Arcos, int opc) 
{
     int i,n;

     int nodecount = Grafo->nodos.numNodos; // nodecount = numero de nodos que hay

     // Inicializa la distancia de todos los nodos a INFINITO, y si es el nodo origen a CERO. isDead = 0 siempre
     for(i=0; i<nodecount; i++) 
     {  
             if(i == source) 
             {
                  Grafo->nodos.nodo[i].distancia = 0;
                  Grafo->nodos.nodo[i].isDead = 0;
             } 
             else 
             {
                  Grafo->nodos.nodo[i].distancia = INFINITY;
                  Grafo->nodos.nodo[i].isDead = 0;
             }
     }
     
     // Tantas veces como nodos haya
     for(i=0; i<nodecount; i++) 
     {
             int next,j;
             int min = INFINITY+1;
             
             for(j=0; j<nodecount; j++) 
             {
                      // Siempre que el nodo no haya sido analizado y la ditancia sea menor que min
                     if(!Grafo->nodos.nodo[j].isDead && Grafo->nodos.nodo[j].distancia < min) 
                     {
                                         next = j;
                                         min = Grafo->nodos.nodo[j].distancia; // cuando salgamos del bucle por primera vez, min valdrá 0 puesto que es la minima distancia (source), por lo tanto, next valdra source 
                     }
             }

             for(j=0; j<Grafo->nodos.nodo[next].arcos.numArcos;j++) 
             {
                     // La distancia del destino del arco que sale del nodo next
                     if(Grafo->nodos.nodo[Grafo->nodos.nodo[next].arcos.arco[j].dest].distancia > Grafo->nodos.nodo[next].distancia + Grafo->nodos.nodo[next].arcos.arco[j].peso)
                     {
                                         Grafo->nodos.nodo[Grafo->nodos.nodo[next].arcos.arco[j].dest].distancia = Grafo->nodos.nodo[next].distancia + Grafo->nodos.nodo[next].arcos.arco[j].peso; // La distancia sera el peso + distancia
                                         Grafo->nodos.nodo[Grafo->nodos.nodo[next].arcos.arco[j].dest].nodo_prec=next; // El nodo precedente al destino de un tramo que sale de un nodo, sera siermpe ese nodo.
                                         Grafo->nodos.nodo[Grafo->nodos.nodo[next].arcos.arco[j].dest].arc_prec=Grafo->nodos.nodo[next].arcos.arco[j].ID; // El arco_prec de un destino, sera el ID de ese arco que llega a ese destino
                     }
             }        
             Grafo->nodos.nodo[next].isDead = 1; // el nodo ha sido ya analizado isDead=1
     }

     // Dependiendo de la opcion seleccionada, nos muestra la ruta mas corta, rapida o barata
     if (opc == 1) mostrarRutaDuracion(Grafo, source, destino, Arcos);
     if (opc == 2) mostrarRutaDistancia(Grafo, source, destino, Arcos);
     if (opc == 3) mostrarRutaPrecio(Grafo, source, destino, Arcos);
}


/**-------------------------------------------------------------
|                 Fin del archivo Dijkstra.c                    |
 --------------------------------------------------------------*/

