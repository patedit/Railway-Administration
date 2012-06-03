/**-------------------------------------------------------------
|  Proyecto: Sistema de Planificacion de Viajes                 |
|  Subproyecto: Gestión                                         |
|  Fuente:     Gestion_main.c                                   |
|  Creado:     01 Dic, 2007                                     |
|  Última revisión:   01 Dic, 2007                              |
|  Autor(es): Sergio Alonso Fernández                     |
 --------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../CodComun/func_auxiliares.h"
#include "../TADsComunes/L_Estaciones.h"

// Prototipos incluidos en este archivo 
void gestionMenuPrincipal(void);
int menuPrincipal(void);

/**-------------------------------------------------------------
|   FUNCION: main()                                             |
 --------------------------------------------------------------*/
int main()
{
	gestionMenuPrincipal();
    printf( "Fin del programa.");
	return 0;
}

/**-------------------------------------------------------------
|  Funcion: gestionMenuPrincipal                                |
|---------------------------------------------------------------|
|  Descripción: selecciona el servicio elegido por el usuario   |
|  Entradas: ninguna                                            |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void gestionMenuPrincipal(void)
{
	int opcion;

	while ((opcion = menuPrincipal()) != 0) {
		switch (opcion) {
			case 1: // Mantenimiento de Estaciones
				mantenimientoEstaciones();
                break;		
			case 2: // Mantenimiento de Trenes
				mantenimientoTrenes();
                break;
			case 3: // Generación de Tramos
				generarTramos();
			case 4:
                 //insertarUnaParada();
			case 0:
				break;
		}
	}
}

/**-------------------------------------------------------------
|  Funcion: menuPrincipal                                       |
 ---------------------------------------------------------------
|  Descripción: Muestra las opciones del menu principal:        |
|               1. Mantenimiento de Estaciones                  |
|               2. Mantenimiento de Trenes                      |
|               3. Generacion de Tramos                         |
|  Entradas: ninguna                                            |
|  Retorno: seleccion del usuario.                              |
 --------------------------------------------------------------*/
int menuPrincipal(void) 
{
	// Variables locales
	int eleccion;
	
	system("cls");
	cabeceraTabla("Sistema de Planificacion de Viajes");

	printf( "1  Mantenimiento de Estaciones.\n");
	printf( "2  Mantenimiento de Trenes.\n");
	printf( "3  Generacion de Tramos.\n");
	printf( "0. Fin del Programa.\n\n");
	         
	eleccion = leerOpcionValida("Seleccione opcion:  ", '3');

	return eleccion;
}

/**-------------------------------------------------------------
|                     FIN DEL ARCHIVO mainGestion               |
 --------------------------------------------------------------*/
