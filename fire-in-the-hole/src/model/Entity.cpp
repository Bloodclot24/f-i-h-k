#include "model/Entity.h"
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include "gui/Dibujar/Defines.h"
#include "model/Connector.h"
#include "model/Via.h"

Entity::Entity(const std::string & name, int orientation)
	: Component(name, orientation)
{
	initializeConnectors();
}


Entity::Entity(const Entity & otro) : Component(otro){

	initializeConnectors();
}


Entity& Entity::operator=(const Entity& otro) {

	Component::operator=(otro);
	initializeConnectors();
	return *this;
}

void Entity::initializeConnectors() {
	addConnector(ENTITY_ENTRADA_0, true);
	addConnector(ENTITY_ENTRADA_1, true);
	addConnector(ENTITY_ENTRADA_2, true);
	addConnector(ENTITY_ENTRADA_3, true);
	addConnector(ENTITY_ENTRADA_4, true);
	addConnector(ENTITY_ENTRADA_5, true);
	addConnector(ENTITY_ENTRADA_6, true);
	addConnector(ENTITY_ENTRADA_7, true);
	addConnector(ENTITY_ENTRADA_8, true);
	addConnector(ENTITY_ENTRADA_9, true);
	addConnector(ENTITY_ENTRADA_10, true);
	addConnector(ENTITY_ENTRADA_11, true);
	addConnector(ENTITY_ENTRADA_12, true);
	addConnector(ENTITY_ENTRADA_13, true);
	addConnector(ENTITY_ENTRADA_14, true);
	addConnector(ENTITY_ENTRADA_15, true);
	addConnector(ENTITY_ENTRADA_16, true);
	addConnector(ENTITY_ENTRADA_17, true);
	addConnector(ENTITY_ENTRADA_18, true);
	addConnector(ENTITY_ENTRADA_19, true);
	addConnector(ENTITY_ENTRADA_20, true);
	addConnector(ENTITY_ENTRADA_21, true);
	addConnector(ENTITY_ENTRADA_22, true);
	addConnector(ENTITY_ENTRADA_23, true);
	addConnector(ENTITY_ENTRADA_24, true);
	addConnector(ENTITY_ENTRADA_25, true);
	addConnector(ENTITY_ENTRADA_26, true);
	addConnector(ENTITY_ENTRADA_27, true);
	addConnector(ENTITY_ENTRADA_28, true);
	m_types.push_back("Fuerte");
	m_types.push_back("Debil");
	m_types.push_back("Transaccional");
	m_types.push_back("Maestra");
}

void Entity::serialize(XmlWriter & writer_rep, XmlWriter & writer_comp)
{
	writer_rep.addRootChild(TARGET_ENTITY, "");
	Component::serialize(writer_rep, writer_comp);
}

void Entity::update()
{
	m_attributes.clear();

	for(unsigned i = 0; i < m_entryConnectors.size(); i++){
		if(m_entryConnectors[i]->getVia() != NULL) {
			Via* via = m_entryConnectors[i]->getVia();
			if(via->getEndConnector() != m_entryConnectors[i])
				m_attributes.push_back((Attribute*)via->getEndConnector()->getFather());
			else
				m_attributes.push_back((Attribute*)via->getStartConnector()->getFather());
		}
	}
}

