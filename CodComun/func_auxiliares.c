/**------------------------------------------------------------- 
|   ARCHIVO: func_auxiliares.c                                  |
|---------------------------------------------------------------|
|   Contenido: funciones auxiliares para la aplicacion de       |
|              la agencia de viajes                             |
 --------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#include "func_auxiliares.h"


/**-------------------------------------------------------------
|   FUNCION: NumRegArchivoBin                                   |
|---------------------------------------------------------------|
|   RESE�A: Calcula el numero de registros de tama�o            |
|           tamReg que hay en el archivo BINARIO 'archivo'      |
|                                                               |
|   DEVUELVE:  numero de registros                              |
 --------------------------------------------------------------*/
int NumRegArchivoBin(char *archivo, int tamReg)
{
	FILE *ptr;
	int nbytes, nreg;
	ptr = fopen(archivo, "r");
	if(ptr == NULL) return 0;  // No hay registros

	fseek(ptr, 0, SEEK_END);
	nbytes = ftell(ptr);
	fclose(ptr);

	nreg = nbytes/tamReg;
	return nreg;
}

/*--------------------------------------------------------------
|   FUNCION: leerSiNo                                           |
|---------------------------------------------------------------|
|   RESE�A: muestra un mensaje al usuario solicitando una       |
|       respuesta S o N.                                        |
|                                                               |
|   DEVUELVE: opci�n seleccionada                               |
 --------------------------------------------------------------*/
int leerSiNo(char *mensaje)
{
	int opcion;

	printf("%s ", mensaje);
	do{
		printf("\b");
		opcion = getche();
		opcion = toupper(opcion);
	
	} while( (opcion!='S') && (opcion!='N') );
	printf("\n");
	return opcion;
}

/*--------------------------------------------------------------
|   FUNCION: Pausa()                                            |
 ---------------------------------------------------------------
|   RESE�A: Espera ENTER, despu�s retorna.                      |
|                                                               |
|   DEVUELVE:  void.                                            |
---------------------------------------------------------------*/
void Pausa()
{
   printf( "\nTeclee <ENTER> para continuar.\n\n");
   getchar();    
}

/*--------------------------------------------------------------
|   FUNCION: cabeceraTabla                                      |
 ---------------------------------------------------------------
|   RESE�A: Escribe en pantalla el t�tulo recibido como         |
|           par�metro, con un determinado formato               |
|                                                               |
|   DEVUELVE:  void.                                            |
 --------------------------------------------------------------*/
void cabeceraTabla(char *titulo)
{
	int margen1, margen2;
	size_t i,j;
	char *cadena, salida[81];

	cadena = (char*)malloc(strlen(titulo)+1 );

	strcpy(cadena, titulo);

	ponerAcentos(cadena);

	margen1 = (int)( 0.5*(77-strlen(titulo) ) );
	margen2 = 77-strlen(titulo)-margen1;

	salida[0] = (char)201; for(j=1;j<78;j++) salida[j] = (char)205; 
	salida[78] = (char)187; salida[79]=0;
	printf("%s\n", salida);

	salida[0]= (char)186; for(j=1;j<79;j++) salida[j] = ' '; 
	for(j=margen1,i=0; i<strlen(cadena); i++,j++)
		salida[j] = cadena[i];
	salida[78] = (char) 186;  salida[79]=0;
	printf("%s\n", salida);

	salida[0] = (char)200; for(j=1;j<78;j++) salida[j] = (char)205; 
	salida[78] = (char)188;
	printf("%s\n", salida);
}

/*--------------------------------------------------------------
|   FUNCION: leerOpcionValida()                                 |
|---------------------------------------------------------------
|   RESE�A: muestra un mensaje al usuario solicitando un        | 
|       valor entero,                                           |
|                                                               |
|   DEVUELVE: opci�n seleccionada                               |
 --------------------------------------------------------------*/
