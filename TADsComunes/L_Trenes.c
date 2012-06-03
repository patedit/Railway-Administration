#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "L_Trenes.h"
#include "Tramo.h"
#include "../CodComun/func_auxiliares.h"


/**-------------------------------------------------------------
|   FUNCION: validarHora                                        |
|---------------------------------------------------------------|
|   RESEÑA: Busca si la hora esta bien o no                     |
|                                                               |
|   DEVUELVE:  si la hora esta bien                             |
 --------------------------------------------------------------*/
void validarHora(int *horas, int *minutos)
{
  if(horas<0 || horas>23)
  {
             printf("\n\nHora NO valida. Revisa la Hora\n");
             Pausa();
             getchar();
             mantenimientoTrenes();
  }
  if(minutos<0 || minutos>59)
  {
             printf("Hora no valida. Revisa los minutos\n\n");
             Pausa();
             getchar();
             mantenimientoTrenes();
  }             
}

/**-------------------------------------------------------------
|  Funcion: abrirArchivoTrenesSinNumero                        |
 ---------------------------------------------------------------
|  Descripción: Abre el archivo binario de trenes y lo carga    | 
|               en memoria en la dirección pasada como parámetro|
|                                                               |
|  Entradas: direccion del registro 'lista de Trenes'           |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void abrirArchivoTrenesSinNumero(L_Trenes *Trenes)
{
	FILE *ptr; 
	
	// Compruebo existencia de archivo y nº de registros
	Trenes->num = NumRegArchivoBin(TRENES_BIN, sizeof(Tren));
	if(Trenes->num){
		ptr = fopen(TRENES_BIN, "rb");
		// Creamos un vector de Trenes->num registros de tipo Tren 
		Trenes->lista = (Tren*) calloc(sizeof(Tren), Trenes->num);
		if(Trenes->lista == NULL) {
			printf("No hay memoria suficiente para la lista de trenes.\n");
			Pausa();
			exit(0);
		}
		fread((Tren*)Trenes->lista, sizeof(Tren), Trenes->num, ptr);
	}
//	return Trenes->num;
}

/**-------------------------------------------------------------
|  Funcion: abrirArchivoTrenes                                  |
 ---------------------------------------------------------------
|  Descripción: Abre el archivo binario de trenes y lo carga    | 
|               en memoria en la dirección pasada como parámetro|
|                                                               |
|  Entradas: direccion del registro 'lista de Trenes'           |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void abrirArchivoTrenes(L_Trenes *Trenes)
{
	FILE *ptr; 
	
	// Compruebo existencia de archivo y nº de registros
	Trenes->num = NumRegArchivoBin(TRENES_BIN, sizeof(Tren));
	if(Trenes->num){
		printf("Numero de trenes: %d\n", Trenes->num);

		ptr = fopen(TRENES_BIN, "rb");
		// Creamos un vector de Trenes->num registros de tipo Tren 
		Trenes->lista = (Tren*) calloc(sizeof(Tren), Trenes->num);
		if(Trenes->lista == NULL) {
			printf("No hay memoria suficiente para la lista de trenes.\n");
			Pausa();
			exit(0);
		}
		fread((Tren*)Trenes->lista, sizeof(Tren), Trenes->num, ptr);
	}
//	return Trenes->num;
}

/**-------------------------------------------------------------
|  Funcion: grabarArchivoTrenes                                 |
 ---------------------------------------------------------------
|  Descripción: graba la lista de trenes en un archivo          | 
|               binario                                         |
|  Entradas: registro 'lista de Trenes'                         |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void grabarArchivoTrenes(L_Trenes Trenes)
{
	FILE *ptr; 
	int reg;
	
	// Compruebo existencia de registros
	if(Trenes.num){
		ptr = fopen(TRENES_BIN, "wb");
		reg = fwrite((Tren*)Trenes.lista, sizeof(Tren), Trenes.num, ptr);
		fclose(ptr);
	}
	else
	{
		printf("La lista esta vacia.\n");
		Pausa();
	}
}
/**-------------------------------------------------------------
|  Funcion: mostrarTodosTrenes                                  |
 ---------------------------------------------------------------
|  Descripción: Lista todos los trenes registrados              |
|                                                               |
|  Entradas: vector de registros de tipo Tren                   |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void mostrarTodosTrenes_v2(void)
{
     char ID[8];
	// Variables locales
	int np, j;
	char linea[255];
	L_Trenes Trenes;
    int encontrado=0;
	// Compruebo existencia de archivo y nº de registros
	Trenes.num = NumRegArchivoBin(TRENES_BIN, sizeof(Tren));
	if(!Trenes.num){
		printf( "La lista de trenes esta vacia. \n");
		Pausa();
		return; // salimos de la función
	}
	
	// Cargamos los datos desde el archivo
	abrirArchivoTrenes(&Trenes);

	system("cls");
	cabeceraTabla("Listado de Trenes");

	comienzoTabla();

	sprintf(linea, FMT_TRENX, 179, "ID", "Tren", "Tipo", 
		                       "Origen", "Destino", "Hora Sal.", "Hora Lleg.", "Precio", 179);
	printf("%s", linea);
	linea[0] = (char)195; for(j=1;j<78;j++) linea[j] = (char)196; linea[78]=(char)180; linea[79]=0;
	printf("%s\n", linea);

	if (Trenes.num == 0) {        
		printf("%c %-75s %c\n", 179, "La lista de trenes esta vacia.",179);
	}
	else {
		for (np=0; np < Trenes.num; np++) {
			mostrarTren(Trenes.lista[np]);
		}
	}
	finTabla();
	Pausa();
}

/**-------------------------------------------------------------
|  Funcion: mostrarTodosTrenes                                  |
 ---------------------------------------------------------------
|  Descripción: Lista todos los trenes registrados              |
|                                                               |
|  Entradas: vector de registros de tipo Tren                   |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void mostrarTodosTrenes(void)
{
     char ID[8];
	// Variables locales
	int np, j;
	char linea[255];
	L_Trenes Trenes;
    int encontrado=0;
	// Compruebo existencia de archivo y nº de registros
	Trenes.num = NumRegArchivoBin(TRENES_BIN, sizeof(Tren));
	if(!Trenes.num){
		printf( "La lista de trenes esta vacia. \n");
		Pausa();
		return; // salimos de la función
	}
	
	// Cargamos los datos desde el archivo
	abrirArchivoTrenes(&Trenes);

	system("cls");
	cabeceraTabla("Listado de Trenes");

	comienzoTabla();

	sprintf(linea, FMT_TRENX, 179, "ID", "Tren", "Tipo", 
		                       "Origen", "Destino", "Hora Sal.", "Hora Lleg.", "Precio", 179);
	printf("%s", linea);
	linea[0] = (char)195; for(j=1;j<78;j++) linea[j] = (char)196; linea[78]=(char)180; linea[79]=0;
	printf("%s\n", linea);

	if (Trenes.num == 0) {        
		printf("%c %-75s %c\n", 179, "La lista de trenes esta vacia.",179);
	}
	else {
		for (np=0; np < Trenes.num; np++) {
			mostrarTren(Trenes.lista[np]);
		}
	}
	finTabla();
	printf("\n\nPresione <RETURN> para volver al menu anterior o bien introduzca la ID del \ntren del que desea mostrar la ruta: "); fflush(stdin); gets(ID);
	// compruebo si la cadena contiene algun codigo
	if(strlen(ID)==0)
	{
		return;
	}
	
	for(np=0;np<Trenes.num;np++)
	{
	     if(strcmp(Trenes.lista[np].ID, ID) ==0) encontrado =1; //los ID coinciden encontrado=1,
    }
 
    if(!encontrado) {printf("\n\nEl ID NO es valido\n\n"); Pausa();}
    else mostrarTramo(ID);

}

/**-------------------------------------------------------------
|  Funcion: imprimirTrenes                                      |
 ---------------------------------------------------------------
|  Descripción: Imprime en un archivo de texto los trenes       |
|               registrados                                     |
|                                                               |
|  Entradas: nada                                               |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void imprimirTrenes(void)
{
	int np;
	char separa[] = " ----------------------------------------------------------------------------- \n";
	char linea[255];
	FILE *ptr;
	L_Trenes Trenes;

	abrirArchivoTrenes(&Trenes);

	// abro archivo de texto para escritura
	ptr = fopen(TRENES_TXT, "w");

	fputs(separa, ptr); 

	sprintf(linea, FMT_TRENX, ' ', "ID", "Estacion", "Tipo", 
		                       "Origen", "Destino", "Hora Sal.", "Hora LLeg.", "Precio", ' ');
	fputs(linea, ptr);
	fputs(separa, ptr);

	if (Trenes.num == 0) {        
		fprintf(ptr,  "%c %-75s %c\n", 5, "La lista de trenes esta vacia.",5);
	}
	else {
		for (np=0; np < Trenes.num; np++) {
			fprintf(ptr, FMT_TREN, ' ', Trenes.lista[np].ID, 
				                               Trenes.lista[np].nombre, 
											   Trenes.lista[np].tipo,
                                               Trenes.lista[np].origen, 
											   Trenes.lista[np].destino,
                                               Trenes.lista[np].salida.horas,
                                               Trenes.lista[np].salida.minutos,
                                               Trenes.lista[np].llegada.horas,
                                               Trenes.lista[np].llegada.minutos,
                                               Trenes.lista[np].precio, ' ');
		}
	}

	fputs(separa, ptr); 
	fclose(ptr);
}


/**-------------------------------------------------------------
|  Funcion: eliminarTren                                        |
 ---------------------------------------------------------------
|  Descripción: elimina un tren de la lista                     |
|                                                               |
|  Entradas: los datos se leen del archivo                      |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void eliminarTren(void)
{
     
	int i, encontrado;
	char codigo[10];
	char archivo[50];
    char archivo2[50];
	int eleccion;
	char opcion; 
	L_Trenes trenes;

	// Compruebo existencia de archivo y nº de registros
	trenes.num = NumRegArchivoBin(TRENES_BIN, sizeof(Tren));

	if(!trenes.num){
		printf( "La lista de trenes esta vacia. \n");
		Pausa();
		return;
	}

	// hay paradass registradas
	system("cls");
	cabeceraTabla("Eliminar un tren");
	abrirArchivoTrenes(&trenes);
	
	mostrarTodosTrenes_v2();
	
	printf("Indique el codigo del tren que quiere eliminar: ");
	gets(codigo);
	i= 0;
	encontrado = 0;

	while(i<trenes.num && !encontrado)
	{
		if( strcmp(trenes.lista[i].ID, codigo) == 0) // si el codigo del tren coincide
		{
			encontrado = 1; // hemos encontrado el tren a borrar
		}
		else i++;
	}
	if(encontrado)
	{
		eleccion = i;
		printf("Ha seleccionado el siguiente tren:\n");
		comienzoTabla();
		mostrarTren(trenes.lista[eleccion]);
		finTabla();
		opcion = leerSiNo("Desea eliminarlo (S/N)?");
		if(opcion == 'S')
		{
          	// borro el archivo ruta correspondiente
            sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", trenes.lista[eleccion].ID);
            sprintf(archivo2, "../BaseDatos/Rutas/%s.lista", trenes.lista[eleccion].ID);
            
            remove(archivo);
            remove(archivo2);
            
			for(i=eleccion;i<trenes.num;i++)
				trenes.lista[i] = trenes.lista[i+1]; // copio el tren i+1 en la i

			trenes.num--;
            
			printf("El tren de codigo %s ha sido borrado\n", codigo);
			grabarArchivoTrenes(trenes);
			imprimirTrenes(); 
		}
		else
		{
			printf("Eliminacion cancelada\n");
			Pausa();
		}
	}
	else // no existe esa estacion
		printf("El codigo seleccionado (%s) no corresponde a ningun tren.\n", codigo);
	Pausa();
}



/**-------------------------------------------------------------
|  Funcion: anadirUnTren                                        |
 ---------------------------------------------------------------
|  Descripción: rellena los campos del registro tren con        |
|               datos leidos del teclado, y añade el nuevo      | 
|               registro al archivo de trenes                   |
|  Entradas: dirección a un registro de tipo Tren               |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void anadirUnTren(void)
{
	Tren tren; // registro para el nuevo tren
	FILE *ptr; // puntero al archivo de datos
	int opcion;
	int nreg; // numero de registros en el archivo de Trenes

	// calculo el numero de trenes almacenados en el 
	// archivo con la funcion numRegArchivoBin
	nreg = NumRegArchivoBin(TRENES_BIN, sizeof(Tren));
	printf("Numero de trenes registrados: %d\n", nreg);

	// Pido los datos del nuevo tren
	anadirTren(&tren);

	// Abro el archivo para AÑADIR (append) el nuevo registro
	ptr = fopen(TRENES_BIN, "ab");
	if(ptr == NULL) {
		printf("El archivo %s no existe.\n", TRENES_BIN);
	}
	fwrite((Tren*)&tren, sizeof(Tren), 1, ptr);
   	fclose(ptr);
	    /* llamo a la funcion imprimirTrenes para generar el 
	   archivo de texto  */
   imprimirTrenes();
}

