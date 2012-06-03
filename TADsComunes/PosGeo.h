/**-------------------------------------------------------------
|   ARCHIVO: PosGeo.h                                           |
 ---------------------------------------------------------------
|   Contenido: declaración del TAD PosGeo y de los              |
|              prototipos de sus funciones asociadas            |
 --------------------------------------------------------------*/
#ifndef __POSGEO_H__
#define __POSGEO_H__
// Constantes para pasar de grados a radianes, y viceversa
#define DEG_RAD 	0.01745329
#define RAD_DEG	    57.29577951

/**-------------------------------------------------------------
|  TAD:   sPosGeo                                               |
|  Alias: PosGeo                                                |
 ---------------------------------------------------------------
|  Descripción: almacena las coordenadas geográficas,           |
|               latitud y longitud                              |
|                                                               |
| Constantes asociadas:                                         |
|     DEG_RAD: constante de conversion de grados a radianes     |
|     RAD_DEG: constante de conversion de radianes a grados     |
|                                                               |
|  Atributos:                                                   |
|     latitud, en grados                                        |
|     longitud, en grados                                       |
|                                                               |
|  Funciones asociadas: ver prototipos                          |
 --------------------------------------------------------------*/
struct sPosGeo {
   double latitud;   // latitud, en grados
   double longitud;  // longitud, en grados
};

typedef struct sPosGeo PosGeo;

/**-------------------------------------------------------------
|  Funciones asociadas al TAD PosGeo                            |
 --------------------------------------------------------------*/
float  distanciaGeodesica(PosGeo p1, PosGeo p2);
void   MostrarPosicion(PosGeo pos);
PosGeo leerPosicion_v1();
void   leerPosicion_v2(PosGeo *);

#endif

/**-------------------------------------------------------------
|                     Fin del archivo PosGeo.h                  |
 --------------------------------------------------------------*/
 
