#ifndef BARRADEHERRAMIENTAS_H_
#define BARRADEHERRAMIENTAS_H_

#include <gtkmm/buttonbox.h>
#include <string>
#include <ostream>
#include <iostream>
#include <gtkmm/builder.h>
#include "gui/Dibujar/AuxiliarDibujar.h"
#include "gui/SubWindow/SubdiagramButton.h"
#include "gtkmm-2.4/gtkmm/button.h"
#include "gtkmm-2.4/gtkmm/buttonbox.h"
#include "gui/SubWindow/DrawingAreaPlusPlus.h"
#include "gui/Handler/HandlerCreateComponent.h"

#define CANTIDAD_BOTONES 5

class Workspace;
class Tabs;

/**
 * Representa la barra de botones que contendra los componentes para crear (ENTIDAD, ATRIBUTO, etc).
 */
class BarraDeHerramientas : public Gtk::VButtonBox {
private:
	Gtk::Button m_buttons[CANTIDAD_BOTONES];
	Gtk::Image* m_images[CANTIDAD_BOTONES];

	SubdiagramButton m_diagramButton;

	Tabs* m_tabs;

public:
	/*
	 * Se debe setear los tabs. Sino la clase tendra un comportamiento erratico.
	 */
	BarraDeHerramientas();

	void setTabs( Tabs* tabs);

	virtual ~BarraDeHerramientas();

	template< typename T > void createVisualComponent();

};

#endif /* BARRADEHERRAMIENTAS_H_ */
