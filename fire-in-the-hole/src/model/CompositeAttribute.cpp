#include "model/CompositeAttribute.h"
#include <iostream>
#include <string>
#include <sstream>
#include "gui/Dibujar/Defines.h"
#include "model/Connector.h"
#include "model/Via.h"
#include "model/Utils.h"

CompositeAttribute::CompositeAttribute(const std::string & name, int orientation)
: Component(name, orientation)
{
	initializeConnectors();
}


CompositeAttribute::CompositeAttribute(const CompositeAttribute & otro) : Component(otro){
	initializeConnectors();
	m_options[0] = otro.m_options[0];
	m_options[1] = otro.m_options[1];
	m_options[2] = otro.m_options[2];
}


CompositeAttribute& CompositeAttribute::operator=(const CompositeAttribute& otro) {

	Component::operator=(otro);
	initializeConnectors();
	m_options[0] = otro.m_options[0];
	m_options[1] = otro.m_options[1];
	m_options[2] = otro.m_options[2];
	return *this;
}


void CompositeAttribute::initializeConnectors() {

	addConnector(COMPOSITEATTRIBUTE_SALIDA_0, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_1, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_2, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_3, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_4, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_5, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_6, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_7, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_8, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_9, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_10, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_11, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_12, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_13, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_14, false);
	addConnector(COMPOSITEATTRIBUTE_SALIDA_15, false);
	m_options.push_back(false);
	m_options.push_back(false);
	m_options.push_back(false);
}

void CompositeAttribute::serialize(XmlWriter & writer_rep, XmlWriter & writer_comp)
{
	writer_rep.addRootChild(TARGET_COMPOSITEATTRIBUTE, "");
	Component::serialize(writer_rep, writer_comp);
	Utils utils;
	writer_rep.addCurrentNodeProperty(TARGET_EXPRESSION, m_expression.c_str());
	writer_rep.addCurrentNodeProperty(TARGET_ID_0, utils.convertToString(m_options[0]).c_str());
	writer_rep.addCurrentNodeProperty(TARGET_ID_1, utils.convertToString(m_options[1]).c_str());
	writer_rep.addCurrentNodeProperty(TARGET_ID_2, utils.convertToString(m_options[2]).c_str());
}

void CompositeAttribute::deserialize(XmlReader & reader) {
	Component::deserialize(reader);
	Utils utils;
	m_expression = reader.getCurrentNodeProperty(TARGET_EXPRESSION);
	m_options[0] = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_ID_0));
	m_options[1] = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_ID_1));
	m_options[2] = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_ID_2));
}

void CompositeAttribute::update()
{
	m_attributes.clear();
	for(unsigned i = 0; i < m_entryConnectors.size(); i++)
		if(m_entryConnectors[i]->getVia() != NULL) {
			Via* via = m_entryConnectors[i]->getVia();
			if(via->getEndConnector() != m_entryConnectors[i])
				m_attributes.push_back((Attribute*)via->getEndConnector()->getFather());
			else
				m_attributes.push_back((Attribute*)via->getStartConnector()->getFather());
		}
}
