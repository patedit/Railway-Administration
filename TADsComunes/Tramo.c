/**------------------------------------------------------------- 
|   ARCHIVO: Tramo.c                                            |
|---------------------------------------------------------------|
|   Contenido: definiciones de las funciones asociadas          |
|               al TAD Tramo                                    |
 --------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "L_Tramos.h"
#include "L_Trenes.h"
#include "L_Estaciones.h"

#include "../CodComun/func_auxiliares.h"


/**-------------------------------------------------------------
|  Funcion: anadirEstacion                                      |
|---------------------------------------------------------------|
|  Descripción: pide los datos de la nueva estacion             |
|                                                               |
|  Entradas: dirección de registro Estacion                     |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/
void anadirTramo(TipoTramo *tramo, Tren tren)
{ 
    L_Tramos Tramos;
   	L_Estaciones estaciones; 
   	L_Trenes Trenes;
   	FILE *ptr;
    int i=0,encontrado=0,est1,est2,duracionMin,duracionHor,duracionTren;
  	char archivo[50];
    char auxiliar[10];
    sprintf(auxiliar, "%s", tren);
    
	abrirArchivoRutas(&Tramos, tren);
    strcpy(tramo->ID, auxiliar);

    if(Tramos.num == 0) strcpy(tramo->IDorigen, tren.origen);
    else if(strcmp(Tramos.lista[Tramos.num-1].IDdestino, tren.destino)==0){ printf("\n\nLa ruta esta ya COMPLETA.\n\nPuedes eliminar toda la ruta o paradas de la misma\n"); getchar(); mantenimientoTrenes(); } else strcpy(tramo->IDorigen, Tramos.lista[Tramos.num-1].IDdestino);
	printf("Codigo de estacion destino: ");     gets(tramo->IDdestino); validarEstacion(tramo->IDdestino);
	if(strcmp(tren.destino, tramo->IDdestino)==0)
    {
                            printf("\nAcabas de completar la ruta\n");
	                        if(Tramos.num == 0) {tramo->inicio.horas = tren.salida.horas ; tramo->inicio.minutos=tren.salida.minutos;}
	                        else {
                                    printf("\n[Consejo] - El tren llega a la estacion de origen a las %02d:%02d\n", Tramos.lista[Tramos.num-1].fin.horas, Tramos.lista[Tramos.num-1].fin.minutos);
                                 	printf("Introduce hora de salida <hh:mm>: "); scanf("%d:%d", &tramo->inicio.horas, &tramo->inicio.minutos); validarHora(tramo->inicio.horas, tramo->inicio.minutos);
                                 }
    tramo->fin.horas = tren.llegada.horas;
    tramo->fin.minutos = tren.llegada.minutos;
    } 
    else
    { 
                       if(Tramos.num == 0) {tramo->inicio.horas = tren.salida.horas ; tramo->inicio.minutos=tren.salida.minutos;printf("\nHora salida: %02d:%02d\n", tramo->inicio.horas, tramo->inicio.minutos);}
	                   else {printf("\n[Consejo] - El tren llega a la estacion de origen a las %02d:%02d\n", Tramos.lista[Tramos.num-1].fin.horas, Tramos.lista[Tramos.num-1].fin.minutos);
	                   printf("Introduce hora de salida <hh:mm>: "); scanf("%d:%d", &tramo->inicio.horas, &tramo->inicio.minutos); validarHora(tramo->inicio.horas, tramo->inicio.minutos);}
                       printf("Introduce hora prevista de llegada <hh:mm>: "); scanf("%d:%d", &tramo->fin.horas, &tramo->fin.minutos); validarHora(tramo->fin.horas, tramo->fin.minutos);
    }
	// Calculamos la duracion del tramo
	if(tramo->inicio.minutos > tramo->fin.minutos)
	{
                             duracionHor = (((tramo->fin.horas) - (tramo->inicio.horas))-1)*60;
                             duracionMin = ((60-tramo->inicio.minutos)+tramo->fin.minutos);
    }
    else 
    {
    duracionHor = (tramo->fin.horas - tramo->inicio.horas)*60;  // En minutos
    
    duracionMin = tramo->fin.minutos - tramo->inicio.minutos;
    if(duracionMin<0) duracionMin = -(duracionMin);     // Cambiamos el signo si fuera negativo
    
    if(duracionHor<0) duracionHor = -(duracionHor);
    }
    tramo->duracion = duracionMin + duracionHor;
        // Calculamos la duracion
    if(tren.salida.minutos > tren.llegada.minutos)
	{
                             duracionHor = (((tren.llegada.horas) - (tren.salida.horas))-1)*60;
                             duracionMin = ((60-tren.salida.minutos)+tren.llegada.minutos);
    }
    else 
    {
    duracionHor = (tren.llegada.horas - tren.salida.horas)*60;  // En minutos
    
    duracionMin = tren.llegada.minutos - tren.salida.minutos;
    if(duracionMin<0) duracionMin = -(duracionMin);     // Cambiamos el signo si fuera negativo
    
    if(duracionHor<0) duracionHor = -(duracionHor);
    }
    duracionTren = duracionMin + duracionHor;
    // Calculamos el precio
	tramo->precio = ((tramo->duracion) * (tren.precio/duracionTren));

    // Calculamos la distancia, abriendo las estaciones
   	abrirArchivoEstaciones(&estaciones);
   	// aqui buscamos la estacion que corresponde con la ID
    while(i<estaciones.num && !encontrado)
    {
                           if(strcmp(estaciones.lista[i].ID, tramo->IDorigen)==0) encontrado=1; //encontro
                           else i++;
    }
    est1 = i; //copiamos
    i=0;
    encontrado=0;
    while(i<estaciones.num && !encontrado)
    {
                           if(strcmp(estaciones.lista[i].ID, tramo->IDdestino)==0) encontrado=1;
                           else i++;
    }
    est2 = i;

    tramo->distancia = distanciaGeodesica(estaciones.lista[est1].pos, estaciones.lista[est2].pos);
    
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
	printf(FMT_TRAMO2, 179, tramo.ID, tramo.IDorigen, 
		                 tramo.IDdestino, tramo.inicio.horas, tramo.inicio.minutos, 
						 tramo.fin.horas, tramo.fin.minutos, tramo.precio, 179);
}




/**-------------------------------------------------------------
|                 Fin del archivo Tramo.c                        |
 --------------------------------------------------------------*/
