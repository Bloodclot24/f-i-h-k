#include "model/Via.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include "model/Utils.h"
#include <typeinfo>

Via::Via(unsigned exit, const std::string & name, int orientation)
: Component(name, orientation)
{
	m_exitNumber = exit;
	initializeConnectors();
}


Via::Via(const Via & otro) : Component(otro){

	for (std::list<Point*>::const_iterator it = otro.m_points.begin(); it != otro.m_points.end(); ++it)
		addPointAtEnd(new Point(*(*it)));
	m_exitNumber = otro.getExitNumber();
	initializeConnectors();
}

Via::~Via(){
	std::list< Point* >::iterator it;
	for ( it = m_points.begin() ; it !=m_points.end() ; ++it )
		delete (*it);
}

Via& Via::operator=(const Via& otro) {

	Component::operator=(otro);
	m_exitNumber = otro.getExitNumber();
	initializeConnectors();
	return *this;
}


void Via::initializeConnectors() {
	m_types.push_back("0..1");
	m_types.push_back("1..1");
	m_types.push_back("0..N");
	m_types.push_back("1..N");
	m_types.push_back("N..N");
}

void Via::serialize(XmlWriter & writer_rep, XmlWriter & writer_comp)
{
	Utils utils;
	writer_rep.addRootChild(TARGET_VIA, "");
	Component::serialize(writer_rep, writer_comp);
	writer_rep.addCurrentNodeProperty("nroSalida", utils.convertToString(m_exitNumber).c_str());
	std::list< Point* >::iterator it;
	xmlNode* nodoActual;
	for ( it=m_points.begin() ; it!=m_points.end() ; ++it){
		nodoActual = writer_rep.addCurrentNodeChild(TARGET_PUNTO, "");
		writer_rep.addProperty( nodoActual, TARGET_POS_X,utils.convertToString((*it)->getX()).c_str());
		writer_rep.addProperty( nodoActual, TARGET_POS_Y,utils.convertToString((*it)->getY()).c_str());
		writer_rep.addProperty( nodoActual, "movible",utils.convertToString((*it)->isMobile()).c_str());
	}
}


void Via::deserialize(XmlReader & reader)
{
	Utils utils;
	Component::deserialize(reader);
	m_exitNumber = utils.convertToUnsigned(reader.getCurrentNodeProperty("nroSalida"));

	xmlNode* nodoVia = reader.getCurrentNode();
	reader.setCurrentNode(reader.getCurrentNodeChild());
	while(reader.getCurrentNode()){
		const char* nameNodo = reader.getCurrentNodeName();
        if(strcmp(nameNodo, TARGET_PUNTO) == 0){//se encontro un nodo punto
        	int x = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_POS_X));
        	int y = utils.convertToUnsigned(reader.getCurrentNodeProperty(TARGET_POS_Y));
        	bool movible = utils.convertToUnsigned(reader.getCurrentNodeProperty("movible"));
        	Point* point = new Point(x,y, movible);
        	addPointAtEnd(point);
        }
        reader.setCurrentNode(reader.nextNode());
	}
	reader.setCurrentNode(nodoVia);
}

void Via::addPoint( Point* p, std::list< Point* >::iterator it){
	m_points.insert(it, p);
}

void Via::removePoint( Point* p){
	for (std::list<Point*>::iterator it = m_points.begin(); it != m_points.end(); ++it)
		if ((*it) == p) {
			m_points.erase(it);
			return;
		}
}

std::list< Point* >& Via::getPoints(){
	return m_points;
}

void Via::addPointAtEnd( Point* point){
	m_points.push_back(point);
}

bool Via::verifyConnectEntityRelation(){

	if ( strcmp(typeid((*this->getStartConnector()->getFather())).name(),"6Entity") == 0 and strcmp(typeid((*this->getEndConnector()->getFather())).name(),"8Relation") == 0 ){
		return true;
	}
	if ( strcmp(typeid((*this->getStartConnector()->getFather())).name(),"8Relation") == 0 and strcmp(typeid((*this->getEndConnector()->getFather())).name(),"6Entity") == 0 ){
			return true;
	}
	return false;


}
