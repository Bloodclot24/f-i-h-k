#include "utils/Settings.h"
#include <sstream>

std::string Settings::m_configPath = CONFIG_DIR;

Settings::Settings(const std::string &configPath) {
	m_configFile.open( (configPath +"/"+ CONFIG_FILE_NAME).c_str() );
	if ( m_configFile.fail()){
		std::cerr << "No se pudo abrir el archivo de configuracion" << std::endl;
		return;
	}
	chargeMap();
	m_configFile.close();
}

Settings::~Settings() { }


Settings& Settings::getInstance(){
	static Settings instance(m_configPath);
	return instance;
}

void Settings::setConfigPath( const std::string &configPath){
	m_configPath = configPath;
}

std::string Settings::getValue(const std::string &parameter){
	return m_config[parameter];
}

std::string Settings::getLogFile(){
	return getValue(LOG_FILE);
}

void Settings::chargeMap(){
	char buffer[MAX_LINE];
	std::vector< std::string > pairs;

	while ( m_configFile.getline(buffer,MAX_LINE)){
		std::string line;
		std::stringstream sstream;
		sstream << buffer;
		sstream >> line;
		if ( !(line != "\n" && !(line.size() <= 2) && line.at(0) != COMENT_CHAR))
			continue;
		pairs = split(SEP, line);
		m_config[pairs[0]] = pairs[1];
	}
}

std::vector< std::string > Settings::split( char separator, const std::string &line){
	int start = 0, end = line.find(separator);
	std::vector< std::string> regs;
	int amount = 0;

	while ( end != -1){
		regs.push_back(line.substr(start, end - start));
		start = end +1 ;
		end = line.find(separator,start);
		amount++;
	}
	regs.push_back(line.substr(start));
	return regs;
}

void chomp(std::string & ln){
	if( ln.at(ln.size()) == '\n')
		ln = ln.substr(0,ln.size()-1);
}
