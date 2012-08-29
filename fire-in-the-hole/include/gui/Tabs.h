#ifndef TABS_H_
#define TABS_H_

#include <gtkmm/notebook.h>
#include <vector>
#include "SubWindow/SubVentana.h"
#include "BarraDeMenu.h"

class Workspace;
/**
 * @brief Representa a la barra de tabs, que encapsula una serie de ventanas y
 * permite la multiple edicion de las mismas. Se encarga de manejar eventos como
 * abrir nuevos tabs, cerrar, cargar archivos, etc.
 */
class Tabs : public Gtk::Notebook {
private:
	BarraDeMenu& barraDeMenu;
	std::vector<SubVentana*> subVentanas;
	bool m_active;
	std::string m_proyectName;

	void save_all();

public:
	Tabs(BarraDeMenu& barraDeMenu);

	virtual ~Tabs();

	/**
	 * @brief Crea y agrega una nueva subVentana
	 * @param diagram: diagrama correspondiente a la nueva subventana
	 */
	void agregarSubVentana(Diagram* diagram = NULL);

	/**
	 * Remueve la subVentana actual.
	 */
	void removerSubVentanaActual();


	/**
	 * Evento que se dispara al cambiar el tab, se debe llamar asi por
	 * problemas con GTK
	 * @param page
	 * @param page_num
	 */
	void on_switch_page_fake(GtkNotebookPage* page, guint page_num);

	/**
	 * Cierra la subventana acutal, removiendola de la coleccion de tabs
	 */
	void on_menu_close();

	/**
	 * Abre y agrega una subventana a los tabs
	 */
	void on_menu_new();

	/**
	 *
	 */
	void on_menu_new_proyect();

	/**
	 * Permite elegir y abrir un archivo correspondiente a un diagrama
	 * ya cargado.
	 */
	void on_menu_open();

	/**
	 *
	 */
	void on_menu_open_proyect();

	/**
	 *
	 */
	void on_menu_close_proyect();

	/**
	 * Metodos que guardan el diagrama correspondiente a la subventana actual.
	 */
	void on_menu_save();

	void on_name_change();

	virtual bool on_key_release_event(GdkEventKey* event);

	virtual bool on_key_press_event(GdkEventKey* event);

	Workspace* getCurrentWorkspace();

	void setActive(bool active) {
		m_active = active;
	}

	Workspace* getWorkspace(Diagram* diagram);
	Workspace* getWorkspace(std::string name) {
		for(unsigned i = 0; i < subVentanas.size(); i++){
			if(strcmp(subVentanas[i]->getDiagram()->getName().c_str(),name.c_str()) == 0)
				return subVentanas[i]->getWorkspace();
		}
		return NULL;
	}
};

#endif /* TABS_H_ */
