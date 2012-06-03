/**-------------------------------------------------------------
|   ARCHIVO: Hora.h                                             |
 ---------------------------------------------------------------
|   Contenido: declaración del TAD Hora y de los                |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
#ifndef __HORA_H__
#define __HORA_H__

/**-------------------------------------------------------------
|  TAD:   sHora                                                 |
|  Alias: Hora                                                  |
 ---------------------------------------------------------------
|  Descripción: almacena las horas de salida y de llegada       |
|                                                               |
|  Atributos:                                                   |
|     horas: horas                                              |
|     minutos: minutos                                          |
|                                                               |
|  Funciones asociadas: ver prototipos                          |
 --------------------------------------------------------------*/
struct sHora 
{
   int horas;   // horas
   int minutos; // minutos
};

typedef struct sHora Hora;

/**-------------------------------------------------------------
|  Funciones asociadas al TAD Hora                              |
 --------------------------------------------------------------*/


#endif

/**-------------------------------------------------------------
|                     Fin del archivo Hora.h                    |
 --------------------------------------------------------------*/
 
