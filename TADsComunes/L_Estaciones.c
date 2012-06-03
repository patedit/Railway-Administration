/**-------------------------------------------------------------
|   ARCHIVO: L_Estaciones.c                                     |
 ---------------------------------------------------------------
|   Contenido: definiciones de las funciones asociadas          |
|               al TAD L_Estacion                               |
 --------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "L_Estaciones.h"
#include "../CodComun/func_auxiliares.h"

/**-------------------------------------------------------------
|  Funcion: mantenimientoEstaciones                             |
|---------------------------------------------------------------
|  Descripción: selecciona el servicio elegido por el usuario   |
|  Entradas: ninguna                                            |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void mantenimientoEstaciones(void)
{
	L_Estaciones est={0}; // Inicializo todos los campos a 0
	int opcion;

	while ((opcion = menuMantenimientoEstaciones()) != 0) {
		switch (opcion) {
			case 1: // Añadir un nueva estacion
				anadirUnaEstacion();
				break;
			case 2: // Listar todas las estaciones
				mostrarTodasEstaciones();
				break;			
			case 3: // Modificar datos de una estacion
				modificarUnaEstacion();
				break; 
			case 4: // Eliminar una estacion
			  	eliminarEstacion();
				break;

			case 0: // Menu anterior
				break;
		} // fin switch
	} // fin while
}

/**-------------------------------------------------------------
|  Funcion: menuMantenimientoEstaciones                         |
 ---------------------------------------------------------------
|  Descripción: Muestra las opciones de mantenimiento:          |
|               1. Añadir una nueva estación                    |
|               2. Listar todas las estaciones                  |
|               3. Actualizar los datos de una estación         |
|               4. Eliminar una estacionMostrar estación        |
|  Entradas: ninguna                                            |
|  Retorno: seleccion del usuario.                              |
 --------------------------------------------------------------*/
int menuMantenimientoEstaciones(void)
{
	// Variables locales
	int eleccion=0;

	system("cls");
	cabeceraTabla("Mantenimiento de Estaciones");
	
	printf( "1  A\244adir una nueva estaci\xA2n\n");
	printf( "2  Listar todas las estaciones.\n");
	printf( "3  Actualizar los datos de una estaci\xA2n\n");
	printf( "4. Eliminar una estaci\xA2n\n");
	printf( "0. Menu anterior.\n\n");

	eleccion = leerOpcionValida("Seleccione opcion:  ", '4');

	return eleccion;
}

