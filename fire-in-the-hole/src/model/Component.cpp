#include "model/Component.h"
#include "model/Utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include "model/Diagram.h"


Component::Component(const std::string & name, int type){
	m_name = name;
	m_type = type;
	m_posX = m_posY = 0;
	m_expression = "";
}


Component::Component(const Component & otroComponente){
	m_name = otroComponente.m_name;
	m_type = otroComponente.m_type;
	m_posX = otroComponente.m_posX;
	m_posY = otroComponente.m_posY;
	m_expression = otroComponente.m_expression;

}

Component& Component::operator=(const Component& otroComponente){
	m_name = otroComponente.m_name;
	m_type = otroComponente.m_type;
	m_posX = otroComponente.m_posX;
	m_posY = otroComponente.m_posY;
	return *this;
}


Component::~Component(){
	for ( unsigned i=0 ; i<m_entryConnectors.size() ; i++)
		delete m_entryConnectors[i];
	for ( unsigned i=0 ; i<m_exitConnectors.size() ; i++)
		delete m_exitConnectors[i];
}


void Component::addConnector(unsigned xRel, unsigned yRel, bool isAttribute, unsigned exitNumber) {

	Connector* conector= new Connector(this, isAttribute, xRel, yRel, exitNumber);
	isAttribute ? m_entryConnectors.push_back(conector) :
		m_exitConnectors.push_back(conector);
}


void Component::serialize(XmlWriter & writer_rep, XmlWriter & writer_comp)
{
	Utils utils;
	xmlNode* nodoActual;
	writer_rep.addCurrentNodeProperty(TARGET_NAME, m_name.c_str());
	writer_rep.addCurrentNodeProperty(TARGET_TYPE, utils.convertToString(m_type).c_str());
	writer_rep.addCurrentNodeProperty(TARGET_POS_X, utils.convertToString(m_posX).c_str());
	writer_rep.addCurrentNodeProperty(TARGET_POS_Y, utils.convertToString(m_posY).c_str());

	//std::string tipo = typeid(this).name();
	//std::cout << "Componente: " << tipo << std::endl;

	if (m_name != "Via"){
		nodoActual = writer_comp.addCurrentNodeChild(m_name.c_str(), "");
		writer_comp.addProperty(nodoActual, TARGET_NAME, m_name.c_str());
		//if (!m_attributes.empty()){
			//writer_comp.setCurrentNode(nodoActual);
			//serializeAttributes(writer_comp);
		//}
		writer_comp.setCurrentNode(nodoActual);
	}

}


void Component::deserialize(XmlReader & reader)
{
	Utils utils;
	m_name = reader.getCurrentNodeProperty(TARGET_NAME);
	m_type = (int) utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_TYPE));
	m_posX = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_POS_X));
	m_posY = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_POS_Y));
}

void Component::addToDiagram(Diagram &diagram){
	std::cout<<"/Agrego  " << getName() << " a "<<diagram.getName()<<"/";
	diagram.addComponent(this);
}

void Component::removeFromDiagram(Diagram &diagram){
	diagram.removeComponent(this);
}

void Component::setX(unsigned x){
	m_posX = x;
}

void Component::setY(unsigned y){
	m_posY = y;
}

unsigned Component::getX() const {
	return m_posX;
}

unsigned Component::getY() const {
	return m_posY;
}

void Component::validate(std::fstream & filestr, bool &valido){

	std::string aux;
	aux= typeid((*this)).name();
	std::cout<<aux;
	int cantAtr=0;
	int cantEnt=0;

	aux.erase(std::remove_if(aux.begin(), aux.end(), &isdigit), aux.end());

	if (  strcmp(aux.c_str(),"Via") != 0 ){
	this->update();
	filestr << " <H1> Nombre: " << this->getName() << " Tipo: " << aux << "</H1>";

	if (  strcmp(aux.c_str(),"Entity") == 0 ){
		if ( m_attributes.empty() && m_entities.empty() ){
			filestr << "<H2>	Error: El elemento esta desconectado" << "</H2>";
			valido = false;
		}
	  for(std::vector<Attribute*>::iterator it = m_attributes.begin(); it != m_attributes.end(); ++it){
			std::string str = typeid((**it)).name();
			str.erase(std::remove_if(str.begin(), str.end(), &isdigit), str.end());
			// verifico que tenga al menos un atributo
			if  ( strcmp(str.c_str(),"Attribute") == 0 )
				cantAtr++;
				// TODO: Abria que verificar si no es clave que herede la clave de alguien
	  }
	     if ( cantAtr == 0){
	    	 filestr << "<H2>	Error: La entidad no posee ningun atributo" << "</H2>";
	    	 valido = false;
	     }
	}

	if (  strcmp(aux.c_str(),"Relation") == 0 ){
		if ( m_attributes.empty() && m_entities.empty() ){
			filestr << "<H2>	Error: El elemento esta desconectado" << "</H2>";
			valido = false;
		}
	      for(std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
				std::string str = typeid((**it)).name();
				str.erase(std::remove_if(str.begin(), str.end(), &isdigit), str.end());

				// No puede estar unida a otra relacion
				if  ( strcmp(str.c_str(),"Relation") == 0 ){
					filestr << "<H2	Error: Una relacion no puede estar unida a otra relacion ("  <<  this->getName() << "," << (*it)->getName() << ")"  << "</H2>";
					valido = false;
				}
				// Una relacion tiene que estar unida al menos con dos entidades
				if  ( strcmp(str.c_str(),"Entity") == 0 )
					cantEnt++;
			}
		     if ( cantEnt < 2) {
		    	 filestr << "<H2>	Error: Las relaciones deben estar conectadas al menos con 2 entidades" << "</H2>";
		    	 valido = false;
		     }
	}

	if (  strcmp(aux.c_str(),"CompositeAttribute") == 0 ) {
		if ( m_attributes.empty() && m_entities.empty() ){
			filestr << "<H2>	Error: El elemento esta desconectado" << "</H2>";
			valido = false;
		}
	}

	if (  strcmp(aux.c_str(),"Fork") == 0 ) {
		if ( m_attributes.empty() && m_entities.empty() ){
			filestr << "<H2>	Error: El elemento esta desconectado" << "</H2>";
			valido = false;
		}
	}

	if (  strcmp(aux.c_str(),"Attribute") == 0 ) {
		Connector* con = this->m_exitConnectors[0];
		if ( con->getVia() == NULL ) {
			filestr << "<H2>	Error: El elemento esta desconectado" << "</H2>";
			valido = false;
		}
	}
	filestr <<std::endl;
	}

}

