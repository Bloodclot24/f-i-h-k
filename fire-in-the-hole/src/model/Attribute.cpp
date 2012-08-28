#include "model/Attribute.h"
#include <iostream>
#include <string>
#include <sstream>
#include "model/Diagram.h"
#include "gui/Dibujar/Defines.h"
#include "model/Utils.h"

Attribute::Attribute(const std::string & name, int orientation)
: Component(name, orientation){
	initializeConnectors();
}


Attribute::Attribute(const Attribute & otro) : Component(otro){
	initializeConnectors();
	m_options[0] = otro.m_options[0];
	m_options[1] = otro.m_options[1];
	m_options[2] = otro.m_options[2];
}


Attribute& Attribute::operator=(const Attribute& otro) {
	Component::operator=(otro);
	initializeConnectors();
	m_options[0] = otro.m_options[0];
	m_options[1] = otro.m_options[1];
	m_options[2] = otro.m_options[2];
	return *this;
}


void Attribute::initializeConnectors() {

	addConnector( ATTRIBUTE_ONLY_CONECTOR, false);
	m_options.push_back(false);
	m_options.push_back(false);
	m_options.push_back(false);
}


void Attribute::serialize(XmlWriter & writer_rep, XmlWriter & writer_comp)
{
	writer_rep.addRootChild(TARGET_ATTRIBUTE, "");
	XmlWriter xml_dummy("dummy");
	Component::serialize(writer_rep, xml_dummy);
	Utils utils;
	writer_rep.addCurrentNodeProperty(TARGET_EXPRESSION, m_expression.c_str());
	writer_rep.addCurrentNodeProperty(TARGET_ID_0, utils.convertToString(m_options[0]).c_str());
	writer_rep.addCurrentNodeProperty(TARGET_ID_1, utils.convertToString(m_options[1]).c_str());
	writer_rep.addCurrentNodeProperty(TARGET_ID_2, utils.convertToString(m_options[2]).c_str());
}

void Attribute::deserialize(XmlReader & reader) {
	Component::deserialize(reader);
	Utils utils;
	m_expression = reader.getCurrentNodeProperty(TARGET_EXPRESSION);
	m_options[0] = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_ID_0));
	m_options[1] = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_ID_1));
	m_options[2] = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_ID_2));
}

void Attribute::removeFromDiagram(Diagram* diagram){
	diagram->removeAttribute(this);
}
