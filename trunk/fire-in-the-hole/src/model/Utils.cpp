#include "model/Utils.h"
#include <iostream>
#include <string>
#include <sstream>

int Utils::convertToInt (const std::string & cadena){
	int numero;
	std::istringstream buffer(cadena);
	buffer >> numero;
	return numero;
}

unsigned Utils::convertToUnsigned (const std::string & cadena)
{
	unsigned numero;
	std::istringstream buffer(cadena);
	buffer >> numero;
	return numero;
}

std::string Utils::convertToString (int numero)
{
	std::ostringstream buffer;
	buffer << numero;
	return buffer.str();
}