/**-------------------------------------------------------------
|  Funcion: modificarUnTren                                     |
 ---------------------------------------------------------------
|  Descripción: selecciona un tren y modifica uno de sus        |
|               campos                                          |
|                                                               |
|  Entradas: ninguna                                            |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void modificarUnTren()
{
	int encontrado = 0, i=0;
	char cadena[80]="";
	L_Trenes trenes;

	// Compruebo existencia de archivo y nº de registros
	trenes.num = NumRegArchivoBin(TRENES_BIN, sizeof(Tren));

	if(!trenes.num){
		printf( "La lista de trenes esta vacia. \n");
		Pausa();
		return;
	}

	// hay paradas registradas
	system("cls");
	cabeceraTabla("Actualizar los datos de un tren");
	abrirArchivoTrenes(&trenes);
	
	mostrarTodosTrenes_v2();

	printf("Seleccione codigo del tren \na modificar (pulse <RETURN> para cancelar): ");
	fflush(stdin);  gets(cadena);
	// compruebo si la cadena contiene algun codigo
	if(strlen(cadena)==0)
	{
		printf("Modificacion cancelada\n");
		Pausa();
		return;
	}

	// busqueda del tren correspondiente al codigo tecleado
	i=0;
	while(!encontrado && i<trenes.num) {
		if( strcmp(trenes.lista[i].ID, cadena) == 0) {
			encontrado = 1;
		}
		else i++;
	}
	if(encontrado) {  // se ha encontrado la estacion
		modificarTren(&trenes.lista[i]);
		grabarArchivoTrenes(trenes);

	}
	else{ // no se ha encontrado la estacion
		printf("El tren de codigo %s no esta registrado\n", cadena);
		Pausa();
	}

}



/**-------------------------------------------------------------
|  Funcion: mantenimientoTrenes                                 |
|---------------------------------------------------------------
|  Descripción: selecciona el servicio elegido por el usuario   |
|  Entradas: ninguna                                            |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void mantenimientoTrenes(void)
{

	int opcion;

	while ((opcion = menuMantenimientoTrenes()) != 0) {
		switch (opcion) {
			case 1: // Añadir un nuevo tren
				anadirUnTren();
				break;
			case 2: // Listar todos los trenes
				mostrarTodosTrenes();
				break;			
			case 3: // Modificar datos de un tren
				modificarUnTren();
				break; 
			case 4: // Eliminar un tren
			  	eliminarTren();
				break;
			case 0: // Menu anterior
				break;
		} // fin switch

	} // fin while
}

/**-------------------------------------------------------------
|  Funcion: menuMantenimientoTrenes                             |
 ---------------------------------------------------------------
|  Descripción: Muestra las opciones de mantenimiento:          |
|               1. Añadir un nuevo tren                         |
|               2. Listar todos los trenes                      |
|               3. Actualizar los datos de un tren              |
|               4. Eliminar un tren                             |
|  Entradas: ninguna                                            |
|  Retorno: seleccion del usuario.                              |
 --------------------------------------------------------------*/
int menuMantenimientoTrenes(void)
{
	// Variables locales
	int eleccion=0;

	system("cls");
	cabeceraTabla("Mantenimiento de Trenes");
	
	printf( "1  A\244adir un nuevo tren\n");
	printf( "2  Listar todos los trenes\n");
	printf( "3  Actualizar los datos de un tren\n");
	printf( "4. Eliminar un tren\n");
	printf( "0. Menu anterior.\n\n");

	eleccion = leerOpcionValida("Seleccione opcion:  ", '4');

	return eleccion;
}

/**-------------------------------------------------------------
|                 Fin del archivo L_Trenes.c                    |
 --------------------------------------------------------------*/
