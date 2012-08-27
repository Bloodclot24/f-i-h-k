#include "gui/VisualComponents/VisualComponentSegment.h"
#include "gui/VisualComponents/VisualComponentVia.h"

VisualComponentSegment::VisualComponentSegment(Point* start, Point* end, bool isVertical){
	m_isVertical = isVertical;
	m_startPoint = start;
	m_endPoint = end;
}


VisualComponentSegment::~VisualComponentSegment() {

}

InfluenceArea VisualComponentSegment::getInfluenceArea() {
	int halfwidth = round(ANCHO_DE_LINEA / 2);
	if (isVertical())
		return InfluenceArea(InfluenceRectangle( m_startPoint->getX() - halfwidth , m_startPoint->getY(), m_endPoint->getX() + halfwidth, m_endPoint->getY()));
	else
		return InfluenceArea(InfluenceRectangle( m_startPoint->getX(), m_startPoint->getY() + halfwidth, m_endPoint->getX(), m_endPoint->getY() - halfwidth));
}

bool VisualComponentSegment::isVertical(){
	return m_isVertical;
}

void VisualComponentSegment::on_expose(Cairo::RefPtr<Cairo::Context> ptrContext) {
	draw(ptrContext);
}

void VisualComponentSegment::on_move(int mouseX, int mouseY) {

}

void VisualComponentSegment::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
	ptrContext->save();
	if (m_selected)
		ptrContext->set_source_rgb(0, 1, 0);
	else
		ptrContext->set_source_rgb(0, 0, 0);
    ptrContext->set_line_width(ANCHO_DE_LINEA);
	ptrContext->move_to(m_startPoint->getX(), m_startPoint->getY());
	ptrContext->line_to(m_endPoint->getX(), m_endPoint->getY());
	ptrContext->stroke();
	ptrContext->restore();
}

int VisualComponentSegment::getX() const{
	return m_startPoint->getX();
}

void VisualComponentSegment::setX(int x){

}

int VisualComponentSegment::getY() const{
	return m_startPoint->getY();
}

void VisualComponentSegment::setY(int y){

}

int VisualComponentSegment::getLength() {
	return isVertical() ? abs(m_endPoint->getY() - m_startPoint->getY()) :  abs(m_endPoint->getX() - m_startPoint->getX());
}

bool VisualComponentSegment::isMobile() {
	return m_startPoint->isMobile() && m_endPoint->isMobile();
}
