#include "gui/Handler/HandlerCreateSelection.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/Handler/HandlerDefault.h"
#include "gui/Handler/HandlerSelected.h"

HandlerCreateSelection::HandlerCreateSelection( DrawingAreaPlusPlus* drawArea, int mouseX, int mouseY) :
Handler(drawArea){
	m_mouseX = mouseX;
	m_mouseY = mouseY;
}

HandlerCreateSelection::~HandlerCreateSelection() {
	m_drawArea->setSelectionRectangle(NULL);
	m_drawArea->reDraw();
}


void HandlerCreateSelection::on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent){
	//dibujamos el cuadro de seleccion.
	InfluenceRectangle* rect= new InfluenceRectangle(m_mouseX, m_mouseY, event->x, event->y);
	m_drawArea->setSelectionRectangle(rect);
	m_drawArea->reDraw();
}

void HandlerCreateSelection::on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){
	int actualX = event->x, actualY = event->y;
	InfluenceArea selectedArea(InfluenceRectangle(m_mouseX, m_mouseY, actualX, actualY));
	std::vector< VisualCompositeComponent*>* selection = new std::vector< VisualCompositeComponent*>();
	m_drawArea->getTouchedVisualComponents(selectedArea, *selection);
	if( selection->size() == 0){
		m_drawArea->setHandler( new HandlerDefault(m_drawArea));
	} else {
		m_drawArea->setHandler( new HandlerSelected(m_drawArea, selection, true));
	}
}