int leerOpcionValida(char *mensaje, char num)
{
	int opcion;

	printf("%s", mensaje);
	fflush(stdin);
	do{
		printf("\b");  // el cursor retrocede una posicion
		opcion = getche(); // lee un caracter
		opcion = toupper(opcion); // pasa a may�sculas el caracter le�do
		if(opcion==13) { // retorno de carro
			printf("\b");
			printf("%s", mensaje); 
		}
	
	} while( (opcion<'0') || (opcion>num) );
	printf("\n");
	return opcion-48;
}

/*--------------------------------------------------------------
|   FUNCION: leerOpcionRango()                                  |     
 ---------------------------------------------------------------
|   RESE�A: muestra un mensaje al usuario solicitando un        | 
|       valor entero, que debe estar comprendido entre dos      |
|	valores (inferior y superior)                               |
|   PARAMETROS:                                                 |
|       mensaje: pregunta que se muestra al usuario             |
|        opc1:   valor inferior                                 |
|        opc2:   valor superior                                 |
|                                                               |
|   DEVUELVE: opci�n elegida                                    |
 --------------------------------------------------------------*/
int leerOpcionRango(char *mensaje, char opc1, char opc2)
{
	int opcion;

	printf("%s", mensaje);
	do{
		printf("\b");      // el cursor retrocede un lugar
		opcion = getche(); // lee un caracter 
		opcion = toupper(opcion); // pasa a may�sculas el caracter le�do
	
	} while( (opcion!=opc1) && (opcion!=opc2) );
	printf("\n");
	return opcion;
}

/*--------------------------------------------------------------
|   FUNCION: ponerAcentos                                       |
 ---------------------------------------------------------------
|   RESE�A: cambia las vocales acentuadas por valores ASCII     |
|           adecuados para su correcta visualizaci�n            |
|   Entrada: direcci�n de la cadena que se quiere acentuar      |
|                                                               |
|   DEVUELVE:  void.                                            |
 --------------------------------------------------------------*/
void ponerAcentos(char *cadena)
{
	char car;
	int i;

	for(i=0;i<(int)strlen(cadena);i++) {
		car = cadena[i];
		switch(car){
			case -31: // �
				car = (char) 160;
				break;
			case -23: // �
				car = (char) 130;
				break;
			case -19: // �
				car = (char) 161;
				break;
			case -13: // �
				car = (char) 162;
				break;
			case -6: // �
				car = (char) 163;
				break;
			case -65: // �
				car = (char) 168;
				break;
			case '�': // �, -15
				car = (char) 164;
				break;
		}
		cadena[i] = car;
	} // fin for
}
/*--------------------------------------------------------------
|   FUNCION: comienzoTabla                                      |
 ---------------------------------------------------------------
|   RESE�A: imprime la linea de comienzo de una tabla,          |
|           utilizando caracteres ASCII                         |
|   Entrada: ninguna                                            |
|   DEVUELVE:  nada                                             |
 --------------------------------------------------------------*/
void comienzoTabla(void)
{
	char linea[80];
	int i;
	linea[0] = (char)218; for(i=1;i<78;i++) linea[i] = (char)196; 
	linea[78]= (char)191; linea[79]=0;
	puts(linea);
}
/*--------------------------------------------------------------
|   FUNCION: finTabla                                           |
 ---------------------------------------------------------------
|   RESE�A: imprime la linea de fin de una tabla,               |
|           utilizando caracteres ASCII                         |
|   Entrada: ninguna                                            |
|   DEVUELVE:  nada                                             |
 --------------------------------------------------------------*/
void finTabla(void)
{
	char linea[80];
	int i;
	linea[0] =(char) 192; for(i=1;i<78;i++) linea[i] = (char)196; 
	linea[78]=(char) 217; linea[79]=0;
	puts(linea);
}

/**-------------------------------------------------------------
|                   Fin del archivo func_auxiliares.c           |
 --------------------------------------------------------------*/
 
