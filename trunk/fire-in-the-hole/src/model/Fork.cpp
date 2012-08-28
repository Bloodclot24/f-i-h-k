#include "model/Fork.h"
#include "gui/Dibujar/Defines.h"
#include "model/Connector.h"
#include "model/Via.h"
#include "model/Entity.h"
#include "model/Attribute.h"

Fork::Fork(const std::string & name, int orientation)
: Component(name, orientation){
	initializeConnectors();
}


Fork::Fork(const Fork & otro) : Component(otro){

	initializeConnectors();
}


Fork& Fork::operator=(const Fork& otro) {

	Component::operator=(otro);
	return *this;
}


void Fork::serialize(XmlWriter & writer_rep, XmlWriter & writer_comp)
{
	writer_rep.addRootChild(TARGET_FORK, "");
	Component::serialize(writer_rep, writer_comp);
}

void Fork::initializeConnectors(){
	addConnector( FORK_ENTRADA_0, false);
	addConnector( FORK_ENTRADA_1, false);
	addConnector( FORK_ENTRADA_2, false);
	addConnector( FORK_ENTRADA_3, false);
	addConnector( FORK_ENTRADA_13, false);
	addConnector( FORK_ENTRADA_32, false);
	addConnector( FORK_ENTRADA_10, false);
	addConnector( FORK_ENTRADA_20, false);
	addConnector( FORK_ENTRADA_100, false);
	addConnector( FORK_ENTRADA_200, false);
	addConnector( FORK_ENTRADA_1000, false);
	addConnector( FORK_ENTRADA_2000, false);
	m_types.push_back("Generalización");
	m_types.push_back("Especialización");
}

void Fork::update() {
	m_attributes.clear();
	m_entities.clear();
	for (unsigned i = 0; i < m_entryConnectors.size(); i++)
		if (m_entryConnectors[i]->getVia() != NULL) {
			Via* via = m_entryConnectors[i]->getVia();
			if (via->getEndConnector() != m_entryConnectors[i]) {
				if (via->getEndConnector()->isEntry())
					m_entities.push_back((Entity*) via->getEndConnector()->getFather());
				else
					m_attributes.push_back((Attribute*) via->getEndConnector()->getFather());
			} else {
				if (via->getStartConnector()->isEntry())
					m_entities.push_back((Entity*) via->getStartConnector()->getFather());
				else
					m_attributes.push_back((Attribute*) via->getStartConnector()->getFather());
			}
		}
}

