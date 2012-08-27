#include "model/Relation.h"
#include <iostream>
#include <string>
#include <sstream>
#include "gui/Dibujar/Defines.h"
#include "model/Connector.h"
#include "model/Via.h"
#include "model/Entity.h"
#include "model/Attribute.h"

Relation::Relation(const std::string & name, int orientation)
: Component(name, orientation){

	initializeConnectors();
}

Relation::Relation(const Relation & otro) : Component(otro){

	initializeConnectors();
}


Relation& Relation::operator=(const Relation& otro) {

	Component::operator=(otro);
	initializeConnectors();
	return *this;
}

void Relation::initializeConnectors() {

	addConnector(RELATION_ENTRADA_0, true);
	addConnector(RELATION_ENTRADA_01, true);
	addConnector(RELATION_ENTRADA_02, true);
	addConnector(RELATION_ENTRADA_03, true);
	addConnector(RELATION_ENTRADA_04, true);
	addConnector(RELATION_ENTRADA_1, true);
	addConnector(RELATION_ENTRADA_11, true);
	addConnector(RELATION_ENTRADA_12, true);
	addConnector(RELATION_ENTRADA_13, true);
	addConnector(RELATION_ENTRADA_14, true);
	addConnector(RELATION_ENTRADA_2, true);
	addConnector(RELATION_ENTRADA_21, true);
	addConnector(RELATION_ENTRADA_22, true);
	addConnector(RELATION_ENTRADA_23, true);
	addConnector(RELATION_ENTRADA_24, true);
	addConnector(RELATION_ENTRADA_3, true);
	addConnector(RELATION_ENTRADA_31, true);
	addConnector(RELATION_ENTRADA_32, true);
	addConnector(RELATION_ENTRADA_33, true);
	addConnector(RELATION_ENTRADA_34, true);
	m_types.push_back("Fuerte");
	m_types.push_back("Debil");
}

void Relation::serialize(XmlWriter & writer_rep, XmlWriter & writer_comp)
{
	writer_rep.addRootChild(TARGET_RELATION, "");
	Component::serialize(writer_rep, writer_comp);
}

void Relation::update()
{
	m_attributes.clear();
	m_entities.clear();
	for(unsigned i = 0; i < m_entryConnectors.size(); i++)
		if(m_entryConnectors[i]->getVia() != NULL) {
			Via* via = m_entryConnectors[i]->getVia();
			if(via->getEndConnector() != m_entryConnectors[i]) {
				if(via->getEndConnector()->isEntry())
					m_entities.push_back((Entity*)via->getEndConnector()->getFather());
				else
					m_attributes.push_back((Attribute*)via->getEndConnector()->getFather());
			} else {
				if(via->getStartConnector()->isEntry())
					m_entities.push_back((Entity*) via->getStartConnector()->getFather());
				else
					m_attributes.push_back((Attribute*)via->getStartConnector()->getFather());
			}
		}
}
