#include "gui/VisualComponents/VisualComponentAttribute.h"
#include "gui/VisualComponents/VisualComponentConector.h"
#include "gui/SubWindow/ViewModifyAttributeInfoWin.h"

VisualComponentAttribute::VisualComponentAttribute(Diagram& diagram) : VisualCompositeComponent(diagram){
	m_component = new Attribute();
	initialize();
}

VisualComponentAttribute::VisualComponentAttribute(const VisualComponentAttribute& other) : VisualCompositeComponent(other.m_diagram) {
	m_component = new Attribute(*(Attribute*)other.m_component);
	initialize();
}

VisualCompositeComponent* VisualComponentAttribute::getCopy(){
	return new VisualComponentAttribute(*this);
}


InfluenceArea VisualComponentAttribute::getInfluenceArea() {

	return InfluenceRectangle(getX(), getY(), getX() + ATTRIBUTE_INFLUENCE_RECTANGLE_XF, getY() + ATTRIBUTE_INFLUENCE_RECTANGLE_YF);
}

void VisualComponentAttribute::showProperties(){
	ViewModifyAttributeInfoWin dialog(m_component);
	dialog.run();
	return;
}

void VisualComponentAttribute::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
	ptrContext->save();

	int x = getX();
	int y = getY();
	Draw draw;
	draw.writeTextInContext(ptrContext, x + ATTRIBUTE_RADIUS, y, m_component->getName(), COLOR_IN_TEXT);
	if(m_component->getExpression() != "")
		draw.writeTextInContext(ptrContext, x + ATTRIBUTE_RADIUS, y + ATTRIBUTE_RADIUS*4, m_component->getExpression(), COLOR_LINE_COMPONENTS);

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
	ptrContext->arc(x + ATTRIBUTE_RADIUS, y + ATTRIBUTE_RADIUS, ATTRIBUTE_RADIUS, 0, 2 * M_PI);
	ptrContext->stroke_preserve();

	if (m_component->getOptions()[0]){
		ptrContext->unset_dash();
		ptrContext->set_source_rgb(0, 0, 0);
		ptrContext->set_line_width(ANCHO_DE_LINEA*2);
		ptrContext->move_to(x - ATTRIBUTE_RADIUS*2, y);
		ptrContext->line_to(x + ATTRIBUTE_RADIUS*4, y);
		ptrContext->stroke_preserve();
	}
	if (m_component->getOptions()[1]) {
		ptrContext->unset_dash();
		ptrContext->set_source_rgb(0, 0, 0);
		ptrContext->set_line_width(ANCHO_DE_LINEA*0.6);
		ptrContext->move_to(x - ATTRIBUTE_RADIUS*2, y + ATTRIBUTE_RADIUS/2);
		ptrContext->line_to(x + ATTRIBUTE_RADIUS*4, y + ATTRIBUTE_RADIUS/2);
		ptrContext->stroke_preserve();
	}
	if (m_component->getOptions()[2]) {
		ptrContext->unset_dash();
		ptrContext->set_source_rgb(0.3, 0.3, 0.3);
		ptrContext->set_line_width(ANCHO_DE_LINEA*0.5);
		ptrContext->move_to(x - ATTRIBUTE_RADIUS*2, y + ATTRIBUTE_RADIUS);
		ptrContext->line_to(x + ATTRIBUTE_RADIUS*4, y + ATTRIBUTE_RADIUS);
		ptrContext->stroke_preserve();
	}
	ptrContext->set_source_rgb(COLOR_COMPONENT);
	ptrContext->fill();
	ptrContext->restore();
	VisualCompositeComponent::draw( ptrContext);

}
