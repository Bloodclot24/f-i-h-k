#include "gui/Handler/HandlerConnectComponents.h"
#include "gui/VisualComponents/VisualComponentVia.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/Handler/HandlerDefault.h"
#include <gtkmm-2.4/gtkmm/messagedialog.h>
#include "gui/VisualComponents/VisualComponentSegment.h"

HandlerConnectComponents::HandlerConnectComponents(DrawingAreaPlusPlus* drawArea, VisualComponentConector* conector) :
Handler(drawArea){
	m_conector = conector;
	m_destinyConnector = NULL;
	m_conector->getParent()->setSelected(true);
	m_drawArea->setConnectingLine( new VisualComponentSegment(
			new Point(conector->getX() + conector->getXCenter(), conector->getY() + conector->getYCenter()),
			new Point(conector->getX() + conector->getXCenter(), conector->getY()  + conector->getYCenter()), false));
	m_drawArea->reDraw();
}

HandlerConnectComponents::~HandlerConnectComponents() {
	m_conector->getParent()->setSelected(false);
	if ( m_destinyConnector != NULL){
		m_destinyConnector->setSelected(false);
		m_destinyConnector->getParent()->setSelected(false);
	}
	m_drawArea->reDraw();
}

void HandlerConnectComponents::on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent){
	if ( m_destinyConnector != NULL){
		m_destinyConnector->setSelected(false);
		m_destinyConnector->getParent()->setSelected(false);
		m_destinyConnector = NULL;
	}
	if ( touchedComponent != NULL){
    	m_destinyConnector = dynamic_cast< VisualComponentConector* >(touchedComponent->getTouchedSubVisualComponent(event->x, event->y));
    	if ( m_destinyConnector != NULL){
    		m_destinyConnector->setSelected(true);
    		m_destinyConnector->getParent()->setSelected(true);
    	}
    }
    m_drawArea->getConnectingLine()->getEndPoint()->setX(event->x);
	m_drawArea->getConnectingLine()->getEndPoint()->setY(event->y);
	m_drawArea->reDraw();
}

void HandlerConnectComponents::on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){
	if ( touchedComponent != NULL && touchedComponent->getTouchedSubVisualComponent(event->x, event->y) != NULL){
		VisualComponentConector* onDroppedConnector = dynamic_cast< VisualComponentConector* >(touchedComponent->getTouchedSubVisualComponent(event->x, event->y));
		if ( onDroppedConnector == NULL){
			m_drawArea->setConnectingLine(NULL);
			m_drawArea->setHandler( new HandlerDefault(m_drawArea));
			return;
		}

			if ( m_conector->getParent() != onDroppedConnector->getParent() && onDroppedConnector->getVia() == NULL && m_conector->getVia() == NULL){
				VisualComponentVia* via = new VisualComponentVia(m_conector, m_conector->getParent()->getDiagram(), onDroppedConnector);
				m_conector->setVia(via);
				onDroppedConnector->setVia(via);
				m_drawArea->addVisualComponent(via);
			} else {
				Gtk::MessageDialog error("Líneas muy juntas. Intente nuevamente dejando mas espacio entre extremos.");
				error.run();
			}
	}
	m_drawArea->setConnectingLine(NULL);
	m_drawArea->setHandler( new HandlerDefault(m_drawArea));
}
