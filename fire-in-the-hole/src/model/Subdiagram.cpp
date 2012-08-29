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

}


void Subdiagram::deserialize(XmlReader & reader)
{
	Component::deserialize(reader);

}

void Subdiagram::addToDiagram(Diagram* diagram){
	diagram->addChip(this);
}

void Subdiagram::removeFromDiagram(Diagram* diagram){
	diagram->removeChip(this);
}
