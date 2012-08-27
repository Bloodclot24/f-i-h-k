#include "gui/VisualComponents/VisualComponentEntity.h"
#include "gui/Dibujar/AuxiliarDibujar.h"

VisualComponentEntity::VisualComponentEntity( Diagram& diagram) : VisualCompositeComponent(diagram) {
	m_component = new Entity();
	initialize();
}

VisualComponentEntity::VisualComponentEntity(const VisualComponentEntity& other) : VisualCompositeComponent(other.m_diagram) {
	m_component = new Entity(*(Entity*)other.m_component);
	initialize();
}

VisualCompositeComponent* VisualComponentEntity::getCopy(){
	return new VisualComponentEntity(*this);
}

InfluenceArea VisualComponentEntity::getInfluenceArea() {
	return InfluenceRectangle(getX(), getY(), getX() + ENTITY_INFLUENCE_RECTANGLE_XF, getY() + ENTITY_INFLUENCE_RECTANGLE_YF);
}

void VisualComponentEntity::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
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
	if(m_component->getType() == 2) {
		std::vector<double> dashes;
		dashes.push_back(0);
		dashes.push_back(1.5);
		dashes.push_back(3);
		dashes.push_back(4.5);
		ptrContext->set_dash(dashes,0);
	}
	ptrContext->rectangle(x + CONECTOR_RADIUS, y, ENTITY_HORIZONTAL_LINE*2, ENTITY_VERTICAL_LINE);
	ptrContext->stroke_preserve();
	ptrContext->set_source_rgb(COLOR_COMPONENT);
	ptrContext->fill();
	ptrContext->restore();
	VisualCompositeComponent::draw( ptrContext);
	Draw draw;
	draw.writeTextInContext(ptrContext, x + (ENTITY_INFLUENCE_RECTANGLE_XF) / 2, y + (ENTITY_INFLUENCE_RECTANGLE_YF) / 1.5, m_component->getName(), COLOR_IN_TEXT);
}
