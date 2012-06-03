/**------------------------------------------------------------- 
|   ARCHIVO: funcionesAds.c                                     |
|---------------------------------------------------------------|
|   Contenido: Archivo con funciones adicionales de PlanViaje   |
 --------------------------------------------------------------*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../TADsComunes/L_Estaciones.h"
#include "../TADsComunes/L_Tramos.h"
#include "../TADsComunes/L_Trenes.h"

#include "TipoGrafo.h"

/**-------------------------------------------------------------
|  Funcion: abrirArchivoEstacionesSinNumero                     |
|---------------------------------------------------------------|
|  Descripción: Abre el archivo de Estaciones (Sin numero)      |
|  Entradas: registro L_Estaciones                              |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void abrirArchivoEstacionesSinNumero(L_Estaciones *Estaciones)
{
	FILE *ptr; 
	
	// Compruebo existencia de archivo y nº de registros
	Estaciones->num = NumRegArchivoBin(ESTACIONES_BIN, sizeof(Estacion));
	if(Estaciones->num){


		ptr = fopen(ESTACIONES_BIN, "rb");
		// Creamos un vector de Estacion->num registros de tipo Estacion 
		Estaciones->lista = (Estacion*) calloc(sizeof(Estacion), Estaciones->num);
		if(Estaciones->lista == NULL) {
			printf("No hay memoria suficiente para la lista de estaciones.\n");
			Pausa();
			exit(0);
		}
		// Leo la lista de estaciones
		fread((Estacion*)Estaciones->lista, sizeof(Estacion), Estaciones->num, ptr);
	}
}


/**-------------------------------------------------------------
|  Funcion: mostrarUnTramo                                      |
|---------------------------------------------------------------|
|  Descripción: muestra un tramo que le paso                    |
|                                                               |
|  Entradas: dirección de registro TipoTramo                    |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void mostrarUnTramo(TipoTramo tramo)
{
     int var1, var2;
     L_Estaciones estaciones;
     // Abrimos el archivo estaciones
     abrirArchivoEstacionesSinNumero(&estaciones);
     // comprobamos el nombre que corresponde a una ID para mostrar el nombre de la estacion y no el ID
     var1 = comprobarNombre(tramo.IDorigen);
     var2 = comprobarNombre(tramo.IDdestino);

	printf(FMT_TRAMO2, 179, tramo.ID, estaciones.lista[var1].nombre, 
		                 estaciones.lista[var2].nombre, tramo.inicio.horas, tramo.inicio.minutos, 
						 tramo.fin.horas, tramo.fin.minutos, tramo.precio, 179);
}


/**-------------------------------------------------------------
|  Funcion: mostrarUnaEstacion                                  |
|---------------------------------------------------------------|
|  Descripción: muestra una estacion que le paso                |
|                                                               |
|  Entradas: dirección de registro Estacion                     |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/
void mostrarUnaEstacion(Estacion estacion)
{

	printf(FMT_ESTACION, 179, estacion.ID, estacion.nombre, 
		                 estacion.localidad, estacion.pos.latitud, 
						 estacion.pos.longitud, 179);
}


/**-------------------------------------------------------------
|  Funcion: calcularDuracionEspera                              |
|---------------------------------------------------------------|
|  Descripción: calcular la duracion de espera de una ruta      |
|                                                               |
|  Entradas: dirección de registro TipoGrafo, ListaArcos..      |
|  Retorno: la duracion de espera d ela ruta (int)              |
|--------------------------------------------------------------*/

int calcularDuracionEspera(TipoGrafo *Grafo,ListaArcos Arcos, int source, int destino)
{                          
     int i, n, numTramos=0,durEspera=0,durEsperaMin,durEsperaHor;
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

     for(i=numTramos-1;i>=0;i--)
     {
         if(i!=0)
         {
             // Si el inicio del tramo2 es menor que el fin del tramo1, hay que sumarle 24 al resultado obtenido
             if(Arcos.arco[vector[i-1]].tramo.inicio.horas < Arcos.arco[vector[i]].tramo.fin.horas)
             {
                   durEsperaHor = ((Arcos.arco[vector[i-1]].tramo.inicio.horas - Arcos.arco[vector[i]].tramo.fin.horas)+24)*60;
             }
             else 
             {    
                  // Restamos la segunda d ela primera y multiplicamos por 60 para pasarlo a minutos                   
                  durEsperaHor = (Arcos.arco[vector[i-1]].tramo.inicio.horas - Arcos.arco[vector[i]].tramo.fin.horas)*60;
                  if(durEsperaHor<0) durEsperaHor = -(durEsperaHor); // Cambiamos el signo si fuera negativo
             }
             durEsperaMin = Arcos.arco[vector[i-1]].tramo.inicio.minutos - Arcos.arco[vector[i]].tramo.fin.minutos;

             durEspera = durEsperaMin + durEsperaHor + durEspera; // Sumamos minutos, horas y el resultado anterior
         } 
     }

         return durEspera; // Devolvemos la duracion de la espera
} 


