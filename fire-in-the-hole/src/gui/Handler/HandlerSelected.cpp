#include "gui/Handler/HandlerSelected.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/Handler/HandlerDefault.h"
#include "gui/VisualComponents/VisualComponentVia.h"
#include "gui/Handler/HandlerCreateSelection.h"
#include "gui/Handler/HandlerEditSegments.h"
#include "gui/Handler/HandlerConnectComponents.h"
#include <gtkmm-2.4/gtkmm/messagedialog.h>
#include <list>
#include <map>


HandlerSelected::HandlerSelected( DrawingAreaPlusPlus* drawArea, std::vector< VisualCompositeComponent* >* selection, bool multipleSelection) :
Handler(drawArea){

	m_selection = selection;
	m_clicked = !multipleSelection;
	selectAll(true);
	m_firstTime = true;
	m_drawArea->reDraw();
	m_popupCalledBefore = false;
	m_lastX = 0;
	m_lastY = 0;
}

HandlerSelected::~HandlerSelected() {
	selectAll(false);
	m_drawArea->reDraw();
	delete m_selection;
}

void HandlerSelected::on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent){
	//esto es por si no se clickeo en alguna opcion del popup
	if ( m_popupCalledBefore){
		m_drawArea->setHandler( new HandlerDefault(m_drawArea));
		return ;
	}

	if (m_clicked) {
		if (m_firstTime) {
			m_firstTime = false;
		} else {
			for (unsigned i = 0; i < m_selection->size(); i++) {
				VisualCompositeComponent* comp = (*m_selection)[i];
				selectAll(true);
				comp->on_move(comp->getX() + event->x - m_lastX , comp->getY() + event->y - m_lastY);
			}
		}
		m_lastX = event->x;
		m_lastY = event->y;
	}
	m_drawArea->reDraw();
}

void HandlerSelected::on_left_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){

	if (touchedComponent == NULL)
		m_drawArea->setHandler( new HandlerCreateSelection(m_drawArea, event->x, event->y));
	else if (!touchedComponent->isSelected()) {
		selectAll(false);
		m_selection->clear();
		touchedComponent->setSelected(true);
		m_selection->push_back(touchedComponent);
		m_firstTime = true;
		m_clicked = true;
		m_drawArea->reDraw();
	} else {
		m_clicked = true;
		VisualComponent* subComp = touchedComponent->getTouchedSubVisualComponent(event->x,	event->y);
		if (subComp != NULL) {
			VisualComponentConector* conector = dynamic_cast<VisualComponentConector*>(subComp);
			if ( conector != NULL)
				m_drawArea->setHandler(new HandlerConnectComponents(m_drawArea, conector));
			else
				m_drawArea->setHandler( new HandlerEditSegments(m_drawArea, (VisualComponentVia*)touchedComponent, (VisualComponentSegment*)subComp));
		}
	}
}

void HandlerSelected::on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){
	m_clicked = false;
}

void HandlerSelected::selectAll(bool select){
	for ( unsigned i=0 ; i<m_selection->size() ; i++)
		(*m_selection)[i]->setSelected(select);
}

void HandlerSelected::on_key_press_event(GdkEventKey* event, VisualCompositeComponent* touchedComponent){
	if ( event->keyval == DELETE)
		deleteSelection();
}

void HandlerSelected::on_right_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){

	if ( touchedComponent == NULL){
		m_drawArea->setHandler( new HandlerDefault(m_drawArea));
		return ;
	}

	if ( !touchedComponent->isSelected()){
		selectAll(false);
		m_selection->clear();
		touchedComponent->setSelected(true);
		m_selection->push_back(touchedComponent);
		m_clicked = true;
		m_drawArea->reDraw();
	}

	m_popup = dynamic_cast<Gtk::Menu*>(m_drawArea->getUIManager()->get_widget("/PopupMenu"));
	if ( m_popup != NULL){
		m_popup->popup(event->button, event->time);
		m_popupCalledBefore = true;
	}
}

void HandlerSelected::deleteSelection(){
	eraseSelection();
	m_drawArea->setHandler( new HandlerDefault(m_drawArea));
}

