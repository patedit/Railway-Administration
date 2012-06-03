/**-------------------------------------------------------------
|  Proyecto: Sistema de Planificacion de Viajes                 |
|  Subproyecto: Plan Viaje                                      |
|  Fuente:     mainPlanViaje.c                                  |
|  Creado:     15 Enero, 2008                                   |
|  Última revisión:   21 Enero, 2008                            |
|  Autor(es): Sergio Alonso Fdez                                |
 --------------------------------------------------------------*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../CodComun/func_auxiliares.h"

// Prototipos incluidos en este archivo 
void menuPlanViaje(void);
int menuPrincipal(void);

/**-------------------------------------------------------------
|   FUNCION: main()                                             |
 --------------------------------------------------------------*/
 
int main()
{
	menuPlanViaje();
    printf( "Fin del programa.");
	return 0;
}

/**-------------------------------------------------------------
|  Funcion: menuPlanViaje                                       |
|---------------------------------------------------------------|
|  Descripción: selecciona el servicio elegido por el usuario   |
|  Entradas: ninguna                                            |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void menuPlanViaje(void)
{
	int opcion;

    
	while ((opcion = menuPrincipal()) != 0) {
		switch (opcion) {
			case 1: // Mantenimiento de Estaciones
				mainCrearGrafo(1);  // Le pasamos 1 como parámetro por ser la opcion 1
                break;		
			case 2: // Mantenimiento de Trenes
				mainCrearGrafo(2); // Le pasamos 2 como parámetro por ser la opcion 2
                break;
			case 3: // Generación de Tramos
				mainCrearGrafo(3); // Le pasamos 3 como parámetro por ser la opcion 3
			case 4:
                 funcionAmpliacion(4);
			case 0:
				break;
		}
	}
}


/**-------------------------------------------------------------
|  Funcion: menuPrincipal                                       |
 ---------------------------------------------------------------
|  Descripción: Muestra las opciones del menu principal:        |
|               1. Calcular ruta mas rapida                     |
|               2. Calcular ruta mas corta                      |
|               3. Calcular ruta mas economica                  |
|  Entradas: ninguna                                            |
|  Retorno: seleccion del usuario.                              |
 --------------------------------------------------------------*/
int menuPrincipal(void) 
{
	// Variables locales
	int eleccion;
	
	system("cls");
	cabeceraTabla("Sistema de Planificacion de Viajes");

	printf( " 1. Calcular ruta mas rapida\n");
	printf( " 2. Calcular ruta mas corta\n");
	printf( " 3. Calcular la ruta mas economica.\n");
	printf( " 4. Funcion ampliacion\n");
	printf( " 0. Fin del Programa.\n\n");
	         
	eleccion = leerOpcionValida("Seleccione opcion:  ", '4');

	return eleccion;
}

/**-------------------------------------------------------------
|                 Fin del archivo mainPlanViaje.c               |
 --------------------------------------------------------------*/

