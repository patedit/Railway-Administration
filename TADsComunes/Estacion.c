/**------------------------------------------------------------- 
|   ARCHIVO: Estacion.c                                         |
|---------------------------------------------------------------|
|   Contenido: definiciones de las funciones asociadas          |
|               al TAD Estacion                                 |
 --------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Estacion.h"
#include "../CodComun/func_auxiliares.h"

/**-------------------------------------------------------------
|  Funcion: anadirEstacion                                      |
|---------------------------------------------------------------|
|  Descripción: pide los datos de la nueva estacion             |
|                                                               |
|  Entradas: dirección de registro Estacion                     |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/
void anadirEstacion(Estacion *estacion)
{
	printf("Codigo de estacion: ");     gets(estacion->ID);
	printf("Nombre de la estacion: ");  gets(estacion->nombre);
	printf("Localidad: ");              gets(estacion->localidad);
	estacion->pos = leerPosicion_v1();
}
/**-------------------------------------------------------------
|  Funcion: mostrarEstacion                                     |
|---------------------------------------------------------------|
|  Descripción: muestra por pantalla los datos del registro     |
|               que recibe como parámetro                       |
|  Entradas: registro de tipo Estacion                          |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/
void mostrarEstacion(Estacion estacion)
{
	printf(FMT_ESTACION, 179, estacion.ID, estacion.nombre, 
		                 estacion.localidad, estacion.pos.latitud, 
						 estacion.pos.longitud, 179);
}

/**-------------------------------------------------------------
|  Funcion: validarEstacion                                     |
|---------------------------------------------------------------|
|  Descripción: comprueba si el código de una estación está     |
|               registrado; si no lo está, pide los datos de la |
|               nueva estación y la registra                    |
|                                                               |
|  Entradas: código de la estación a validar                    |
|  Retorno: nada                                                |
|--------------------------------------------------------------*/

void validarEstacion(char *ID)
{
	FILE *ptr;
	Estacion estacion;
	char opcion;
	int encontrado = 0;

	ptr = fopen(ESTACIONES_BIN, "rb");
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

	if(!encontrado)
	{
		printf("\nESTACION NO REGISTRADA.\n\n");
        
	    opcion = leerSiNo("La estacion DEBE estar registrada para poder continuar\n\nDesea crear una estacion con ese codigo (S/N)?");
		if(opcion == 'S')
		{
		          strcpy(estacion.ID, ID);
                  fflush(stdin);
		          printf("\tNombre: "); gets(estacion.nombre);
		          printf("\tLocalidad: "); gets(estacion.localidad);
		          printf("\tLatitud (en grados) : "); scanf("%lf", &estacion.pos.latitud);
		          printf("\tLongitud (en grados): "); scanf("%lf", &estacion.pos.longitud);

		          // grabar datos de la nueva estacion
                  ptr = fopen(ESTACIONES_BIN, "ab");
          	      if(ptr == NULL) {
          		  printf("El archivo %s no existe.\n", ESTACIONES_BIN);
              }
             	  fwrite((Estacion*)&estacion, sizeof(Estacion), 1, ptr);
        	      fclose(ptr);
              	  /* llamo a la funcion imprimirEstaciones para generar el archivo de texto  */
                  imprimirEstaciones();
                  Pausa();

        }
        else
        {
            mantenimientoTrenes();
        }

      }

}

void modificarEstacion(Estacion *estacion)
{
	int eleccion;

	comienzoTabla();
	mostrarEstacion(*estacion);
	finTabla();
	printf("Indique el campo que quiere modificar (1 a 4): ");
	eleccion = leerOpcionValida("Seleccione opcion:  ", '4');
	switch(eleccion)
	{
		case 1: // ID
			printf("Nuevo codigo: "); gets(estacion->ID);
			break;
		case 2: // Nombre
			printf("Nuevo nombre: "); gets(estacion->nombre);
			break;
		case 3: // Localidad
			printf("Localidad: "); gets(estacion->localidad);
			break;
		case 4: // posicion
			estacion->pos = leerPosicion_v1();
			break;
		default: printf("Seleccion erronea\n"); 
			printf("La estacion de codigo %s no ha sido modificada\n", estacion->ID);
			Pausa();
			return;
	}

	printf("La estacion de codigo %s ha sido modificada\n", estacion->ID);
}

/**-------------------------------------------------------------
|                 Fin del archivo Estacion.c                    |
 --------------------------------------------------------------*/
 