void HandlerSelected::eraseSelection(){
	std::vector<VisualCompositeComponent*> resto;
	//Borra primero las vias porque son las unicas que no tienen conectores propios
	for ( unsigned i=0 ; i < m_selection->size() ; i++ ) {
		VisualComponentVia* via = dynamic_cast<VisualComponentVia*>((*m_selection)[i]);
		if ( via != NULL) {
			m_drawArea->removeVisualComponent(via);
			delete via;
		} else
			resto.push_back((*m_selection)[i]);
	}

	//Borra las vias que no quedaron dentro de la seleccion pero que van a
	//quedar desconectadas en un extremo, recorriendo los conectores de la seleccion
	for ( unsigned i=0 ; i < resto.size() ; i++ ) {
		for ( unsigned j=0 ; j < resto[i]->getChildren().size() ; j++ ) {
			VisualComponentConector* conector = (VisualComponentConector*) resto[i]->getChildren()[j]; //son everythings conectores
			if(conector->getVia() != NULL) {
				m_drawArea->removeVisualComponent(conector->getVia());
				delete conector->getVia(); //setea los conectores de los extremos a NULL
			}
		}
		m_drawArea->removeVisualComponent(resto[i]);
		delete resto[i];
	}
	m_selection->clear();
}

bool HandlerSelected::onlyOneComponentSelected() {
	if(m_selection->size() != 1) {
		Gtk::MessageDialog error("Se debe seleccionar solo un componente para realizar la accion solicitaeda");
		error.run();
		return false;
	}
	return true;
}

void HandlerSelected::showProperties(){
	if ( m_selection->size() >= 1)
		m_selection->at(0)->showProperties();
	m_drawArea->reDraw();
}

void HandlerSelected::copy(bool add){
	std::vector< VisualCompositeComponent* >* newSelection = duplicateSelection();
	selectAll(false);
	delete m_selection;
	m_selection = newSelection;
	selectAll(true);
	m_drawArea->reDraw();
	//flags de control de seniales.
	m_popupCalledBefore = false;
	m_clicked = true;
}

void HandlerSelected::cut(){
	std::vector< VisualCompositeComponent* >* newSelection = duplicateSelection();
	eraseSelection();
	delete m_selection;
	m_selection = newSelection;
	selectAll(true);
	m_drawArea->reDraw();
	//flags de control de seniales.
	m_popupCalledBefore = false;
	m_clicked = true;
}

void HandlerSelected::createSubdiagram(){
	selectAll(false);
	m_drawArea->reDraw();
	//flags de control de seniales.
	m_popupCalledBefore = false;
	m_clicked = true;
}

std::vector< VisualCompositeComponent* >* HandlerSelected::duplicateSelection(bool add){
	std::map< VisualCompositeComponent* , VisualCompositeComponent* > index;
	std::list< VisualComponentVia* > originalVias;
	std::vector< VisualCompositeComponent* >* newSelection = new std::vector< VisualCompositeComponent* >();
	for ( std::vector< VisualCompositeComponent* >::iterator it=m_selection->begin() ; it!=m_selection->end() ; ++it) {
		VisualCompositeComponent* copy = (*it)->getCopy(*((Workspace*)m_drawArea)->getDiagram());
		VisualComponentVia* viaCopy = dynamic_cast< VisualComponentVia* >(copy);
		// si los conectores de la via estan seleccionados ==> esta se debe copiar.
		if ( viaCopy != NULL ){
			VisualComponentVia* originalVia = (VisualComponentVia*)(*it);
			if (originalVia->getStartConector()->getParent()->isSelected() &&
					originalVia->getEndConector()->getParent()->isSelected())
				originalVias.push_back(originalVia);
			else
				continue;
		}
		newSelection->push_back(copy);
		if(add)
			m_drawArea->addVisualComponent(copy);
		index[(*it)] = copy;
	}

	//Ahora conectamos las vias nuevas con los nuevos componentes.
	for ( std::list< VisualComponentVia* >::iterator it=originalVias.begin() ; it!=originalVias.end() ; ++it){
		VisualComponentVia* newVia = (VisualComponentVia*) index[(*it)];
		VisualComponentConector* AttributeConnector = obtainCopyConnector((*it)->getStartConector(), index);
		VisualComponentConector* exitConnector = obtainCopyConnector((*it)->getEndConector(), index);
		AttributeConnector->setVia(newVia);
		exitConnector->setVia(newVia);
		newVia->setStartConector(AttributeConnector);
		newVia->setEndConector(exitConnector);
	}
	return newSelection;
}

VisualComponentConector* HandlerSelected::obtainCopyConnector(VisualComponentConector* connector,
		std::map< VisualCompositeComponent* , VisualCompositeComponent* > & index) {

	for(unsigned i = 0; i < connector->getParent()->getChildren().size(); i++){
		if(connector == connector->getParent()->getChildren()[i])
			return (VisualComponentConector*) ( index[ connector->getParent() ]->getChildren()[i] );
	}
	return NULL;
}
