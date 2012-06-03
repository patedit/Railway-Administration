#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "L_Tramos.h"
#include "L_Estaciones.h"
#include "Tramo.h"
#include "L_Trenes.h"


#include "../CodComun/func_auxiliares.h"

/**-------------------------------------------------------------
|  Funcion: comprobarNombre                                     |
 ---------------------------------------------------------------*/

int comprobarNombre(char *ID)
{
    L_Estaciones estaciones;
    int np=0, encontrado=0;
   	abrirArchivoEstacionesSinNumero(&estaciones);
   	
   	while(np<estaciones.num && !encontrado)
    {
   	     if(strcmp(estaciones.lista[np].ID,  ID) ==0) encontrado=1;
   	     else np++;
    }
    
    if(encontrado) return np;
}
/**-------------------------------------------------------------
|  Funcion: abrirArchivoRutasSinNumero                          |
 ---------------------------------------------------------------
|  Descripción: Abre el archivo binario de estaciones y lo carga| 
|               en memoria en la dirección pasada como parámetro|
|                                                               |
|  Entradas: direccion del registro 'lista de Estaciones'       |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void abrirArchivoRutasSinNumero(L_Tramos *Tramos,Tren tren)
{
    FILE *ptr; 
    char archivo[50];
	
	// Compruebo existencia de archivo y nº de registros
	sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", tren);
	Tramos->num = NumRegArchivoBin(archivo, sizeof(TipoTramo));
	if(Tramos->num){

		ptr = fopen(archivo, "rb");
		// Creamos un vector de Tramos->num registros de tipo Tramos 
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
|  Funcion: abrirArchivoRutas                                  |
 ---------------------------------------------------------------
|  Descripción: Abre el archivo binario de estaciones y lo carga| 
|               en memoria en la dirección pasada como parámetro|
|                                                               |
|  Entradas: direccion del registro 'lista de Estaciones'       |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void abrirArchivoRutas(L_Tramos *Tramos,Tren tren)
{
    FILE *ptr; 
    char archivo[50];
	
	// Compruebo existencia de archivo y nº de registros
	sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", tren);
	Tramos->num = NumRegArchivoBin(archivo, sizeof(TipoTramo));
	if(Tramos->num){
		printf("Numero de tramos: %d\n", Tramos->num);

		ptr = fopen(archivo, "rb");
		// Creamos un vector de Tramos->num registros de tipo Tramos 
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
|  Funcion: eliminarUnTramo                                     |
 ---------------------------------------------------------------
|  Descripción: elimina un tramo de la lista                    |
|                                                               |
|  Entradas: los datos se leen del archivo                      |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void eliminarUnTramo(Tren tren)
{
    FILE *ptr; 
	int i,i1, est1, est2,encontrado1,encontrado, duracionMin, duracionHor,np,var1,duracionTren;
	char cadena[10];
	char archivo[50];
	int eleccion;
	char opcion; 
	L_Tramos tramos;
	L_Estaciones estaciones;

	// Compruebo existencia de archivo y nº de registros
	sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", tren);
	tramos.num = NumRegArchivoBin(archivo, sizeof(TipoTramo));

	if(!tramos.num){
		printf( "La lista de tramos esta vacia. \n");
		Pausa();
		return;
	}

	// hay paradass registradas
	system("cls");
	cabeceraTabla("Eliminar un tramo");
	abrirArchivoRutas(&tramos,tren);
	
	mostrarTramo(tren);
	printf("Asociacion de nombre con su ID:\n");
	abrirArchivoEstacionesSinNumero(&estaciones);
    for (np=0; np < tramos.num; np++) {
            var1 = comprobarNombre(tramos.lista[np].IDorigen);
            printf("\t%d. %s - (%s%)\n", np, estaciones.lista[var1].nombre,tramos.lista[np].IDorigen);

		}
	printf("\nEscriba la ID de la estacion de origen del tramo que quiere eliminar: ");
	gets(cadena);
	i= 0;
	encontrado = 0;

	while(i<tramos.num && !encontrado)
	{
		if( strcmp(tramos.lista[i].IDorigen, cadena) == 0) // si el codigo de la estacion coincide
		{
			encontrado = 1; // hemos encontrado la estacion a borrar
		}
		else i++;
	}
	if(encontrado)
	{
		eleccion = i;
		printf("Ha seleccionado el siguiente tramo:\n");
		comienzoTabla();
		mostrarUnTramo(tramos.lista[eleccion]);
		finTabla();
		opcion = leerSiNo("Desea eliminarlo (S/N)?");
		if(opcion == 'S')
		{
            // Recalculamos IDdestino de la anterior ID, la hora..precio..duracion..distancia..
            tramos.lista[i-1].fin.horas = tramos.lista[i].fin.horas;
            tramos.lista[i-1].fin.minutos = tramos.lista[i].fin.minutos;
            strcpy(tramos.lista[i-1].IDdestino, tramos.lista[i+1].IDorigen);
            // Calculamos la duracion del tramo
            if(tramos.lista[i-1].inicio.minutos > tramos.lista[i-1].fin.minutos)
         	{
                             duracionHor = (((tramos.lista[i-1].fin.horas) - (tramos.lista[i-1].inicio.horas))-1)*60;
                             duracionMin = ((60-tramos.lista[i-1].inicio.minutos)+tramos.lista[i-1].fin.minutos);
            }
            else 
            {
               duracionHor = (tramos.lista[i-1].fin.horas - tramos.lista[i-1].inicio.horas)*60;  // En minutos
    
               duracionMin = tramos.lista[i-1].fin.minutos - tramos.lista[i-1].inicio.minutos;
               if(duracionMin<0) duracionMin = -(duracionMin);     // Cambiamos el signo si fuera negativo
    
               if(duracionHor<0) duracionHor = -(duracionHor);
            }
            tramos.lista[i-1].duracion = duracionMin + duracionHor;
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
            //Recalculamos el precio
            tramos.lista[i-1].precio = ((tramos.lista[i-1].duracion) * (tren.precio/duracionTren));
            // Calculamos la distancia, abriendo las estaciones
   	        abrirArchivoEstaciones(&estaciones);
   	        // aqui buscamos la estacion que corresponde con la ID
   	        encontrado1=0;
   	        i1=0;
            while(i1<estaciones.num && !encontrado1)
            {
                           if(strcmp(estaciones.lista[i1].ID, tramos.lista[i-1].IDorigen)==0) encontrado1=1; //encontro
                           else i1++;
            }
            est1 = i1; //copiamos
            i1=0;
            encontrado1=0;
            while(i1<estaciones.num && !encontrado1)
            {
                                    if(strcmp(estaciones.lista[i1].ID, tramos.lista[i-1].IDdestino)==0) encontrado1=1;
                                    else i1++;
            }
            est2 = i1;
            tramos.lista[i-1].distancia = distanciaGeodesica(estaciones.lista[est1].pos, estaciones.lista[est2].pos);
			for(i=eleccion;i<tramos.num;i++)
 
				tramos.lista[i] = tramos.lista[i+1]; // copio el tramo i+1 en la i

			tramos.num--;
			
			printf("El tramo ha sido borrado\n"); Pausa();

		ptr = fopen(archivo, "wb");
		fwrite((TipoTramo*)tramos.lista, sizeof(TipoTramo), tramos.num, ptr);
		fclose(ptr);
		imprimirTramos(tren); 
		}
		else
		{
			printf("Eliminacion cancelada\n");
			Pausa();
		}
	}
	else // no existe esa estacion
		printf("El codigo seleccionado (%s) no corresponde a ningun tramo.\n", cadena);
	Pausa();
}

/**-------------------------------------------------------------
|  Funcion: mostrarTramo                                        |
 ---------------------------------------------------------------
|  Descripción: Lista el tramo                                  |
|                                                               |
|  Entradas: nada                                               |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void mostrarTramo(Tren ID)
{
	// Variables locales
	int np, j,var1,var2;
	char linea[255];
	L_Tramos Tramos;
	L_Estaciones estaciones;
	char archivo[50];

	// Compruebo existencia de archivo y nº de registros
	sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", ID);
	Tramos.num = NumRegArchivoBin(archivo, sizeof(TipoTramo));
	if(!Tramos.num){
		printf( "La lista de tramos esta vacia. \n");
		Pausa();
		return; // salimos de la función
	}
	
	// Cargamos los datos desde el archivo
	abrirArchivoRutasSinNumero(&Tramos, ID);
	abrirArchivoEstacionesSinNumero(&estaciones);

    printf("\n\n");
	cabeceraTabla("Listado de Tramos");

	comienzoTabla();

	sprintf(linea, FMT_TRAMOX2, 179, "ID", "Origen", "Destino", 
		                       "Inicio", "Fin", "Precio", 179);
	printf("%s", linea);
	linea[0] = (char)195; for(j=1;j<78;j++) linea[j] = (char)196; linea[78]=(char)180; linea[79]=0;
	printf("%s\n", linea);

	if (Tramos.num == 0) {        
		printf("%c %-75s %c\n", 179, "La lista de tramos esta vacia.",179);
	}
	else {
		for (np=0; np < Tramos.num; np++) {
            var1 = comprobarNombre(Tramos.lista[np].IDorigen);
            var2 = comprobarNombre(Tramos.lista[np].IDdestino);
            printf(FMT_TRAMO2, 179, Tramos.lista[np].ID, estaciones.lista[var1].nombre, 
                                    estaciones.lista[var2].nombre,Tramos.lista[np].inicio.horas,
                                    Tramos.lista[np].inicio.minutos,Tramos.lista[np].fin.horas,
                                    Tramos.lista[np].fin.minutos, Tramos.lista[np].precio, 179);

		}
	}
	finTabla();
	Pausa();



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
void imprimirTramos(Tren tren)
{
     
    FILE *ptr;
	L_Estaciones estaciones;
	int encontrado = 0;
	int np;
	char separa[] = " ------------------------------------------------------------------------------------------------------------------ \n";
	char linea[255];
	int var1,var2;

	L_Tramos Tramos;
	char archivo[50];

	abrirArchivoRutas(&Tramos, tren);
	abrirArchivoEstacionesSinNumero(&estaciones);

	// abro archivo de texto para escritura
	sprintf(archivo, "../BaseDatos/Rutas/%s.lista", tren);
	ptr = fopen(archivo, "w");

	fputs(separa, ptr); 

	sprintf(linea, FMT_TRAMOX, ' ', "ID", "Origen", "Destino", "Inicio", 
		                       "Fin", "Duracion", "Distancia", "Precio", ' ');
	fputs(linea, ptr);
	fputs(separa, ptr);


	if (Tramos.num == 0) {        
		fprintf(ptr,  "%c %-75s %c\n", 5, "La lista de tramos esta vacia.",5);
	}
        
	else {
		for (np=0; np < Tramos.num; np++) {
            var1 = comprobarNombre(Tramos.lista[np].IDorigen);
            var2 = comprobarNombre(Tramos.lista[np].IDdestino);
			fprintf(ptr, FMT_TRAMO, ' ', Tramos.lista[np].ID, 
                                               estaciones.lista[var1].nombre, 
				                               estaciones.lista[var2].nombre, 
											   Tramos.lista[np].inicio.horas,
                                               Tramos.lista[np].inicio.minutos, 
											   Tramos.lista[np].fin.horas,
                                               Tramos.lista[np].fin.minutos,
                                               Tramos.lista[np].duracion,
                                               Tramos.lista[np].distancia,
                                               Tramos.lista[np].precio, ' ');
   
		}
	}
	fclose(ptr);

}
/**-------------------------------------------------------------
|  Funcion: imprimirTodosTramos                                 |
 ---------------------------------------------------------------
|  Descripción: Imprime todos los tramos en tramos.lista        |
|                                                               |
|  Entradas: nada                                               |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/
void imprimirTodosTramos()
{
     
    FILE *ptr;
    FILE *ptr1;
	L_Estaciones estaciones;
	int encontrado = 0;
	int np,i;
	char separa[] = " ------------------------------------------------------------------------------------------------------------------ \n";
	char linea[255];
	int var1,var2;
    L_Trenes Trenes;
	L_Tramos Tramos;
	char archivo[50];

	abrirArchivoEstacionesSinNumero(&estaciones);
    abrirArchivoTrenesSinNumero(&Trenes);
	// abro archivo de texto para escritura
	ptr = fopen("../BaseDatos/tramos.lista", "w");

	fputs(separa, ptr); 

	sprintf(linea, FMT_TRAMOX, ' ', "ID", "Origen", "Destino", "Inicio", 
		                       "Fin", "Duracion", "Distancia", "Precio", ' ');
	fputs(linea, ptr);
	fputs(separa, ptr);
   
    for(i=0;i<Trenes.num;i++)
      {
                               sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", Trenes.lista[i].ID);
                               Tramos.num = NumRegArchivoBin(archivo, sizeof(TipoTramo));
                               ptr1 = fopen(archivo, "rb");
                               // Creamos un vector de Tramos->num registros de tipo Tramos 
                               Tramos.lista = (TipoTramo*) calloc(sizeof(TipoTramo), Tramos.num);
		                         if(Tramos.lista == NULL) {
			                             printf("No hay memoria suficiente para la lista de tramos.\n");
			                             Pausa();
		                                 exit(0);
	                              }
		                        fread((TipoTramo*)Tramos.lista, sizeof(TipoTramo), Tramos.num, ptr1);
         
		for (np=0; np < Tramos.num; np++) {
            var1 = comprobarNombre(Tramos.lista[np].IDorigen);
            var2 = comprobarNombre(Tramos.lista[np].IDdestino);
			fprintf(ptr, FMT_TRAMO, ' ', Tramos.lista[np].ID, 
                                               estaciones.lista[var1].nombre, 
				                               estaciones.lista[var2].nombre, 
											   Tramos.lista[np].inicio.horas,
                                               Tramos.lista[np].inicio.minutos, 
											   Tramos.lista[np].fin.horas,
                                               Tramos.lista[np].fin.minutos,
                                               Tramos.lista[np].duracion,
                                               Tramos.lista[np].distancia,
                                               Tramos.lista[np].precio, ' ');
   fwrite((TipoTramo*)Tramos.lista, sizeof(TipoTramo), Tramos.num, ptr1);
		}
	}
	Pausa();
	fclose(ptr1);
	fclose(ptr);

}  
     
/**-------------------------------------------------------------
|  Funcion: anadirUnTramo                                       |
 ---------------------------------------------------------------
|  Descripción: inserta una parada en la ruta                   |
|                                                               |
|  Entradas: TAD tramo                                          |
|  Retorno: nada                                                |
 --------------------------------------------------------------*/

