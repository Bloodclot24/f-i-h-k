#ifndef SUBVENTANA_H_
#define SUBVENTANA_H_

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include <gtkmm/label.h>
#include <gtkmm/separator.h>
#include "Workspace.h"
#include "../../model/Diagram.h"

/**
 * @brief Representa una subventana.
 * Una subventana es la parte visible de cada proyecto, la misma cuenta de:
 * 	-Workspace
 * 	-Pila de acciones
 */
class SubVentana : public Gtk::VBox {
private:
    Diagram & m_diagram;

    //Estructura.
    Gtk::HBox boxInicial;
    Gtk::VBox boxHomogenea;

    //Workspace
    Gtk::ScrolledWindow scrollWorkspace;
    Gtk::Adjustment ajusteHorizontal, ajusteVertical;
    Gtk::Viewport adaptador;
    Workspace workspace;

public:
	/**
	 * Constructor.
	 *
	 * @param Diagrama
	 * @param control
	 * @param allocation
	 */
	SubVentana(Diagram& diagram, Gtk::Allocation allocation);

    Workspace* getWorkspace() {
        return &workspace;
    }

    Diagram* getDiagram() {
    	return &m_diagram;
    }
};

#endif /* SUBVENTANA_H_ */
