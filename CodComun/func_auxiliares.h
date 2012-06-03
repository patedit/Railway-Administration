/**-------------------------------------------------------------
|   ARCHIVO: func_auxiliares.h                                  |
|---------------------------------------------------------------
|   Contenido: prototipos de las funciones auxiliares           |
|              definidas en el archivo func_auxiliares.c        |
|              para la aplicacion de la agencia de viajes       |
 --------------------------------------------------------------*/
#ifndef __FUNC_AUXILIARES_H__
#define __FUNC_AUXILIARES_H__

void cabeceraTabla(char *titulo);
int  leerSiNo(char *mensaje);
int  leerOpcionValida(char *mensaje, char num);
int  leerOpcionRango(char *mensaje, char opc1, char opc2);
void ponerAcentos(char *cadena);
void Pausa();
void comienzoTabla(void);
void finTabla(void);
int  NumRegArchivoBin(char *archivo, int tamReg);

#endif

/**-------------------------------------------------------------
|                   Fin del archivo func_auxiliares.h           |
 --------------------------------------------------------------*/
 
