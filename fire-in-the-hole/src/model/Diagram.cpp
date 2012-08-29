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
	for(unsigned i = 0; i < m_attributes.size(); i++)
		delete m_attributes[i];
	for(unsigned i = 0; i < m_components.size(); i++)
		delete m_components[i];
	for(unsigned i = 0; i < m_subdiagrams.size(); i++)
		delete m_subdiagrams[i];
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

void Diagram::startSerialization(){
	m_serializationIndex = new std::map< Component* , int>();
	int id = 0;
	for(unsigned i = 0; i < m_attributes.size(); i++){
		(*m_serializationIndex)[m_attributes[i]] = id ;
		id++;
	}

	for(unsigned i = 0; i < m_components.size(); i++){
		(*m_serializationIndex)[m_components[i]] = id ;
		id++;
	}
	for(unsigned i = 0; i < m_subdiagrams.size(); i++){
		(*m_serializationIndex)[m_subdiagrams[i]] = id ;
		id++;
	}
}

void Diagram::finalizeSerialization(){
	delete m_serializationIndex;
}

int Diagram::getId(Component* component)
{
	if ( m_serializationIndex->count(component)==0)
		return -1;
	return (*m_serializationIndex)[component];

}

void Diagram::addComponent(Component* component)
{
	m_components.push_back(component);
	
}

void Diagram::addAttribute(Attribute* Attribute) {
	Utils utils;
	Attribute->setName(Attribute->getName() + utils.convertToString(m_lastAttributeId));
	m_attributes.push_back(Attribute);
	m_lastAttributeId++;
}

void Diagram::addChip(Subdiagram* SUBDIAGRAM){
	m_subdiagrams.push_back(SUBDIAGRAM);
}


void Diagram::removeComponent(Component* component) {
	for(std::vector<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		if((*it) == component) {
		   m_components.erase(it);
		   return;
		}
}

void Diagram::removeChip(Subdiagram* subdiagram) {
	for(std::vector<Subdiagram*>::iterator it = m_subdiagrams.begin(); it != m_subdiagrams.end(); ++it)
		if((*it) == subdiagram) {
		   m_subdiagrams.erase(it);
		   return;
		}
}

void Diagram::removeAttribute(Attribute* attribute) {
	for(std::vector<Attribute*>::iterator it = m_attributes.begin(); it != m_attributes.end(); ++it)
		if((*it) == attribute) {
			m_attributes.erase(it);
			break;
		}
}

void Diagram::serializeToDraw(XmlWriter & writer)
{
	Utils utils;
	writer.addCurrentNodeProperty(TARGET_NAME, m_name.c_str());
	writer.addCurrentNodeProperty(TARGET_CANT_ENTRADAS, utils.convertToString(m_attributes.size()).c_str());
	writer.addCurrentNodeProperty(TARGET_SIZE_X, utils.convertToString(m_sizeX).c_str());
	writer.addCurrentNodeProperty(TARGET_SIZE_Y, utils.convertToString(m_sizeY).c_str());
}


void Diagram::deserialize(XmlReader & reader)
{
	try{
		Utils utils;
		reader.setCurrentNode(reader.getRoot());
		m_name = reader.getCurrentNodeProperty(TARGET_NAME);
		m_sizeX = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_SIZE_X));
		m_sizeY = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_SIZE_Y));

		std::map< unsigned, Component* > components;
		std::map< unsigned , std::vector<int> > idsComponentesEntradas;
		const char* nameComponente;
		xmlNode* nodoAnterior = reader.getCurrentNodeChild();
		reader.setCurrentNode(nodoAnterior);
		while(reader.getCurrentNode()){
			nameComponente = reader.getCurrentNodeName();

			Component* component = NULL;
			if(!strcmp(nameComponente, TARGET_ENTITY))
				component = new Entity();
			else if (!strcmp(nameComponente, TARGET_ATTRIBUTE))
				component = new Attribute();
			else if (!strcmp(nameComponente, TARGET_RELATION))
				component = new Relation();
			else if (!strcmp(nameComponente, TARGET_COMPOSITEATTRIBUTE))
				component = new CompositeAttribute();
			else if (!strcmp(nameComponente, TARGET_SUBDIAGRAM))
				component = new Subdiagram();
			else if (!strcmp(nameComponente, TARGET_VIA))
				component = new Via();
			else if (!strcmp(nameComponente, TARGET_FORK))
				component = new Fork();
			else
				throw std::runtime_error("Formato invalido del archivo xml");

			if(component){
				component->deserialize(reader);
				component->addToDiagram(this);
				nodoAnterior = reader.getCurrentNode();
				int identificador = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_ID));
				components[identificador] = component;

				std::vector<int> ids;
				xmlNode* nodoActual = reader.getCurrentNodeChild();
				while(nodoActual){
					reader.setCurrentNode(nodoActual);
					if(strcmp(reader.getCurrentNodeName(), TARGET_PUNTO) != 0)
						ids.push_back(utils.convertToInt(reader.getCurrentNodeProperty(TARGET_ID)));
					nodoActual = reader.nextNode();
				}
				idsComponentesEntradas[identificador] =  ids;
			}

			reader.setCurrentNode(nodoAnterior);
			nodoAnterior = reader.nextNode();
			reader.setCurrentNode(nodoAnterior);
		}

		//Conecta los components
		for(unsigned i = 0; i < idsComponentesEntradas.size(); i++){
			std::vector<int> ids = idsComponentesEntradas[i];
			Component* component = components[i];
			for (unsigned j = 0; j < ids.size(); j++) {
				if(ids[j] >= 0) {
					Via* via = (Via*) components[ids[j]];
					Connector* connector = j < component->getAttributeConnectors()->size() ?
							(*component->getAttributeConnectors())[j] : (*component->getExitConnectors())[j - component->getAttributeConnectors()->size()];
					unsigned x = (*via->getPoints().begin())->getX();
					unsigned y = (*via->getPoints().begin())->getY();
					unsigned delta = 10;
					if(component->getX() + connector->getXRel() - delta <= x && x <= component->getX() + connector->getXRel() + delta &&
							component->getY() + connector->getYRel() - delta <= y && y <= component->getY() + connector->getYRel() +delta )
							via->setStartConnector(connector);
					else
							via->setEndConnector(connector);
					connector->setVia(via);
				}
			}
		}
	} catch (std::exception e) {
		throw std::runtime_error("Formato invalido del archivo xml");
	}
}

std::string Diagram::serializeToDraw(){
	XmlWriter xml("diagram");
	serializeToDraw(xml);
	return xml.toString();
}

void Diagram::deserialize(const std::string &str){
	XmlReader xml(str.c_str(), str.size());
	deserialize(xml);
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
	for(std::vector<Attribute*>::iterator it = m_attributes.begin(); it != m_attributes.end(); ++it)
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
