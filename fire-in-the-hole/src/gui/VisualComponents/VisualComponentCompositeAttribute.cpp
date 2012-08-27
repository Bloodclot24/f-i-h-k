#include "gui/VisualComponents/VisualComponentCompositeAttribute.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/SubWindow/ViewModifyAttributeInfoWin.h"

VisualComponentCompositeAttribute::VisualComponentCompositeAttribute( Diagram& diagram) : VisualCompositeComponent(diagram) {
	m_component = new CompositeAttribute();
	initialize();
}

VisualComponentCompositeAttribute::VisualComponentCompositeAttribute(const VisualComponentCompositeAttribute& other) : VisualCompositeComponent(other.m_diagram) {
	m_component = new CompositeAttribute(*(CompositeAttribute*)other.m_component);
	initialize();
}

VisualCompositeComponent* VisualComponentCompositeAttribute::getCopy(Diagram & diagram){
	Diagram & origen = m_diagram;
	m_diagram = diagram;
	VisualCompositeComponent* comp = new VisualComponentCompositeAttribute(*this);
	m_diagram = origen;
	return comp;
}


InfluenceArea VisualComponentCompositeAttribute::getInfluenceArea() {
	return InfluenceRectangle(getX(), getY(), getX() + COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF + 3, getY() + COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_YF + 3);
}

void VisualComponentCompositeAttribute::showProperties(){
	ViewModifyAttributeInfoWin dialog(m_component);
	dialog.run();
	return;
}

void VisualComponentCompositeAttribute::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
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
	ptrContext->arc(x + CONECTOR_RADIUS + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 2, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_YF) / 2 + CONECTOR_RADIUS,  (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 2, -M_PI, M_PI);
	ptrContext->stroke_preserve();

	if (m_component->getOptions()[0]) {
		ptrContext->unset_dash();
		ptrContext->set_source_rgb(0, 0, 0);
		ptrContext->set_line_width(ANCHO_DE_LINEA*2);
		ptrContext->move_to(x - (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 2 - 6, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 1.5);
		ptrContext->line_to(x + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) * 2 - 6, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 1.5);
		ptrContext->stroke_preserve();
	}
	if (m_component->getOptions()[1]) {
		ptrContext->unset_dash();
		ptrContext->set_source_rgb(0, 0, 0);
		ptrContext->set_line_width(ANCHO_DE_LINEA*0.6);
		ptrContext->move_to(x - (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 2 - 6, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 1.25);
		ptrContext->line_to(x + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) * 2 - 6, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 1.25);
		ptrContext->stroke_preserve();
	}
	if (m_component->getOptions()[2]) {
		ptrContext->unset_dash();
		ptrContext->set_source_rgb(0.3, 0.3, 0.3);
		ptrContext->set_line_width(ANCHO_DE_LINEA*0.5);
		ptrContext->move_to(x - (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 2 - 6, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 1.1);
		ptrContext->line_to(x + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) * 2 - 6, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 1.1);
		ptrContext->stroke_preserve();
	}

	ptrContext->set_source_rgb(COLOR_COMPONENT);
	ptrContext->fill();

	ptrContext->restore();
	VisualCompositeComponent::draw( ptrContext);
	Draw draw;
	draw.writeTextInContext(ptrContext, x + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 2, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_YF) / 1.5, m_component->getName(), COLOR_IN_TEXT);
	if(m_component->getExpression() != "")
		draw.writeTextInContext(ptrContext, x + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_XF) / 2, y + (COMPOSITEATTRIBUTE_INFLUENCE_RECTANGLE_YF)*1.6, m_component->getExpression(), COLOR_LINE_COMPONENTS);
}
