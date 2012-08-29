#include "gui/VisualComponents/VisualComponentSubdiagram.h"
#include "gui/VisualComponents/VisualComponentConector.h"
#include "xml/XmlReader.h"

VisualComponentSubdiagram::VisualComponentSubdiagram(Diagram* diagram, const std::string & xml) :
VisualCompositeComponent(diagram),	m_xml(xml) {
	m_component = new Subdiagram();
	if(m_xml != "")
		crear();
}

VisualComponentSubdiagram::	VisualComponentSubdiagram( Diagram* diagram, Diagram* sourceDiagram, const std::string & name, std::vector< VisualCompositeComponent* >* components, bool source) :
VisualCompositeComponent(diagram) {
	m_component = new Subdiagram(name);
	m_components = components;
}

VisualComponentSubdiagram::VisualComponentSubdiagram(const VisualComponentSubdiagram& other) : VisualCompositeComponent(other.m_diagram) {
	m_component = new Subdiagram(*(Subdiagram*)other.m_component);
	initialize();
}

VisualCompositeComponent* VisualComponentSubdiagram::getCopy(Diagram* diagram){
	Diagram* origen = m_diagram;
	m_diagram = diagram;
	VisualCompositeComponent* comp = new VisualComponentSubdiagram(*this);
	m_diagram = origen;
	return comp;
}

InfluenceArea VisualComponentSubdiagram::getInfluenceArea() {

	return InfluenceRectangle( getX(), getY(), getX() + getSubdiagram()->getSizeY() * PROP_SUBDIAGRAM +
		2 * CONECTOR_RADIUS, getY() + getSubdiagram()->getSizeY() * PROP_SUBDIAGRAM + 2* CONECTOR_RADIUS);
}

void VisualComponentSubdiagram::showProperties(){
}

void VisualComponentSubdiagram::crear() {
	XmlReader xmlReader(m_xml.c_str(), m_xml.size());
	initialize();
}

void VisualComponentSubdiagram::load(XmlReader& reader, Diagram* diagram){
	VisualCompositeComponent::load(reader, diagram);
	//Luego de cargar la cantidad de entradas y salidas se inicializan los conectores
	initialize();
}


void VisualComponentSubdiagram::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
	ptrContext->save();

	int x = getX();
	int y = getY();
	int sizeLine = getSubdiagram()->getSizeY() * PROP_SUBDIAGRAM;
	int offsetToCenter = getYCenter();

	if (m_selected)
		ptrContext->set_source_rgb(0, 1, 0);
	else
		ptrContext->set_source_rgb(0, 0, 0);
	ptrContext->set_line_width(ANCHO_DE_LINEA);

	ptrContext->translate(x + offsetToCenter, y + offsetToCenter);
	ptrContext->rotate_degrees(getSubdiagram()->getType());
	ptrContext->translate(-(x + offsetToCenter), -(y + offsetToCenter));

	ptrContext->rectangle(x + CONECTOR_RADIUS, y, sizeLine, sizeLine);
	ptrContext->stroke_preserve();
	ptrContext->set_source_rgb(258, 195, 195);
	ptrContext->fill();

	ptrContext->restore();
	VisualCompositeComponent::draw( ptrContext);
}
