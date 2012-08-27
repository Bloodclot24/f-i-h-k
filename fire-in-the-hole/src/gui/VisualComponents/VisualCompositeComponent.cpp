#include "gui/VisualComponents/VisualCompositeComponent.h"
#include "gui/VisualComponents/VisualComponentConector.h"
#include "gui/VisualComponents/VisualComponentVia.h"
#include "model/Utils.h"
#include "model/Diagram.h"
#include "gui/SubWindow/ViewModifyComponentInfoWin.h"

VisualCompositeComponent::VisualCompositeComponent(Diagram& diagram) : m_diagram(diagram){
	m_selected = false;
}

VisualCompositeComponent::VisualCompositeComponent(const VisualCompositeComponent &other) :
m_diagram( other.m_diagram){
	m_selected = false;
}


VisualCompositeComponent::~VisualCompositeComponent() {
	for (std::vector<VisualComponent*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		delete (*it);
	m_component->removeFromDiagram(m_diagram);
}

void VisualCompositeComponent::initialize() {
	m_component->addToDiagram(m_diagram);

	for(unsigned i = 0; i < m_component->getAttributeConnectors()->size(); i++)
		addChild(new VisualComponentConector(this, (*m_component->getAttributeConnectors())[i], i, true, m_diagram));
	for(unsigned i = 0; i < m_component->getExitConnectors()->size(); i++)
		addChild(new VisualComponentConector(this,(*m_component->getExitConnectors())[i], i, false, m_diagram));
}

void VisualCompositeComponent::addChild(VisualComponent* child) {
	m_children.push_back(child);
}

void VisualCompositeComponent::removeChild(VisualComponent* child) {
	for (std::vector<VisualComponent*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		if ((*it) == child) {
			m_children.erase(it);
			return;
		}
}

void VisualCompositeComponent::on_expose(Cairo::RefPtr<Cairo::Context> ptrContext) {
	draw(ptrContext);
}

void VisualCompositeComponent::on_move(int mouseX, int mouseY) {
	m_component->setX(mouseX);
	m_component->setY(mouseY);
	for (std::vector<VisualComponent*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->on_move(mouseX, mouseY);
}

VisualComponent* VisualCompositeComponent::getTouchedSubVisualComponent(int x, int y) {
	for (std::vector<VisualComponent*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		if ((*it)->getInfluenceArea().touch(x, y))
			return (*it);
	return NULL;
}

void VisualCompositeComponent::draw(Cairo::RefPtr<Cairo::Context> ptrContext){
	for (std::vector<VisualComponent*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		(*it)->draw(ptrContext);
}

void VisualCompositeComponent::load(XmlReader& reader, Diagram & diagram){
	m_component->deserialize(reader);
}

void VisualCompositeComponent::store(XmlWriter& writer_rep, XmlWriter& writer_comp, Diagram & diagram) {
	xmlNode* nodoActual;
	//m_component->update();
	nodoActual = writer_comp.getCurrentNode();
	m_component->serialize(writer_rep, writer_comp);
	Utils utils;
	writer_rep.addCurrentNodeProperty(TARGET_ID, utils.convertToString(diagram.getId(m_component)).c_str());

	std::string tipo = typeid(*m_component).name();
	//std::cout << "Componente: " << tipo << std::endl;

	if (m_component->getName() != "Via"){
		if (tipo.substr(1,9) != "Attribute"){
			writer_comp.addCurrentNodeProperty(TARGET_ID, utils.convertToString(diagram.getId(m_component)).c_str());
			if (tipo.substr(1,6) == "Entity")
				serializedAttributes(writer_comp, &diagram, m_component);
		}
		writer_comp.setCurrentNode(nodoActual);
	}
	diagram.serializeConnectedComponents(m_component, writer_rep);
}

void VisualCompositeComponent::setX(int x){
	m_component->setX(x);
}

void VisualCompositeComponent::setY(int y){
	m_component->setY(y);
}

int VisualCompositeComponent::getX() const {
	return m_component->getX();
}

int VisualCompositeComponent::getY() const{
	return m_component->getY();
}

void VisualCompositeComponent::showProperties(){
	ViewModifyComponentInfoWin dialog(m_component);
	dialog.run();
	return;
}

Diagram& VisualCompositeComponent::getDiagram(){
	return m_diagram;
}

void VisualCompositeComponent::serializedAttributes(XmlWriter & xml, Diagram * diagram, Component * component){

	xmlNode* nodoActual;
	Utils utils;

	m_component->update();

	std::string tipo;

	for (std::vector<Attribute*>::iterator it = component->getAtrributes()->begin(); it != component->getAtrributes()->end(); ++it)
	{
		tipo = typeid(**it).name();
		if (tipo.substr(1,8) != "Relation"){
			nodoActual = xml.addCurrentNodeChild("atributo", "");
			xml.addProperty(nodoActual, TARGET_ID, utils.convertToString(diagram->getId(*it)).c_str());
			xml.addProperty(nodoActual, TARGET_NAME, (*it)->getName().c_str());
		}
	}
}
