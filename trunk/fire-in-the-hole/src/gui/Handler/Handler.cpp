#include "gui/Handler/Handler.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/Handler/HandlerDefault.h"

Handler::Handler( DrawingAreaPlusPlus* drawArea) {
	m_drawArea = drawArea;
}

Handler::~Handler() { }

void Handler::on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent){ }

void Handler::on_left_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){ }

void Handler::on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){ }

void Handler::on_key_release_event(GdkEventKey* event, VisualCompositeComponent* touchedComponent){ }

void Handler::on_key_press_event(GdkEventKey* event, VisualCompositeComponent* touchedComponent, Tabs* tabs){
	m_drawArea->setHandler( new HandlerDefault(m_drawArea));
}

void Handler::on_right_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){

}

void Handler::on_right_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){

}
