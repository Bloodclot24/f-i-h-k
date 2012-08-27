#ifndef UTILS__H_
#define UTILS__H_
#include <iostream>
#include <string>

/*
 * Definicion de tipos de target utilizados por el xml
 */
#define TARGET_NAME "name"
#define TARGET_POS_X "x"
#define TARGET_POS_Y "y"
#define TARGET_TYPE "type"
#define TARGET_ID "id"
#define TARGET_VACIO "NULL"
#define TARGET_CANT_ENTRADAS "cantidadEntradas"
#define TARGET_CANT_SALIDAS "cantidadSalidas"
#define TARGET_SIZE_X "sizex"
#define TARGET_SIZE_Y "sizey"
#define TARGET_ENTITY "entidad"
#define TARGET_ATTRIBUTE "atributo"
#define TARGET_RELATION "relacion"
#define TARGET_COMPOSITEATTRIBUTE "at_compuesto"
#define TARGET_SUBDIAGRAM "diagrama"
#define TARGET_VIA "rol"
#define TARGET_FORK "jerarquia"
#define TARGET_PUNTO "Punto"
#define TARGET_EXPRESSION "expression"
#define TARGET_ID_0 "id0"
#define TARGET_ID_1 "id1"
#define TARGET_ID_2 "id2"

/**
 * Clase utilizada durante la persistencia para transformar
 * tipos de datos
 */
class Utils {

public:
	int convertToInt (const std::string & cadena);

	unsigned convertToUnsigned (const std::string & cadena);

	std::string convertToString(int numero);

};

#endif /* UTILS__H_ */
