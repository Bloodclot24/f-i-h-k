#include "gui/SubWindow/SubdiagramButton.h"
#include "gui/VisualComponents/VisualComponentSubdiagram.h"
//#include "gui/SubWindow/PedirDatodChip.h"
#include <iostream>
#include "gui/SubWindow/Workspace.h"
#include "gui/Handler/HandlerCreateComponent.h"

bool SubdiagramButton::on_button_press_event(GdkEventButton* event) {
/*	if ( m_tabs->getCurrentWorkspace() == NULL)
		return true;

	PedirDatosChip pedirDatos;
	if (pedirDatos.pedir(m_xml))
		if (m_xml != "") {
			m_ipPort = pedirDatos.getIpPort();
			VisualComponentSubdiagram* vChip = new VisualComponentSubdiagram(*m_tabs->getCurrentWorkspace()->getDiagram(), m_xml);
			m_tabs->getCurrentWorkspace()->setHandler( new HandlerCreateComponent(m_tabs->getCurrentWorkspace(), vChip));
			vChip->getChip()->setIp(m_ipPort.getT1());
			vChip->getChip()->setPort(m_ipPort.getT2());
		}
	get_display()->pointer_ungrab(NULL);
*/
	return true;
}

void SubdiagramButton::setTabs(Tabs* t){
	m_tabs = t;
}
