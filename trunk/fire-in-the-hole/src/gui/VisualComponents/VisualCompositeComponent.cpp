#include "gui/VisualComponents/VisualCompositeComponent.h"
#include "gui/VisualComponents/VisualComponentConector.h"
#include "gui/VisualComponents/VisualComponentVia.h"
#include "model/Utils.h"
#include "model/Diagram.h"
#include "gui/SubWindow/ViewModifyComponentInfoWin.h"

VisualCompositeComponent::VisualCompositeComponent(Diagram* diagram) : m_diagram(diagram){
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

void VisualCompositeComponent::addView(VisualCompositeComponent* view) {
	m_views.push_back(view);
}

void VisualCompositeComponent::removeChild(VisualComponent* child) {
	for (std::vector<VisualComponent*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		if ((*it) == child) {
			m_children.erase(it);
			return;
		}
}

void VisualCompositeComponent::on_expose(Cairo::RefPtr<Cairo::Context> ptrContext) {
	update();
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

void VisualCompositeComponent::load(XmlReader& reader, Diagram* diagram){
	m_component->deserialize(reader);
}

void VisualCompositeComponent::store(XmlWriter& writer_rep, XmlWriter& writer_comp, Diagram* diagram) {
	xmlNode* nodoActual;
	//m_component->update();
	nodoActual = writer_comp.getCurrentNode();
	m_component->serialize(writer_rep, writer_comp);
	Utils utils;
	writer_rep.addCurrentNodeProperty(TARGET_ID, utils.convertToString(diagram->getId(m_component)).c_str());

	std::string tipo = typeid(*m_component).name();
	//std::cout << "Componente: " << tipo << std::endl;

	if (m_component->getName() != "Via"){
		if (tipo.substr(1,9) != "Attribute"){
			writer_comp.addCurrentNodeProperty(TARGET_ID, utils.convertToString(diagram->getId(m_component)).c_str());
			if (tipo.substr(1,6) == "Entity")
				serializedAttributes(writer_comp, diagram, m_component);
		}
		writer_comp.setCurrentNode(nodoActual);
	}
	diagram->serializeConnectedComponents(m_component, writer_rep);
/*	xmlNode* nodoActual;
	for(unsigned i = 0; i < connectors.size(); i++){
		nodoActual = connectors[i]->getVia() != NULL ?
			writer.addCurrentNodeChild(connectors[i]->getVia()->getName().c_str(), "") :
			writer.addCurrentNodeChild(TARGET_VACIO, "");
		Utils utils;
		writer.addProperty(nodoActual, TARGET_ID, utils.convertToString(getId(connectors[i]->getVia())).c_str());
*/	xmlNode* nodoActual2;
	for (std::vector<VisualCompositeComponent*>::iterator it = m_views.begin(); it != m_views.end(); ++it) {
		Component* viewComp = (*it)->getComponent();
		Diagram* otherDiagram = (*it)->getDiagram();
		nodoActual2 = writer_rep.addCurrentNodeChild(TARGET_OTHER_DIAGRAM, "");
		writer_rep.addProperty(nodoActual2, TARGET_NAME, otherDiagram->getName().c_str());
		writer_rep.addProperty(nodoActual2, TARGET_ID, utils.convertToString(otherDiagram->getId(viewComp)).c_str());
	}
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

Diagram* VisualCompositeComponent::getDiagram(){
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

void VisualCompositeComponent::update(){
	for (std::vector<VisualCompositeComponent*>::iterator it = m_views.begin(); it != m_views.end(); ++it) {
		Component* viewComp = (*it)->getComponent();
		viewComp->setName(m_component->getName());
		viewComp->setType(m_component->getType());
		viewComp->setExpression(m_component->getExpression());
		if(viewComp->getOptions().size() > 0) {
			viewComp->getOptions()[0] = m_component->getOptions()[0];
			viewComp->getOptions()[1] = m_component->getOptions()[1];
			viewComp->getOptions()[2] = m_component->getOptions()[2];
		}
	}

}
