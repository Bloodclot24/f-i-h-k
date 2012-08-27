#include "model/Connector.h"
#include "model/Via.h"

Connector::Connector(Component* father, bool isAttribute, unsigned xRel, unsigned yRel, unsigned exitNumber) {
	m_father = father;
	m_isEntry = isAttribute;
	m_xRel = xRel;
	m_yRel = yRel;
	m_via = NULL;
}

Connector::~Connector() { }

