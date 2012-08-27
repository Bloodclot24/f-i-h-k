#include "gui/VisualComponents/VisualComponentRelation.h"

VisualComponentRelation::VisualComponentRelation( Diagram& diagram) : VisualCompositeComponent(diagram) {
	m_component = new Relation();
	initialize();
}

VisualComponentRelation::VisualComponentRelation(const VisualComponentRelation& other) : VisualCompositeComponent(other.m_diagram) {
	m_component = new Relation(*(Relation*)other.m_component);
	initialize();
}

VisualCompositeComponent* VisualComponentRelation::getCopy(){
	return new VisualComponentRelation(*this);
}

InfluenceArea VisualComponentRelation::getInfluenceArea() {
	return InfluenceRectangle(getX(), getY(), getX() + RELATION_INFLUENCE_RECTANGLE_XF, getY() + RELATION_INFLUENCE_RECTANGLE_YF);
}

void VisualComponentRelation::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
	ptrContext->save();

	int x = getX();
	int y = getY();

	if (m_selected)
		ptrContext->set_source_rgb(0, 1, 0);
	else
		ptrContext->set_source_rgb(0, 0, 0);
	ptrContext->set_line_width(ANCHO_DE_LINEA);
	if(m_component->getType() == 1)
		ptrContext->set_line_width(ANCHO_DE_LINEA*3);
	ptrContext->move_to(x + CONECTOR_RADIUS + RELATION_HORIZONTAL_DISPLACEMENT/2, y);
	ptrContext->rel_line_to(RELATION_HORIZONTAL_DISPLACEMENT/2, RELATION_VERTICAL_LINE / 2);
	ptrContext->rel_line_to(- RELATION_HORIZONTAL_DISPLACEMENT/2, RELATION_VERTICAL_LINE / 2);
	ptrContext->rel_line_to(- RELATION_HORIZONTAL_DISPLACEMENT/2, - RELATION_VERTICAL_LINE / 2);
	ptrContext->close_path();
	ptrContext->stroke_preserve();
	ptrContext->set_source_rgb(COLOR_COMPONENT);
	ptrContext->fill();
	ptrContext->restore();
	VisualCompositeComponent::draw( ptrContext);
	Draw draw;
	draw.writeTextInContext(ptrContext, x + RELATION_HORIZONTAL_DISPLACEMENT/2, y + RELATION_VERTICAL_LINE / 1.5, m_component->getName(), COLOR_IN_TEXT);
}
