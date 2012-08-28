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

	Workspace* workspace;
    //Estructura.
    Gtk::HBox boxInicial;
    Gtk::VBox boxHomogenea;

    //Workspace
    Gtk::ScrolledWindow scrollWorkspace;
    Gtk::Adjustment ajusteHorizontal, ajusteVertical;
    Gtk::Viewport adaptador;


public:
	/**
	 * Constructor.
	 *
	 * @param Diagrama
	 * @param control
	 * @param allocation
	 */
	SubVentana(Diagram* diagram, Gtk::Allocation allocation);

	virtual ~SubVentana() {
		delete workspace;
	}

    Workspace* getWorkspace() {
        return workspace;
    }

    Diagram* getDiagram() {
    	return workspace->getDiagram();
    }
};

#endif /* SUBVENTANA_H_ */
