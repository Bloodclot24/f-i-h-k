#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

/**
 * @brief
 * Esta clase se utiliza para levantar el archivo de configuracion y poder
 * pedirle directamente a esta clase los distintos valores de los distintos
 * parametros que se encuentran en el mismo. Si no se le ingresa el path del
 * archivo de configuracion, se usa por defecto CONFIG_DIR.
 * El archivo de configuracion se levanta una vez en un hash, el cual posee
 * tiene como key el parametro y como value el valor del mismo.
 * ARCHIVO CONFIGURACION :
 * Este archivo tiene el siguiente formato:
 *
 * - Possee lineas conformadas por Clave/Valor de la forma "Parametro=valor"
 * sin espacios entre estos. (Max linea = 1024)
 *
 * - Las lineas de comentario deben empezar con #. Solo se puede comentar al
 * principio de estas.
 *
 * - Las lineas de comentario como las que esten en blanco son ignoradas.
 */

const int MAX_LINE = 1024;
const std::string CONFIG_DIR = "../config";
const std::string CONFIG_FILE_NAME = "diagrams.conf";
const char SEP = '=';
const char COMENT_CHAR = '#';
const std::string LOG_FILE = "DiagramLog";


class Settings {
public:

	virtual ~Settings();

	std::string getLogFile();

	/**
	 * @brief devuelve el valor del parametro que se encuentra en el archivo
	 * configuracion.
	 * @param parameter
	 * @return valor
	 */
	std::string getValue(const std::string &parameter);

	static Settings& getInstance();

	/**
	 * @brief divide el string con separadores en un vector con cada string
	 * que esta entre los separadores.
	 * @param separator
	 * @param line
	 * @return vector de strings separados
	 */
	 static std::vector< std::string > split( char separator, const std::string &line);

	 /**
	  * @brief indica a settings donde se encuentra el directorio donde
	  * se encuentra el archivo de configuracion.
	  * @param configPath
	  */
	 static void setConfigPath( const std::string &configPath);

	 static void chomp(std::string &);

private:

	static std::string m_configPath;

	Settings(const std::string &configPath );

	std::fstream m_configFile;
	std::map< std::string , std::string > m_config;

	/**
	 * @brief carga el archivo de configuracion a memoria(hash).
	 */
	void chargeMap();
};

#endif /* SETTINGS_H_ */
