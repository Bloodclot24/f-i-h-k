#include "model/Subdiagram.h"
#include "model/Utils.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include "model/Entity.h"
#include "model/CompositeAttribute.h"
#include "model/Relation.h"
#include "model/Via.h"
#include "model/Attribute.h"
#include "model/Diagram.h"
#include "gui/Dibujar/Defines.h"

Subdiagram::Subdiagram(const std::string & name) : Component(name)
{

}


Subdiagram::Subdiagram(const Subdiagram & otro) : Component(otro){

}


Subdiagram& Subdiagram::operator=(const Subdiagram& otro) {


	return *this;
}

void Subdiagram::serialize(XmlWriter & writer_rep, XmlWriter & writer_comp)
{
	writer_rep.addRootChild(TARGET_SUBDIAGRAM, "");
	Component::serialize(writer_rep, writer_comp);
/*	writer_rep.addCurrentNodeProperty(TARGET_SIZE_X, utils.convertToString(m_sizeX).c_str());
	writer_rep.addCurrentNodeProperty(TARGET_SIZE_Y, utils.convertToString(m_sizeY).c_str());

	writer_rep.addCurrentNodeProperty(TARGET_CANT_ENTRADAS, utils.convertToString(m_AttributeNumber).c_str());
*/
}


void Subdiagram::deserialize(XmlReader & reader)
{
	Component::deserialize(reader);
/*	m_AttributeNumber = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_CANT_ENTRADAS));
	m_sizeX = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_SIZE_X));
	m_sizeY = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_SIZE_Y));
	initializeConnectors();
	*/
}

void Subdiagram::addToDiagram(Diagram* diagram){
	diagram->addChip(this);
}

void Subdiagram::removeFromDiagram(Diagram* diagram){
	diagram->removeChip(this);
}
