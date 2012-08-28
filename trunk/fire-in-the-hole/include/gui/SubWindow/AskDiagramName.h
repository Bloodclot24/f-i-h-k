#ifndef ASKDIAGRAMNAME_H_
#define ASKDIAGRAMNAME_H_

#include <iostream>
#include "gtkmm/dialog.h"
#include "gtkmm/entry.h"
#include "gtkmm/label.h"
#include "gtkmm/frame.h"

/**
 * @brief Clase que despiega una ventana donde se le pide al usuario que
 * ingrese el nombre del diagrama. Para obtener el valor ingresado
 * se debe llamar a askName que despiega la ventana y devuelve el valor.
 */

class AskDiagramName {
public:
	AskDiagramName(std::string name);
	virtual ~AskDiagramName();
	/**
	 * @brief despliega una ventana que pide al usuario el nombre del diagrama.
	 * @return
	 */
	std::string askName();

private:
	Gtk::Dialog m_dialog;
	Gtk::Entry m_nameEntry;
	Gtk::Label m_label;

};

#endif /* ASKDIAGRAMNAME_H_ */