/**-------------------------------------------------------------
|  Funcion: modificarUnaEstacion                                |
 ---------------------------------------------------------------
|  Descripción: selecciona una estación y modifica uno de sus   |
|               campos                                          |
|                                                               |
|  Entradas: ninguna                                            |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/

void modificarUnaEstacion()
{
	int encontrado = 0, i=0;
	char cadena[80]="";
	L_Estaciones estaciones;

	// Compruebo existencia de archivo y nº de registros
	estaciones.num = NumRegArchivoBin(ESTACIONES_BIN, sizeof(Estacion));

	if(!estaciones.num){
		printf( "La lista de estaciones esta vacia. \n");
		Pausa();
		return;
	}

	// hay paradass registradas
	system("cls");
	cabeceraTabla("Actualizar los datos de una estacion");

	abrirArchivoEstaciones(&estaciones);
	
	mostrarTodasEstaciones();


	printf("Seleccione codigo de la estacion \na modificar (pulse <RETURN> para cancelar): ");
	fflush(stdin);  gets(cadena);
	// compruebo si la cadena contiene algun codigo
	if(strlen(cadena)==0)
	{
		printf("Modificacion cancelada\n");
		Pausa();
		return;
	}

	// busqueda de la estacion correspondiente al codigo tecleado
	i=0;
	while(!encontrado && i<estaciones.num) {
		if( strcmp(estaciones.lista[i].ID, cadena) == 0) {
			encontrado = 1;
		}
		else i++;
	}
	if(encontrado) {  // se ha encontrado la estacion
		modificarEstacion(&estaciones.lista[i]);
		grabarArchivoEstaciones(estaciones);
		imprimirEstaciones();
	}
	else{ // no se ha encontrado la estacion
		printf("La estacion de codigo %s no esta registrada\n", cadena);
		Pausa();
	}

}

/**-------------------------------------------------------------
|  Funcion: eliminarEstacion                                    |
 ---------------------------------------------------------------
|  Descripción: elimina una estacion de la lista                |
|                                                               |
|  Entradas: los datos se leen del archivo                      |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void eliminarEstacion(void)
{
	int i, encontrado;
	char codigo[10];
	int eleccion;
	char opcion; 
	L_Estaciones estaciones;

	// Compruebo existencia de archivo y nº de registros
	estaciones.num = NumRegArchivoBin(ESTACIONES_BIN, sizeof(Estacion));

	if(!estaciones.num){
		printf( "La lista de estaciones esta vacia. \n");
		Pausa();
		return;
	}

	// hay paradass registradas
	system("cls");
	cabeceraTabla("Eliminar una estacion");
	abrirArchivoEstaciones(&estaciones);
	
	mostrarTodasEstaciones();
	
	printf("Indique el codigo de la estacion que quiere modificar: ");
	gets(codigo);
	i= 0;
	encontrado = 0;

	while(i<estaciones.num && !encontrado)
	{
		if( strcmp(estaciones.lista[i].ID, codigo) == 0) // si el codigo de la estacion coincide
		{
			encontrado = 1; // hemos encontrado la estacion a borrar
		}
		else i++;
	}
	if(encontrado)
	{
		eleccion = i;
		printf("Ha seleccionado la siguiente estacion:\n");
		comienzoTabla();
		mostrarEstacion(estaciones.lista[eleccion]);
		finTabla();
		opcion = leerSiNo("Desea eliminarla (S/N)?");
		if(opcion == 'S')
		{
			for(i=eleccion;i<estaciones.num;i++)
				estaciones.lista[i] = estaciones.lista[i+1]; // copio la estacion i+1 en la i

			estaciones.num--;
			
			printf("La estacion de codigo %s ha sido borrada\n", codigo);
			grabarArchivoEstaciones(estaciones);
			imprimirEstaciones(); 
		}
		else
		{
			printf("Eliminacion cancelada\n");
			Pausa();
		}
	}
	else // no existe esa estacion
		printf("El codigo seleccionado (%s) no corresponde a ninguna estacion.\n", codigo);
	Pausa();
}


/**-------------------------------------------------------------
|  Funcion: mostrarTodasEstaciones                              |
 ---------------------------------------------------------------
|  Descripción: Lista todos las estaciones registradas          |
|                                                               |
|  Entradas: vector de registros de tipo Estacion               |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void mostrarTodasEstaciones(void)
{
	// Variables locales
	int np, j;
	char linea[255];
	L_Estaciones Estaciones;

	// Compruebo existencia de archivo y nº de registros
	Estaciones.num = NumRegArchivoBin(ESTACIONES_BIN, sizeof(Estacion));
	if(!Estaciones.num){
		printf( "La lista de estaciones esta vacia. \n");
		Pausa();
		return; // salimos de la función
	}
	
	// Cargamos los datos desde el archivo
	abrirArchivoEstaciones(&Estaciones);

	system("cls");
	cabeceraTabla("Listado de Estaciones");

	comienzoTabla();

	sprintf(linea, FMT_ESTACIONX, 179, "ID", "Nombre", "Poblacion", 
		                       "Latitud", "Longitud", 179);
	printf("%s", linea);
	linea[0] = (char)195; for(j=1;j<78;j++) linea[j] = (char)196; linea[78]=(char)180; linea[79]=0;
	printf("%s\n", linea);

	if (Estaciones.num == 0) {        
		printf("%c %-75s %c\n", 179, "La lista de estaciones esta vacia.",179);
	}
	else {
		for (np=0; np < Estaciones.num; np++) {
			mostrarEstacion(Estaciones.lista[np]);
		}
	}
	finTabla();
	Pausa();
}

/**-------------------------------------------------------------
|  Funcion: anadirNuevaEstacion                                 |
 ---------------------------------------------------------------
|  Descripción: rellena los campos del registro estacion con    |
|               datos leidos del teclado, y añade el nuevo      | 
|               registro al archivo de estaciones               |
|  Entradas: dirección a un registro de tipo Estacion           |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void anadirUnaEstacion()
{
	Estacion estacion; // registro para la nueva estación
	FILE *ptr; // puntero al archivo de datos
	int nreg; // numero de registros en el archivo de Estaciones

	// calculo el numero de estaciones almacenadas en el 
	// archivo con la funcion numRegArchivoBin
	nreg = NumRegArchivoBin(ESTACIONES_BIN, sizeof(Estacion));
	printf("Numero de estaciones registradas: %d\n", nreg);

	// Pido los datos de la nueva estación
	anadirEstacion(&estacion);

	// Abro el archivo para AÑADIR (append) el nuevo registro
	ptr = fopen(ESTACIONES_BIN, "ab");
	if(ptr == NULL) {
		printf("El archivo %s no existe.\n", ESTACIONES_BIN);
	}
	fwrite((Estacion*)&estacion, sizeof(Estacion), 1, ptr);
	fclose(ptr);
	/* llamo a la funcion imprimirEstaciones para generar el 
	   archivo de texto  */
   imprimirEstaciones();
}
/**-------------------------------------------------------------
|  Funcion: abrirArchivoEstacionesSinNumero                     |
 ---------------------------------------------------------------
|  Descripción: Abre el archivo binario de estaciones y lo carga| 
|               en memoria en la dirección pasada como parámetro|
|                                                               |
|  Entradas: direccion del registro 'lista de Estaciones'       |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
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
		fread((Estacion*)Estaciones->lista, sizeof(Estacion), Estaciones->num, ptr);
	}
//	return Estaciones->num;
}
/**-------------------------------------------------------------
|  Funcion: abrirArchivoEstaciones                              |
 ---------------------------------------------------------------
|  Descripción: Abre el archivo binario de estaciones y lo carga| 
|               en memoria en la dirección pasada como parámetro|
|                                                               |
|  Entradas: direccion del registro 'lista de Estaciones'       |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void abrirArchivoEstaciones(L_Estaciones *Estaciones)
{
	FILE *ptr; 
	
	// Compruebo existencia de archivo y nº de registros
	Estaciones->num = NumRegArchivoBin(ESTACIONES_BIN, sizeof(Estacion));
	if(Estaciones->num){
		printf("Numero de estaciones: %d\n", Estaciones->num);

		ptr = fopen(ESTACIONES_BIN, "rb");
		// Creamos un vector de Estacion->num registros de tipo Estacion 
		Estaciones->lista = (Estacion*) calloc(sizeof(Estacion), Estaciones->num);
		if(Estaciones->lista == NULL) {
			printf("No hay memoria suficiente para la lista de estaciones.\n");
			Pausa();
			exit(0);
		}
		fread((Estacion*)Estaciones->lista, sizeof(Estacion), Estaciones->num, ptr);
	}
//	return Estaciones->num;
}

/**-------------------------------------------------------------
|  Funcion: grabarArchivoEstaciones                             |
 ---------------------------------------------------------------
|  Descripción: graba la lista de estaciones en un archivo      | 
|               binario                                         |
|  Entradas: registro 'lista de Estaciones'                     |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void grabarArchivoEstaciones(L_Estaciones Estaciones)
{
	FILE *ptr; 
	int reg;
	
	// Compruebo existencia de registros
	if(Estaciones.num){
		ptr = fopen(ESTACIONES_BIN, "wb");
		reg = fwrite((Estacion*)Estaciones.lista, sizeof(Estacion), Estaciones.num, ptr);
		fclose(ptr);
	}
	else
	{
		printf("La lista esta vacia.\n");
		Pausa();
	}
}



/**-------------------------------------------------------------
|  Funcion: imprimirEstaciones                                  |
 ---------------------------------------------------------------
|  Descripción: Imprime en un archivo de texto las estaciones   |
|               registradas                                     |
|                                                               |
|  Entradas: nada                                               |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void imprimirEstaciones(void)
{
	int np;
	char separa[] = " ---------------------------------------------------------------------------- \n";
	char linea[255];
	FILE *ptr;
	L_Estaciones Estaciones;

	abrirArchivoEstaciones(&Estaciones);

	// abro archivo de texto para escritura
	ptr = fopen(ESTACIONES_TXT, "w");

	fputs(separa, ptr); 

	sprintf(linea, FMT_ESTACIONX, ' ', "ID", "Nombre", "Poblacion", 
		                       "Latitud", "Longitud", ' ');
	fputs(linea, ptr);
	fputs(separa, ptr);

	if (Estaciones.num == 0) {        
		fprintf(ptr,  "%c %-75s %c\n", 5, "La lista de estaciones esta vacia.",5);
	}
	else {
		for (np=0; np < Estaciones.num; np++) {
			fprintf(ptr, FMT_ESTACION, ' ', Estaciones.lista[np].ID, 
				                               Estaciones.lista[np].nombre, 
											   Estaciones.lista[np].localidad,
                                               Estaciones.lista[np].pos.latitud, 
											   Estaciones.lista[np].pos.longitud, ' ');
		}
	}

	fputs(separa, ptr); 
	fclose(ptr);
}

/**-------------------------------------------------------------
|                 Fin del archivo L_Estaciones.c                |
 --------------------------------------------------------------*/
 
