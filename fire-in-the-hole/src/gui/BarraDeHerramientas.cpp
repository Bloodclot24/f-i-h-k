#include "gui/BarraDeHerramientas.h"
#include "gui/VisualComponents/VisualComponentEntity.h"
#include "gui/VisualComponents/VisualComponentSubdiagram.h"
#include "gui/VisualComponents/VisualComponentAttribute.h"
#include "gui/VisualComponents/VisualComponentCompositeAttribute.h"
#include "gui/VisualComponents/VisualComponentRelation.h"
#include "gui/VisualComponents/VisualComponentForkVia.h"
#include <iostream>
#include "gui/Tabs.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/SubWindow/Workspace.h"
#include "utils/Settings.h"

BarraDeHerramientas::BarraDeHerramientas() : Gtk::VButtonBox(Gtk::BUTTONBOX_START) {
	std::string buttonNames[] = { "ATRIBUTO", "RELACION", "ENTIDAD", "AT_COMPUESTO", "FORK"};
	unsigned size = CANTIDAD_BOTONES;

	std::string pathToImages = Settings::getInstance().getValue("ImagesPath");

	for ( unsigned i=0 ; i<size ; i++) {
		pack_start(m_buttons[i], false, false, 0);
		m_buttons[i].set_label(buttonNames[i]);
		m_images[i] = new Gtk::Image(pathToImages + buttonNames[i] + ".png");
		m_images[i]->show();
		m_buttons[i].set_image_position(Gtk::POS_TOP);
		m_buttons[i].set_image(*m_images[i]);
	}

	m_buttons[0].signal_pressed().connect(sigc::mem_fun(this, &BarraDeHerramientas::createVisualComponent<VisualComponentAttribute>));
	m_buttons[1].signal_pressed().connect(sigc::mem_fun(this, &BarraDeHerramientas::createVisualComponent<VisualComponentRelation>));
	m_buttons[2].signal_pressed().connect(sigc::mem_fun(this, &BarraDeHerramientas::createVisualComponent<VisualComponentEntity>));
	m_buttons[3].signal_pressed().connect(sigc::mem_fun(this, &BarraDeHerramientas::createVisualComponent<VisualComponentCompositeAttribute>));
	m_buttons[4].signal_pressed().connect(sigc::mem_fun(this, &BarraDeHerramientas::createVisualComponent<VisualComponentForkVia>));

	//Se agregan los botones "especiales".
	pack_start(m_diagramButton, false, false, 0);
}

BarraDeHerramientas::~BarraDeHerramientas() {
	for ( unsigned i=0 ; i<CANTIDAD_BOTONES ; i++)
		delete m_images[i];
}

void BarraDeHerramientas::setTabs( Tabs* tabs){
	m_tabs = tabs;
	m_diagramButton.setTabs(tabs);
}

template< typename T >
void BarraDeHerramientas::createVisualComponent(){
	Workspace* currentWorkspace = m_tabs->getCurrentWorkspace();
	if ( currentWorkspace == NULL)
		return;
	HandlerCreateComponent* handler = new HandlerCreateComponent(currentWorkspace, new T(*currentWorkspace->getDiagram()));
	currentWorkspace->setHandler(handler);
	for( unsigned i=0 ; i<CANTIDAD_BOTONES ; i++){
		m_buttons[i].get_display()->pointer_ungrab(NULL);
	}
}
