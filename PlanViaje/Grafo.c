/**------------------------------------------------------------- 
|   ARCHIVO: Grafo.c                                            |
|---------------------------------------------------------------|
|   Contenido: Crea un grafo, cargando los nodos, los arcos...  |
 --------------------------------------------------------------*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../TADsComunes/L_Estaciones.h"
#include "../TADsComunes/L_Tramos.h"

#include "TipoGrafo.h"

/**-------------------------------------------------------------
|  Funcion: mainCrearGrafo                                      |
|---------------------------------------------------------------|
|  Descripción: Carga la lista de nodos, arcos, crea el grafo   |
|                    y devuelve lo que le pides                 |
|  Entradas: La opcion seleccionada (1,2,3)                     |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void mainCrearGrafo(int opc)
{
     ListaNodos nodos;
     ListaArcos arcos;
     TipoGrafo Grafo;

     cargarListaNodos(&nodos);
     
     cargarListaTramos(&arcos, opc);
     
     crearGrafo(nodos, arcos, &Grafo);
     
     mainDijkstra(&Grafo, arcos, opc);
}


/**-------------------------------------------------------------
|  Funcion: cargarListaNodos                                    |
|---------------------------------------------------------------|
|  Descripción: Carga la lista de nodos (estaciones)            |
|  Entradas: registro de tipo ListaNodos                        |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void cargarListaNodos(ListaNodos *nodos)
{
        int n;
     	L_Estaciones estaciones;
     	
     	abrirArchivoEstacionesSinNumero(&estaciones);
     	
        // El numero de nodos es igual al numero de estaciones
       	nodos->numNodos = NumRegArchivoBin(NODOS_BIN, sizeof(Estacion));
        
        //Comprobamos que hay estaciones
        if(nodos->numNodos == 0)
        {
                      printf("ERROR. Debe haber estaciones registradas\n");
                      getchar();
                      exit(0);
        }
        else
        {        printf("Numero de estaciones: %d\n", nodos->numNodos);
		         // Creamos un vector de nodos->nodo registros de tipo TipoNodo 
		         nodos->nodo = (TipoNodo*) calloc(sizeof(TipoNodo), nodos->numNodos); 
		
		         // Cargamos cada estacion en cada nodo, asignando n al ID
		         for(n=0;n<nodos->numNodos;n++)
		         {
                                      nodos->nodo[n].ID = n;                                               
                                      nodos->nodo[n].estacion = estaciones.lista[n];
                 }       
        }                    
}


/**-------------------------------------------------------------
|  Funcion: cargarListaTramos                                   |
|---------------------------------------------------------------|
|  Descripción: Carga la lista de arcos (tramos)                |
|  Entradas: registro de tipo ListaArcos                        |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void cargarListaTramos(ListaArcos *arcos, int opc)
{
        int n;
     	L_Tramos Tramos;
     	
     	abrirArchivoTramos(&Tramos);
     	
        // El numero de arcos es igual al numero de tramos en total
       	arcos->numArcos = NumRegArchivoBin("../BaseDatos/tramos.dat", sizeof(TipoTramo));
       	
       	// Comprobamos que hay tramos registrados
        if(arcos->numArcos == 0)
        {
                      printf("ERROR. Debes generar los tramos previamente\n");
                      getchar();
                      exit(0);
        }
        else
        {           
		            // Creamos un vector de arcos->arco registros de tipo TipoArco 
		            arcos->arco = (TipoArco*) calloc(sizeof(TipoArco), arcos->numArcos); 
		
		            // Cargamos la informacion de todos los tramos en los arcos
		            for(n=0;n<arcos->numArcos;n++)
		            {
                                               arcos->arco[n].ID = n;
                                               arcos->arco[n].tramo = Tramos.lista[n];
                                               if(opc == 1) arcos->arco[n].peso = Tramos.lista[n].duracion; // Si se seleccino la opcion 1, el peso = duracion
                                               if(opc == 2) arcos->arco[n].peso = Tramos.lista[n].distancia; // Si se selecciono la opcion 2, el peso = distancia
                                               if(opc == 3) arcos->arco[n].peso = Tramos.lista[n].precio; // Si se seleciono la opcion 3, el peso = precio
                    }
        }   
}


/**-------------------------------------------------------------
|  Funcion: crearGrafo                                          |
|---------------------------------------------------------------|
|  Descripción: Carga la lista de arcos (tramos)                |
|  Entradas: registro de tipo ListaArcos, ListaNodos y TipoGrafo|
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void crearGrafo(ListaNodos nodos, ListaArcos arcos, TipoGrafo *Grafo)
{
        int numA, numN,n,na,num,i;
        char IDnodo[15];
        char IDarco[15];
    
        // El numero de arcos y de nodos lo guardamos en dos variables int
        numA = arcos.numArcos;
        numN = nodos.numNodos;

        Grafo->nodos = nodos;
        num = 0;
        for(n=0;n<numN;n++)
        {
                           // Copiamos en IDnodo el ID de cada estacion (de nodos)
                           strcpy(IDnodo, Grafo->nodos.nodo[n].estacion.ID);
                           Grafo->nodos.nodo[n].arcos.numArcos = 0;
                           // Buscamos cuantos tramos salen del nodo[n]. Solo interesa el numero 'num'
                           for(na=0;na<numA;na++)
                           {
                                            strcpy(IDarco, arcos.arco[na].tramo.IDorigen);
                                            // Si IDnodo e IDarco coinciden, ese tramo sale de ese nodo, sumamos 1 a num
                                            if(strcmp(IDnodo, IDarco) ==0) num++;
                           }
                           
                           // Si hay tramos que salen de ese nodo, cargamos la info de esos tramos en los arcos del nodo
                           if(num != 0)
                           {
                                  // Creamos vector dinamico de tamaño num
                                  Grafo->nodos.nodo[n].arcos.arco = calloc(sizeof(TipoArco),num);
                                  Grafo->nodos.nodo[n].arcos.numArcos = num;
                                  // Buscamos los tramos para copiarlos
                                  i = 0;
                                  for(na=0;na<numA;na++)
                                  {
                                                        strcpy(IDarco, arcos.arco[na].tramo.IDorigen);
                                                        // Igual que antes, si IDnodo e IDarco, coinciden, el origen de ese arco es ese nodo, lo copiamos
                                                        if(strcmp(IDnodo, IDarco) ==0)
                                                        {
                                                                       Grafo->nodos.nodo[n].arcos.arco[i] = arcos.arco[na];
                                                                       Grafo->nodos.nodo[n].arcos.arco[i].dest = nodoDestino(nodos, arcos.arco[na].tramo.IDdestino);  // Guardamos el destino de este tramo           
                                                                       i++;
                                                        }    
                                  }
                                  num = 0;
                           }
        }
}


/**-------------------------------------------------------------
|                 Fin del archivo Grafo.c                       |
 --------------------------------------------------------------*/
