#include "gui/VisualComponents/VisualComponentConector.h"
#include "gui/VisualComponents/VisualComponentVia.h"
#include "gui/Dibujar/AuxiliarDibujar.h"

VisualComponentConector::VisualComponentConector(VisualCompositeComponent* parent, Connector* connector, int nro, bool esEntrada, Diagram* diagram) :
	m_isEntry(esEntrada), m_number(nro), m_diagram(diagram) {
	m_connector = connector;
	m_parent = parent;
	m_number = nro;
	m_via = NULL;
}

VisualComponentConector::~VisualComponentConector(){
	if ( m_via != NULL){
		m_via->setStartConector(NULL);
		m_via->setEndConector(NULL);
	}
}

void VisualComponentConector::on_expose(Cairo::RefPtr<Cairo::Context> ptrContext){
	draw(ptrContext);
}

bool VisualComponentConector::isEditable(){
	return m_connector->isEntry();
}

InfluenceArea VisualComponentConector::getInfluenceArea() {
	return InfluenceRectangle(getX(), getY(), getX() + CONECTOR_INFLUENCE_RECTANGLE_XF, getY() + CONECTOR_INFLUENCE_RECTANGLE_YF);
}

void VisualComponentConector::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
	/*ptrContext->save();

	int x = getX();
	int y = getY();

	ptrContext->set_source_rgb(COLOR_LINE_COMPONENTS);
	ptrContext->set_line_width(ANCHO_DE_LINEA_CONECTOR);
	ptrContext->arc(x + CONECTOR_RADIUS, y + CONECTOR_RADIUS, CONECTOR_RADIUS, 0, 2 * M_PI);
	ptrContext->stroke_preserve();
	if ( m_selected){
		if( m_isAttribute)
			ptrContext->set_source_rgb(0, 0, 1);
		else
			ptrContext->set_source_rgb(1, 0, 0);
	}else
		ptrContext->set_source_rgb(1, 1, 1);
	ptrContext->fill();
	ptrContext->restore();
	*/
}

int VisualComponentConector::getNumber(){
	return m_number;
}

void VisualComponentConector::on_move(int x, int y){
	//mover la via cuando sea necesario
	if ( m_via != NULL )
		m_via->extend();
}

int VisualComponentConector::getX() const{
	return m_connector->getXRel() + m_parent->getX();
}

void VisualComponentConector::setX(int x){
	m_connector->setXRel(x);
}

int VisualComponentConector::getY() const{
	return m_connector->getYRel() + m_parent->getY();
}

void VisualComponentConector::setY(int y){
	m_connector->setYRel(y);
}

VisualCompositeComponent* VisualComponentConector::getParent(){
	return m_parent;
}

VisualComponentVia* VisualComponentConector::getVia() const {
    return m_via;
}

void VisualComponentConector::setVia(VisualComponentVia* via){
    m_via = via;
    //conecta el model/.
    if ( via != NULL)
    	m_connector->setVia((Via*)via->getComponent());
    else
    	m_connector->setVia(NULL);
}
