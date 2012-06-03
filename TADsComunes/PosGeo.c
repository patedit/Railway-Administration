/**-------------------------------------------------------------
|   ARCHIVO: PosGeo.c                                           |
 ---------------------------------------------------------------
|   Contenido: definiciones de las funciones asociadas          |
|               al TAD PosGeo                                   |
 --------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

#include"PosGeo.h"

/**-------------------------------------------------------------
|   FUNCION: mostrarPosicion                                    |
 ---------------------------------------------------------------
|   RESEÑA: muestra por pantalla los datos de posicion          |
|   ENTRADAS: registro PosGeo                                   |
|   DEVUELVE: nada                                              |
 --------------------------------------------------------------*/
void mostrarPosicion(PosGeo pos)
{
     printf("%lf, %lf\n", pos.latitud, pos.longitud);     
}


/**-------------------------------------------------------------
|   FUNCION: leerPosicion_v1                                    |
 ---------------------------------------------------------------
|   RESEÑA: lee datos de posicion desde teclado                 |
|   ENTRADAS: nada                                              |
|   DEVUELVE: registro PosGeo con las coordenadas leidas        |
 --------------------------------------------------------------*/
PosGeo leerPosicion_v1()
{
	PosGeo pos;

	printf("Latitud: ");
	scanf("%lf", &pos.latitud);
	printf("Longitud: ");
	scanf("%lf", &pos.longitud);
	return pos;
}
/**-------------------------------------------------------------
|   FUNCION: leerPosicion_v2                                    |
 ---------------------------------------------------------------
|   RESEÑA: lee datos de posicion desde teclado                 |
|   ENTRADAS: dirección de un registro PosGeo                   |                                           *
|   DEVUELVE: nada                                              |
 --------------------------------------------------------------*/
void leerPosicion_v2(PosGeo *pos)
{
	printf("Latitud: ");
	scanf("%lf", &pos->latitud);
	printf("Longitud: ");
	scanf("%lf", &pos->longitud);
}


/**-------------------------------------------------------------
|   FUNCION: distanciaGeodesica()                               |
 ---------------------------------------------------------------
|   RESEÑA: calcula la distancia entre dos posiciones           |
|   ENTRADAS: coordenadas geográficas de las dos posiciones     |                                           *
|   DEVUELVE: distancia en kilometros                           |
 --------------------------------------------------------------*/
float distanciaGeodesica(PosGeo p1, PosGeo p2)
{
	float dlong, dvalue, dd, km;

	dlong = (float)(p1.longitud - p2.longitud); 
	dvalue = (float)( (sin(p1.latitud * DEG_RAD) * sin(p2.latitud * DEG_RAD)) 
		+ (cos(p1.latitud * DEG_RAD) * cos(p2.latitud * DEG_RAD) 
		* cos(dlong * DEG_RAD)) ); 

	dd = (float) (acos(dvalue) * RAD_DEG );
	km = (dd * 111.302F); 
	return km; 
}

/**-------------------------------------------------------------
|                     Fin del archivo PosGeo.c                  |
 --------------------------------------------------------------*/
 
