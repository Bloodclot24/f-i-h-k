#include "model/Diagram.h"
#include "model/Utils.h"
#include "model/Fork.h"
#include <exception>
#include <math.h>
#include <iostream>
#include <string.h>
#include <list>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <gtkmm-2.4/gtkmm/messagedialog.h>


Diagram::Diagram(const std::string & name) {

	m_name = name;
	m_lastAttributeId = 0;
}

Diagram::~Diagram(){
	for(unsigned i = 0; i < m_components.size(); i++)
		delete m_components[i];
}

void Diagram::serializeConnectedComponents(Component* component, XmlWriter & writer)
{
	serializeConnectedComponents(*component->getAttributeConnectors(), writer);
	serializeConnectedComponents(*component->getExitConnectors(), writer);
}


void Diagram::serializeConnectedComponents(std::vector<Connector*> connectors, XmlWriter & writer) {
	xmlNode* nodoActual;
	for(unsigned i = 0; i < connectors.size(); i++){
		nodoActual = connectors[i]->getVia() != NULL ?
			writer.addCurrentNodeChild(connectors[i]->getVia()->getName().c_str(), "") :
			writer.addCurrentNodeChild(TARGET_VACIO, "");
		Utils utils;
		writer.addProperty(nodoActual, TARGET_ID, utils.convertToString(getId(connectors[i]->getVia())).c_str());
	}
}

int Diagram::getId(Component* component)
{
	for( unsigned i = 0; i < m_components.size(); i++)
		if(m_components[i] == component)
			return i;
	return -1;

}

void Diagram::addComponent(Component* component)
{
	m_components.push_back(component);
	
}

void Diagram::removeComponent(Component* component) {
	for(std::vector<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		if((*it) == component) {
		   m_components.erase(it);
		   return;
		}
}

void validateConections(std::vector<Connector*> connectors){

bool conectado = false;
	for(unsigned i = 0; i < connectors.size(); i++){
		if ( connectors[i]->getVia() != NULL ){
			conectado = true;
			break;
		}
	}
	if (conectado){
	printf("123");
	}
}

void Diagram::validateDiagram(std::fstream & filestr){
	bool valido = true;

	filestr<< "<HTML><HEAD><TITLE>ARCHIVO DE VALIDACION</TITLE></HEAD><BODY> ";

	for(std::vector<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		(*it)->validate(filestr,valido);

	filestr << "<H1>**************************************************************************************************" << "</H1>";
	filestr << "<H1>**************************************************************************************************" << "</H1>";

	if (valido) {
		Gtk::MessageDialog msg("El diagrama es válido. Se ha generado el html de los detalles.");
		msg.run();
		filestr << "<font color=\"green\">" << "<STRONG> EL DIAGRAMA ANALIZADO ES VALIDO </STRONG>" << std::endl;
	}else{
		Gtk::MessageDialog msg("El diagrama es inválido. Se ha generado el html de los detalles.");
		msg.run();
		filestr << "<font color=\"red\">" <<"<STRONG> EL DIAGRAMA ANALIZADO ES INVALIDO </STRONG>" <<std::endl;
	}

	filestr<< "</BODY></HTML>";
}