void anadirUnTramo(Tren tren)
{
    TipoTramo tramo; // registro para la nueva parada
	FILE *ptr; // puntero al archivo de datos
	char archivo[50];
	int nreg; // numero de registros en el archivo de Tramos

	// calculo el numero de tramos almacenados en el 
	// archivo con la funcion numRegArchivoBin
	sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", tren);

	// Pido los datos del nuevo tramo
	getchar();
	anadirTramo(&tramo, tren);

	// Abro el archivo para AÑADIR (append) el nuevo registro
	ptr = fopen(archivo, "ab");
	if(ptr == NULL) {
		printf("El archivo %s no existe.\n", archivo);
	}
	fwrite((TipoTramo*)&tramo, sizeof(TipoTramo), 1, ptr);
	fclose(ptr);
	imprimirTramos(tren);

}
/**-------------------------------------------------------------
|  Funcion: eliminarTramo                                       |
 ---------------------------------------------------------------
|  Entradas: ninguna                                            |
|  Retorno: seleccion del usuario.                              |
 --------------------------------------------------------------*/
void eliminarTramo(Tren tren)
{
       char archivo[50], archivo2[50];
       char opcion;
       L_Tramos Tramos;
       sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", tren);
       sprintf(archivo2, "../BaseDatos/Rutas/%s.lista", tren);
       Tramos.num = NumRegArchivoBin(archivo, sizeof(TipoTramo));
	  if(!Tramos.num){
		printf( "La lista de tramos esta vacia. \n");
		Pausa();
		getchar();
		return; // salimos de la función
	}
        mostrarTramo(tren);
        printf("\n\nVa a borrar TODOS los tramos del tren: %s\n", tren);
        opcion = leerSiNo("Desea continuar (S/N)?");
		if(opcion == 'S')
		{
			remove(archivo);
			remove(archivo2);
		}
		else
		{
			printf("Eliminacion cancelada\n");
			Pausa();
		}
}

