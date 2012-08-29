#include "gui/SubWindow/SubdiagramButton.h"
#include "gui/VisualComponents/VisualComponentSubdiagram.h"
#include <iostream>
#include "gui/SubWindow/Workspace.h"
#include "gui/Handler/HandlerCreateComponent.h"

bool SubdiagramButton::on_button_press_event(GdkEventButton* event) {

	return true;
}

void SubdiagramButton::setTabs(Tabs* t){
	m_tabs = t;
}
