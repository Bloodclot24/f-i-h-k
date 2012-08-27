#include "gui/VisualComponents/VisualComponentForkVia.h"
#include "model/Fork.h"
#include "gui/Dibujar/AuxiliarDibujar.h"

VisualComponentForkVia::VisualComponentForkVia(Diagram& diagram) : VisualCompositeComponent(diagram) {
	m_component = new Fork();
	initialize();
}

VisualComponentForkVia::VisualComponentForkVia(const VisualComponentForkVia& other) : VisualCompositeComponent(other.m_diagram) {
	m_component = new Fork(*(Fork*)other.m_component);
	initialize();
}

VisualComponentForkVia::~VisualComponentForkVia() {

}

VisualCompositeComponent* VisualComponentForkVia::getCopy(Diagram & diagram){
	Diagram & origen = m_diagram;
	m_diagram = diagram;
	VisualCompositeComponent* comp = new VisualComponentForkVia(*this);
	m_diagram = origen;
	return comp;
}


InfluenceArea VisualComponentForkVia::getInfluenceArea(){
	return InfluenceArea(InfluenceRectangle(getX(),getY(),getX() + FORK_INFLUENCE_RECTANGLE_XF, getY() + FORK_INFLUENCE_RECTANGLE_YF));
}

void VisualComponentForkVia::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
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
	ptrContext->move_to(x + CONECTOR_RADIUS, y + CONECTOR_RADIUS);
	ptrContext->rel_line_to(DIST_FORK, 0);
	ptrContext->rel_line_to(-DIST_FORK/2, DIST_FORK);
	ptrContext->rel_line_to(-DIST_FORK/2, -DIST_FORK);
	ptrContext->stroke_preserve();
	ptrContext->set_source_rgb(COLOR_COMPONENT);
	ptrContext->fill();
	ptrContext->restore();
	VisualCompositeComponent::draw( ptrContext);
	Draw draw;
	draw.writeTextInContext(ptrContext, x + (DIST_FORK + CONECTOR_RADIUS) / 1.9, y + (DIST_FORK) / 2, m_component->getName(), COLOR_IN_TEXT);

}