/**-------------------------------------------------------------
|  Funcion: generarTramo                                       |
 ---------------------------------------------------------------
|  Entradas: ninguna                                            |
|  Retorno: seleccion del usuario.                              |
 --------------------------------------------------------------*/
 void generarTramos()
 {
      FILE *ptr;
      FILE *ptr1;
      int i;
      char archivo[50];
      L_Trenes Trenes;
      L_Tramos Tramos;
      abrirArchivoTrenes(&Trenes);
      ptr1 = fopen("../BaseDatos/tramos.dat", "wb");
      for(i=0;i<Trenes.num;i++)
      {
                               sprintf(archivo, "../BaseDatos/Rutas/%s.ruta", Trenes.lista[i].ID);
                               Tramos.num = NumRegArchivoBin(archivo, sizeof(TipoTramo));
	                           if(Tramos.num){

                                 ptr = fopen(archivo, "rb");
		                         // Creamos un vector de Tramos->num registros de tipo Tramos 
		                         Tramos.lista = (TipoTramo*) calloc(sizeof(TipoTramo), Tramos.num);
		                         if(Tramos.lista == NULL) {
			                             printf("No hay memoria suficiente para la lista de tramos.\n");
			                             Pausa();
		                                 exit(0);
	                              }
		                        fread((TipoTramo*)Tramos.lista, sizeof(TipoTramo), Tramos.num, ptr);
	                             }
                                printf("\nNumero de tramos en %s.ruta: %d\n", Trenes.lista[i].ID, Tramos.num);                             
                               fwrite((TipoTramo*)Tramos.lista, sizeof(TipoTramo), Tramos.num, ptr1);
        }
        imprimirTodosTramos();
        fclose(ptr1);
 }
      
 
 
/**-------------------------------------------------------------
|  Funcion: actualizarRuta                                      |
 ---------------------------------------------------------------
|  Descripción: Muestra las opciones del menu principal:        |
|               1. Insertar parada                              |
|               2. Eliminar parada                              |
|               3. Eliminar tramo                               |
|               0. Menu anterior                                |
|  Entradas: ninguna                                            |
|  Retorno: seleccion del usuario.                              |
 --------------------------------------------------------------*/
void actualizarRuta(Tren tren)
{
    int opcion;
    
   	system("cls");
	cabeceraTabla("Actualizar datos de la RUTA");
	printf( "1  Insertar una nueva parada.\n");
	printf( "2  Eliminar una parada.\n");
	printf( "3. Eliminar todos los tramos.\n");
	printf( "0. Menu anterior.\n\n");
	printf("Selecciona opcion y pulsa <RETURN>: ");
    scanf("%d", &opcion);
    
	switch (opcion) {
			case 1: // Insertar una parada
				anadirUnTramo(tren);
				break;			
			case 2: // Eliminar una parada
				eliminarUnTramo(tren);
                break;
            case 3: // Eliminar todo el tramo
                eliminarTramo(tren);
			case 0: // Menu anterior
				break;
	}
}

