/**------------------------------------------------------------- 
|   ARCHIVO: Tren.c                                             |
|---------------------------------------------------------------|
|   Contenido: definiciones de las funciones asociadas          |
|               al TAD Tren                                     |
 --------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Tren.h"
#include "../CodComun/func_auxiliares.h"


/**-------------------------------------------------------------
|  Funcion: mostrarTren                                         |
|---------------------------------------------------------------|
|  Descripción: muestra por pantalla los datos del registro     |
|               que recibe como parámetro                       |
|  Entradas: registro de tipo Tren                              |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/
void mostrarTren(Tren tren)
{
     
	printf(FMT_TREN, 179, tren.ID, tren.nombre, 
		                 tren.tipo, tren.origen, 
						 tren.destino, tren.salida.horas, tren.salida.minutos, tren.llegada.horas, tren.llegada.minutos, tren.precio, 179);
}


void modificarTren(Tren *tren)
{

	int eleccion;

	comienzoTabla();
	mostrarTren(*tren);
	finTabla();
	printf("Indique el campo que quiere modificar (1 a 9)\n ");
	printf("\t1.ID\n\t2.Nombre\n\t3.Tipo de tren\n\t4.Est. Origen\n\t5.Est.Destino\n\t6.Hora salida\n\t7.Hora llegada\n\t8.Precio\n\t9.RUTAS\n\n");
	eleccion = leerOpcionValida("Seleccione opcion:  ", '9');
	switch(eleccion)
	{
		case 1: // ID
			printf("Nuevo codigo de identificación: "); gets(tren->ID);
			break;
		case 2: // Nombre
			printf("Nuevo nombre: "); gets(tren->nombre);
			break;
		case 3: // Tipo tren
			printf("Nuevo tipo tren: "); gets(tren->tipo);
			break;
		case 4: // Codigo estacion origen
            printf("Nuevo cod. estacion origen: "); gets(tren->origen);
			break;
		case 5: // Codigo estacion destino
            printf("Nuevo cod. estacion destino: "); gets(tren->destino);
			break;
		case 6: // Hora salida
            printf("Nueva hora de salida <hh:mm>: "); scanf("%d:%d", &tren->salida.horas, &tren->salida.minutos);
			break;
		case 7: // Hora llegada
            printf("Nueva hora de llegada <hh:mm>: "); scanf("%d:%d", &tren->llegada.horas, &tren->llegada.minutos);
			break;
		case 8: // Precio
            printf("Nuevo precio: "); scanf("%f", &tren->precio);
			break;
		case 9: // Ruta
            actualizarRuta(tren->ID);
			break;
		default: printf("Seleccion erronea\n"); 
			printf("El tren de codigo %s no ha sido modificado\n", tren->ID);
			Pausa();
			return;
	}

	printf("El tren de codigo %s ha sido modificado\n", tren->ID);
}


void anadirTren(Tren *tren)
{
    int duracionMin, duracionHor;
	printf("Codigo de identificacion del tren: ");     gets(tren->ID);
	printf("Nombre del tren: ");  gets(tren->nombre);
	printf("Tipo de tren: ");  gets(tren->tipo);
	printf("Codigo de estacion de origen: ");                gets(tren->origen); validarEstacion();
	printf("Codigo de estacion de destino: ");               gets(tren->destino); validarEstacion();
	printf("Hora salida en formato <hh:mm>: ");              scanf("%d:%d", &tren->salida.horas, &tren->salida.minutos); validarHora(tren->salida.horas, tren->salida.minutos);
	printf("Hora llegada en formato <hh:mm>: ");             scanf("%d:%d", &tren->llegada.horas, &tren->llegada.minutos); validarHora(tren->salida.horas, tren->salida.minutos);
	printf("Precio total del viaje: ");                      scanf("%f", &tren->precio);
	
}

/**-------------------------------------------------------------
|                 Fin del archivo Tren.c                        |
 --------------------------------------------------------------*/
 
