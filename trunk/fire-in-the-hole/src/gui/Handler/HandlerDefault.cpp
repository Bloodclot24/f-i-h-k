#include "gui/Handler/HandlerDefault.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/Handler/HandlerSelected.h"
#include "gui/Handler/HandlerCreateSelection.h"
#include "gui/Handler/HandlerConnectComponents.h"
#include "gui/Handler/HandlerEditSegments.h"
#include <gdkmm-2.4/gdkmm.h>

HandlerDefault::HandlerDefault( DrawingAreaPlusPlus* drawArea) : Handler(drawArea){
	m_lastTouched = NULL;
	m_lastComponentTouched = NULL;
}

HandlerDefault::~HandlerDefault(){
	if( m_lastTouched != NULL)
		m_lastTouched->setSelected(false);
	if ( m_lastComponentTouched != NULL)
		m_lastComponentTouched->setSelected(false);
}

void HandlerDefault::on_left_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){
	if (touchedComponent == NULL) {
		m_drawArea->setHandler(new HandlerCreateSelection(m_drawArea, event->x, event->y));
	} else {
		VisualComponent* subComp = touchedComponent->getTouchedSubVisualComponent(event->x,	event->y);
		if (subComp != NULL) {
			VisualComponentConector* conector = dynamic_cast<VisualComponentConector*>(subComp);
			if ( conector != NULL)
				m_drawArea->setHandler(new HandlerConnectComponents(m_drawArea, conector));
			else  // es un segmento.
				m_drawArea->setHandler( new HandlerEditSegments(m_drawArea, (VisualComponentVia*)touchedComponent, (VisualComponentSegment*)subComp));
		} else { //se clickeo sobre un componente
			std::vector<VisualCompositeComponent*>* vec = new std::vector<VisualCompositeComponent*>();
			vec->push_back(touchedComponent);
			m_drawArea->setHandler(new HandlerSelected(m_drawArea, vec));
		}
	}
}

void HandlerDefault::on_right_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){
	if ( touchedComponent != NULL){
		std::vector<VisualCompositeComponent*>* vec = new std::vector<VisualCompositeComponent*>();
		vec->push_back(touchedComponent);
		m_drawArea->setHandler(new HandlerSelected(m_drawArea, vec));
	}
}

void HandlerDefault::on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent){
	m_drawArea->get_window()->set_cursor();
	if ( m_lastComponentTouched != NULL)
		m_lastComponentTouched->setSelected(false);

	if (m_lastTouched != NULL)
		m_lastTouched->setSelected(false);

	if ( touchedComponent != NULL){
		touchedComponent->setSelected(true);
		m_lastComponentTouched = touchedComponent;
		m_lastTouched = touchedComponent->getTouchedSubVisualComponent(event->x, event->y);
		if ( m_lastTouched != NULL){
			m_lastTouched->setSelected(true);
			m_drawArea->get_window()->set_cursor(Gdk::Cursor(Gdk::HAND2));
		}
	}
	m_drawArea->reDraw();
}
