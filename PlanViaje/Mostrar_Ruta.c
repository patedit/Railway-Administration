/**------------------------------------------------------------- 
|   ARCHIVO: Mostrar_Ruta.c                                     |
|---------------------------------------------------------------|
|   Contenido: Muestra la ruta seleccionada por Dijkstra        |
 --------------------------------------------------------------*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TipoGrafo.h"

/**-------------------------------------------------------------
|  Funcion: mostrarRutaDuracion                                 |
|---------------------------------------------------------------|
|  Descripción: Muestra la ruta mas rapida                      |
|  Entradas: registro TipoGrafo, ListaArcos y un orig. y dest.  |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void mostrarRutaDuracion(TipoGrafo *Grafo, int source, int destino, ListaArcos Arcos)
{

     int i, n, numTramos=0,durEspera=0;
     float precioTotal=0,distanciaTotal=0;
     int *vector;
     
     i=destino;
     
     // Calculamos el numero de tramos que hay desde el origen hasta el destino
     while(i!=source)
     {
         numTramos++;
         i=Grafo->nodos.nodo[i].nodo_prec;
     }

     // Creamos un vector de tamaño el numero de tramos que hay para esa ruta nueva
     vector = calloc(sizeof(vector), numTramos);
     
     n=destino;
     i=0;
     
     // Rellenamos el vector[i] con el arco precedente de cada nodo
     while(n!=source)
     {
         vector[i]=Grafo->nodos.nodo[n].arc_prec;
         n=Grafo->nodos.nodo[n].nodo_prec;
         i++;
     }
     system("cls"); // Nueva pantalla
   	 printf("\n\n");
     cabeceraTabla("Ruta mas rapida");
     comienzoTabla();
     // Mostramos cada tramo, para ello tendremos que empezar por el ultimo tramo (primero) y acabar por el primero (ultimo)
     for(i=numTramos-1;i>=0;i--)
     {
         mostrarUnTramo(Arcos.arco[vector[i]].tramo); 
         precioTotal = Arcos.arco[vector[i]].tramo.precio + precioTotal; // Calculamos el precio total del trayecto
         distanciaTotal = Arcos.arco[vector[i]].tramo.distancia + distanciaTotal; // Calculamos la duracion total del trayecto
     }
     finTabla();
     fflush(stdin);
     
     durEspera = calcularDuracionEspera(Grafo,Arcos,source,destino); // Llamamos a la funcion para calcular la duracion de la espera
      
     printf("\n\nCaracteristicas de la ruta mas rapida entre %s y %s:\n", Grafo->nodos.nodo[source].estacion.nombre, Grafo->nodos.nodo[destino].estacion.nombre);
     printf("\t-> DURACION TRAYECTO: %.0f minutos\n", Grafo->nodos.nodo[destino].distancia);
     printf("\t-> DURACION ESPERA: %d minutos", durEspera);
     if(durEspera > 2*(Grafo->nodos.nodo[destino].distancia)) printf("  [CUIDADO] Demasiado tiempo de espera");
     printf("\n\t-> Paradas: %d\n", numTramos);
     printf("\t-> Distancia: %.2f kilometros\n", distanciaTotal);
     printf("\t-> Precio: %.2f Euros\n", precioTotal); 
     Pausa();
}


/**-------------------------------------------------------------
|  Funcion: mostrarRutaDistancia                                |
|---------------------------------------------------------------|
|  Descripción: Muestra la ruta mas corta                       |
|  Entradas: registro TipoGrafo, ListaArcos y un orig. y dest.  |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void mostrarRutaDistancia(TipoGrafo *Grafo, int source, int destino, ListaArcos Arcos)
{
     int i, n, numTramos=0,durEspera=0,duracionTotal=0;
     float precioTotal=0,distanciaTotal=0;
     int *vector;
     
     i=destino;
     
     // Calculamos el numero de tramos que hay desde el origen hasta el destino
     while(i!=source)
     {
         numTramos++;
         i=Grafo->nodos.nodo[i].nodo_prec;
     }

     // Creamos un vector de tamaño el numero de tramos que hay para esa ruta nueva
     vector = calloc(sizeof(vector), numTramos);
     
     n=destino;
     i=0;
     
     // Rellenamos el vector[i] con el arco precedente de cada nodo
     while(n!=source)
     {
         vector[i]=Grafo->nodos.nodo[n].arc_prec;
         n=Grafo->nodos.nodo[n].nodo_prec;
         i++;
     }
     system("cls"); // Nueva pantalla
   	 printf("\n\n");
     cabeceraTabla("Ruta mas corta");
     comienzoTabla();
     // Mostramos cada tramo, para ello tendremos que empezar por el ultimo tramo (primero) y acabar por el primero (ultimo)
     for(i=numTramos-1;i>=0;i--)
     {
         mostrarUnTramo(Arcos.arco[vector[i]].tramo); 
         precioTotal = Arcos.arco[vector[i]].tramo.precio + precioTotal; // Calculamos el precio total del trayecto
         duracionTotal = Arcos.arco[vector[i]].tramo.duracion + duracionTotal; // Calculamos la duracion total del trayecto
     }
     finTabla();
     fflush(stdin);
     
     durEspera = calcularDuracionEspera(Grafo,Arcos,source,destino); // Llamamos a la funcion para calcular la duracion de la espera

     printf("\n\nCaracteristicas de la ruta minima entre %s y %s:\n", Grafo->nodos.nodo[source].estacion.nombre, Grafo->nodos.nodo[destino].estacion.nombre);
     
     printf("\t-> DISTANCIA: %.2f kilometros\n", Grafo->nodos.nodo[destino].distancia);
     printf("\t-> Paradas: %d\n", numTramos);
     printf("\t-> Tiempo trayecto: %d minutos\n", duracionTotal);
     printf("\t-> Tiempo espera: %d minutos", durEspera);
     if(durEspera > 2*(duracionTotal)) printf("  [CUIDADO!!] Demasiado tiempo de espera");
     printf("\n\t-> Precio: %.2f Euros\n", precioTotal); 
     Pausa();
}


/**-------------------------------------------------------------
|  Funcion: mostrarRutaPrecio                                   |
|---------------------------------------------------------------|
|  Descripción: Muestra la ruta mas barata                      |
|  Entradas: registro TipoGrafo, ListaArcos y un orig. y dest.  |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void mostrarRutaPrecio(TipoGrafo *Grafo, int source, int destino, ListaArcos Arcos)
{
     int i, n, numTramos=0, durTotal=0, durEspera=0;
     float distanciaTotal=0;
     int *vector;

     i=destino;
     
     // Calculamos el numero de tramos que hay desde el origen hasta el destino
     while(i!=source)
     {
         numTramos++;
         i=Grafo->nodos.nodo[i].nodo_prec;
     }
     
     // Creamos un vector de tamaño el numero de tramos que hay para esa ruta nueva
     vector = calloc(sizeof(vector), numTramos);
     
     n=destino;
     i=0;
     
     // Rellenamos el vector[i] con el arco precedente de cada nodo
     while(n!=source)
     {
         vector[i]=Grafo->nodos.nodo[n].arc_prec;
         n=Grafo->nodos.nodo[n].nodo_prec;
         i++;
     }
     system("cls"); // Nueva pantalla
     printf("\n\n");
     cabeceraTabla("Ruta mas economica");
     comienzoTabla();
     
     // Mostramos cada tramo, para ello tendremos que empezar por el ultimo tramo (primero) y acabar por el primero (ultimo)
     for(i=numTramos-1;i>=0;i--)
     {
         mostrarUnTramo(Arcos.arco[vector[i]].tramo); 
         distanciaTotal = Arcos.arco[vector[i]].tramo.distancia + distanciaTotal; // Calculamos la distancia total del trayecto
         durTotal = Arcos.arco[vector[i]].tramo.duracion + durTotal; // Calculamos la duracion total del trayecto
     }
     
     finTabla();
     fflush(stdin);
     
     durEspera = calcularDuracionEspera(Grafo,Arcos,source,destino); // Llamamos a la funcion para calcular la duracion de la espera
     printf("\n\nCaracteristicas de la ruta mas economica entre %s y %s:\n", Grafo->nodos.nodo[source].estacion.nombre, Grafo->nodos.nodo[destino].estacion.nombre);
     
     printf("\t-> PRECIO: %.2f Euros\n", Grafo->nodos.nodo[destino].distancia);
     printf("\t-> Paradas: %d\n", numTramos);
     printf("\t-> Distancia: %.2f kilometros\n", distanciaTotal);
     printf("\t-> Tiempo trayecto: %d minutos\n", durTotal);
     printf("\t-> Tiempo espera: %d minutos", durEspera);
     if(durEspera > 2*(durTotal)) printf("  [CUIDADO!!] Demasiado tiempo de espera\n"); 
     Pausa();
}

/**-------------------------------------------------------------
|                 Fin del archivo Mostrar_Ruta.c                |
 --------------------------------------------------------------*/
