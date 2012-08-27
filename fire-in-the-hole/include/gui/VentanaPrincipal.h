#ifndef VENTANAPRINCIPAL_H_
#define VENTANAPRINCIPAL_H_

#include <gtkmm/window.h>
#include "SubWindow/SubVentana.h"
#include "BarraDeHerramientas.h"
#include "BarraDeMenu.h"
#include "Tabs.h"
#include "VentanaPrincipal.h"

#define TITULO "Editor de diagramas"

/**
 * @brief Representa la ventana principal del programa.
 */
class VentanaPrincipal : public Gtk::Window {
private:
	BarraDeHerramientas barraDeHerramientas;
	BarraDeMenu barraDeMenu;
	Tabs* tabs;
	Gtk::VBox separadorPrincipal;
	Gtk::HBox separadorTabsAndButtons;

public:
	VentanaPrincipal();

	virtual ~VentanaPrincipal();

	bool on_asd_key_release_event(GdkEventKey* event);

	bool on_asd_key_press_event(GdkEventKey* event);
};

#endif /* VENTANAPRINCIPAL_H_ */