/**-------------------------------------------------------------
|  Funcion: validarEstacionViaje                                |
|---------------------------------------------------------------|
|  Descripción: comprueba si el código de una estación está     |
|               registrado.                                     |
|                                                               |
|  Entradas: código de la estación a validar                    |
|  Retorno: devuelve si encontro la estacion                    |
|--------------------------------------------------------------*/

int validarEstacionViaje(char *ID)
{
	FILE *ptr;
	Estacion estacion;
	char opcion;
	int encontrado = 0,a;

	ptr = fopen(NODOS_BIN, "rb");
	if(ptr!=NULL) // el archivo existe
	{
		while(!feof(ptr) && !encontrado) 
		{
			fread(&estacion, sizeof(Estacion), 1, ptr); // leo el registro
			if(strcmp(estacion.ID, ID)==0 ) // los ID coinciden
			{
				encontrado = 1;
			}
		}
		fclose(ptr);
	}
    
    // En este caso la estacion no esta registrada
	if(!encontrado)
	{
        
		printf("----------------------\nESTACION NO REGISTRADA\n----------------------\n"); 
        return 0;
      }
      else return -1;

}

/**-------------------------------------------------------------
|  Funcion: comprobarNombre                                     |
|---------------------------------------------------------------|
|  Descripción: comprueba si el código de una estación está     |
|               registrado.                                     |
|                                                               |
|  Entradas: código de la estación a validar                    |
|  Retorno: Numero de la estacion con esa ID                    |
|--------------------------------------------------------------*/

int comprobarNombre(char *ID)
{
    L_Estaciones estaciones;
    int np=0, encontrado=0;
   	abrirArchivoEstacionesSinNumero(&estaciones);
   	
   	// Busca en la lista de estaciones la que tiene el ID que le pasamos y copia np y lo devuelve
   	while(np<estaciones.num && !encontrado)
    {
   	     if(strcmp(estaciones.lista[np].ID,  ID) ==0) encontrado=1;
   	     else np++;
    }
    
    if(encontrado) return np;
     
     
}

/**-------------------------------------------------------------
|  Funcion: nodoDestino                                         |
|---------------------------------------------------------------|
|  Descripción: calcula el nodo destino de un tramo.            |
|                                                               |
|  Entradas: código de la estación a validar                    |
|  Retorno: devuelve el nodo destino                            |
|--------------------------------------------------------------*/

int nodoDestino(ListaNodos nodos, char *IDdestino)
{
    int n,numN;
    
    numN = nodos.numNodos;
    // Compara el IDdestino del nodo con todas las ID de cada esatcion
    for(n=0; n<numN; n++)
    {
             if(strcmp(IDdestino, nodos.nodo[n].estacion.ID) ==0)
             {
                                  return n;
             }
    }
}


/**-------------------------------------------------------------
|  Funcion: abrirArchivoTramos                                  |
|---------------------------------------------------------------|
|  Descripción: abre el archivo de tramos.dat y lo lee          |
|                                                               |
|  Entradas: registro de tipo L_Tramos                          |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void abrirArchivoTramos(L_Tramos *Tramos)
{
	FILE *ptr; 
	
	// Compruebo existencia de archivo y nº de registros
	Tramos->num = NumRegArchivoBin("../BaseDatos/tramos.dat", sizeof(TipoTramo));
	if(Tramos->num){
		printf("Numero de tramos: %d\n\n\n", Tramos->num);

		ptr = fopen("../BaseDatos/tramos.dat", "rb");
		// Creamos un vector de Tramos->num registros de tipo TipoTramo 
		Tramos->lista = (TipoTramo*) calloc(sizeof(TipoTramo), Tramos->num);
		if(Tramos->lista == NULL) {
			printf("No hay memoria suficiente para la lista de tramos.\n");
			Pausa();
			exit(0);
		}
		fread((TipoTramo*)Tramos->lista, sizeof(TipoTramo), Tramos->num, ptr);
	}
}

/**-------------------------------------------------------------
|                 Fin del archivo funcionesAds.c                |
 --------------------------------------------------------------*/
