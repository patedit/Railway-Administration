/**-------------------------------------------------------------
|   ARCHIVO: funcionesAds.h                                     |
|---------------------------------------------------------------
|   Contenido: prototipos de las funciones auxiliares           |
|              definidas en el archivo funcionesAds.c           |
|              para la aplicacion de la agencia de viajes       |
 --------------------------------------------------------------*/
#ifndef __FUNCIONESADS_H__
#define __FUNCIONESADS_H__

void abrirArchivoEstacionesSinNumero(L_Estaciones *Estaciones);
void mostrarUnTramo(TipoTramo tramo);
void mostrarUnaEstacion(Estacion estacion);
int validarEstacionViaje(char *ID);
int comprobarNombre(char *ID);
int nodoDestino(ListaNodos nodos, char *IDdestino);
void abrirArchivoTramos(L_Tramos *Tramos);
int calcularDuracionEspera(TipoGrafo *Grafo,ListaArcos Arcos, int source, int destino);

#endif

/**-------------------------------------------------------------
|                   Fin del archivo funcionesAds.h              |
 --------------------------------------------------------------*/
