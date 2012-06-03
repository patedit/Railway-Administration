/**------------------------------------------------------------- 
|   ARCHIVO: ampliacion.c                                       |
|   AUTOR: Sergio Alonso Fernández. fp063                       |
|---------------------------------------------------------------|
|   Contenido: Archivo con la ampliacion del dia 24/01/08       |
 --------------------------------------------------------------*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../TADsComunes/L_Estaciones.h"
#include "../TADsComunes/L_Tramos.h"
#include "../TADsComunes/L_Trenes.h"

#include "TipoGrafo.h"

/**-------------------------------------------------------------
|  Funcion: funcionAmpliacion                                   |
 ---------------------------------------------------------------
|  Descripción: Carga Nodos, carga Arcos, Crea grafos, pide     |
|           un ID y muestra las estaciones cercanas             |
|                                                               |
|  Entradas: La opcion del menu correspondiente                 |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
 
void funcionAmpliacion(int opc)
{     
     int ID;
     ListaNodos nodos;
     ListaArcos arcos;
     TipoGrafo Grafo;

     cargarListaNodos(&nodos);
     cargarListaTramos(&arcos, opc);
     crearGrafo(nodos, arcos, &Grafo);

     printf("Introduce el ID del nodo: "); scanf("%d", &ID);
     // En el caso de que el numero no exista
     if(ID>nodos.numNodos)
     {
        printf("ERROR. El numero debe estar comprendido entre 0 y %d\n", nodos.numNodos); 
        Pausa(); 
        getchar();
        exit(0);
     }
     
     muestraEstacionesCercanas(Grafo, ID);

}


/**-------------------------------------------------------------
|  Funcion: muestraEstacionesCercanas                           |
 ---------------------------------------------------------------
|  Descripción: Abre el archivo binario de estaciones y lo carga| 
|               en memoria en la dirección pasada como parámetro|
|                                                               |
|  Entradas: registro TipoGrafo e ID de origen del nodo         |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void muestraEstacionesCercanas(TipoGrafo grafo, int ID_origen)
{
     int z,numArcos,n,encontrado,i,numEst;
     int tramosTotales = 1; // Va a ver un tramo por lo menos, es util inicializarlo a 1 para que luego empiece a contar desde 1 y no 0 para que compare con los anteriores...
     int *vector;
     int nomEst,nomEst1;
     int min,minN;
     char archivo[50];
     
     FILE *ptr;
     L_Estaciones estaciones;

     sprintf(archivo, "../PlanViaje/Destinos/%d.destinos", ID_origen);
     // Abrimos el archivo
     ptr = fopen(archivo, "w");

     //Llamos numEst al IDorigen
     numEst=ID_origen;
     
     //Calculamos los arcos que salen de ese nodo
     numArcos = grafo.nodos.nodo[numEst].arcos.numArcos;
     
     // Vamos a contar UNICAMENTE cuantos tramos salen de ese nodo (tramos UNICOS.. no numArcos)
     for(n=1; n<numArcos; n++)
     {
              encontrado = 0;
              i = 1;
              while(i<=n  && !encontrado)
              {
                       // En el caso de que ese nodo ya hubiera sido analizado, se compara con los anteriores para ver si son el mismo
                       if(grafo.nodos.nodo[numEst].arcos.arco[n].dest == grafo.nodos.nodo[numEst].arcos.arco[n-i].dest) encontrado = 1;
                       else i++;
              }
              if(encontrado == 0) tramosTotales++; // Si es la primera vez que "ve" el nodo, suma 1 a los tramos totales UNICOS del nodo
     }
     
     // Creamos un vector de tamaño los tramos totales que salen del nodo ID_origen
     vector = calloc(sizeof(vector), tramosTotales);
     // El primer elemento del vector, es el primer elemento de la lista --> 0
     // Hacemos esto porque la lista comienza en el 1, y hay que tener en cuenta el 0 también
     vector[0] = 0;
     
     // Comenzamos a contar en vector[1]
     z = 1;
     // Vamos a copiar en el vector, los nodos que nos interesan
     for(n=1; n<numArcos; n++)
     {
              encontrado = 0;
              i = 1;
              while(i<=n  && !encontrado)
              {
                       // Si el destino de ese arco es igual a otro cualquiera, ese destino no cuenta como destino UNICO
                       if(grafo.nodos.nodo[numEst].arcos.arco[n].dest == grafo.nodos.nodo[numEst].arcos.arco[n-i].dest) encontrado = 1;
                       else i++;
              }
              if(encontrado == 0) // No lo ha encontrado
              {
                            vector[z] = n; // Copiamos n en cada elemento del vector
                            z++;
              }
     }
     // Imprimimos con cuantas estanciones esta conectado el nodo
     fprintf(ptr, "%s %s %s %d %s", "La estacion", grafo.nodos.nodo[numEst].estacion.nombre, "esta conectado con",tramosTotales,"estaciones");
     
     // Abrimos el archivo de estaciones para mostrar el nombre de las estaciones a partir de ahora
     abrirArchivoEstacionesSinNumero(&estaciones);
     for(i=0; i<tramosTotales;i++)
     {
              // Comprobamos el nombre con una funcion auxiliar creada en el prototipo 1
              nomEst = comprobarNombre(grafo.nodos.nodo[numEst].arcos.arco[vector[i]].tramo.IDdestino);
              
              // Imprimimos el nombre de la estacion
              fprintf(ptr, "\n\n%s %s\n", "Estacion: ",  estaciones.lista[nomEst].nombre);     
              min = grafo.nodos.nodo[numEst].arcos.arco[vector[i]].tramo.duracion; // Suponemos como 'min' la duracion del tramo de vector[i]
              minN = vector[i];
              
              for(n=0; n<numArcos; n++)
              {
                       if(grafo.nodos.nodo[numEst].arcos.arco[vector[i]].dest == grafo.nodos.nodo[numEst].arcos.arco[n].dest)
                       {
                       // Imprimos la informacion del tramo
                       // Hay que mencionar que ya hay una funcion mostrarTramo, pero nos muestra la ID no el nombre, por eso creo esto.
                           nomEst1 = comprobarNombre(grafo.nodos.nodo[numEst].estacion.ID); // Comprobamos el nombre a partir del ID con una funcion auxiliar
                           fprintf(ptr, "  %s %s %s %02d:%02d %02d:%02d %.2f\n", grafo.nodos.nodo[numEst].arcos.arco[n].tramo.ID, estaciones.lista[nomEst1].nombre,estaciones.lista[nomEst].nombre,
                           grafo.nodos.nodo[numEst].arcos.arco[n].tramo.inicio.horas,grafo.nodos.nodo[numEst].arcos.arco[n].tramo.inicio.minutos,
                           grafo.nodos.nodo[numEst].arcos.arco[n].tramo.fin.horas,grafo.nodos.nodo[numEst].arcos.arco[n].tramo.fin.minutos,
                           grafo.nodos.nodo[numEst].arcos.arco[n].tramo.precio); 
                           
                        // Comprobamos cual es la duracion mínimam, comparando cada duracion con el minimo
                           if(grafo.nodos.nodo[numEst].arcos.arco[n].tramo.duracion < min)
                           {
                                min = grafo.nodos.nodo[numEst].arcos.arco[n].tramo.duracion;
                                minN = n;
                           }
                       }
              }
              // Imprimimos por ultimo la distancia minima, informando a qué tren corresponde
              fprintf(ptr, "\n%s%s%s %d %s\n", "El tren mas rapido (",grafo.nodos.nodo[numEst].arcos.arco[minN].tramo.ID,") dura",min,"minutos");
     }  
     fclose(ptr); // Cerramos el archivo .destino
     printf("\n\nArchivo creado con exito\n");
     Pausa();
     getchar();
}


/**-------------------------------------------------------------
|                 Fin del archivo ampliacion.c                  |
 --------------------------------------------------------------*/
