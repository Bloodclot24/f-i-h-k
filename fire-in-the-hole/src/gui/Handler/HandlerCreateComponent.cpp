#include "gui/Handler/HandlerCreateComponent.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/Handler/HandlerDefault.h"

HandlerCreateComponent::HandlerCreateComponent(DrawingAreaPlusPlus* drawArea, VisualCompositeComponent* comp) :
Handler(drawArea){
	m_vComponent = comp;
	m_vComponent->setSelected(true);
	m_drawArea->addVisualComponent(comp);
}

HandlerCreateComponent::~HandlerCreateComponent() {
	m_vComponent->setSelected(false);
	m_drawArea->reDraw();
}

void HandlerCreateComponent::on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent){
	m_vComponent->on_move(event->x, event->y);
	m_drawArea->reDraw();
}

void HandlerCreateComponent::on_left_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){
	m_drawArea->setHandler( new HandlerDefault(m_drawArea));
}

void HandlerCreateComponent::on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent){
	m_drawArea->setHandler(new HandlerDefault(m_drawArea));
}
