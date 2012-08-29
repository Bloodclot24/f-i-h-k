#ifndef WORKSPACE_H_
#define WORKSPACE_H_

#include <gtkmm/drawingarea.h>
#include <gtkmm/printcontext.h>
#include <gtkmm/printoperation.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "../Dibujar/Defines.h"
#include "../Dibujar/AuxiliarDibujar.h"
#include "../../model/Diagram.h"
#include "DrawingAreaPlusPlus.h"
#include "../VisualComponents/VisualComponentEntity.h"
#include <fstream>
#include <iostream>

class Tabs;
/**
 * @brief Lugar donde efectivamente se interactua con los VisualComponents.
 */
class Workspace : public DrawingAreaPlusPlus {
private:
	/**
	 * Sobre el cual trabaja este workspace.
	 */
	Diagram* m_diagram;
	int m_diagramOffsetX;
	int m_diagramOffsetY;

	Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
	Glib::RefPtr<Gtk::PrintSettings> m_refSettings;

public:
	Workspace(Diagram* diagram, bool enableEvents = true);

	virtual ~Workspace();

	/**
	 * Evento que se llama al pedir imprimir este workspace a PNG.
	 *
	 * @param archivo donde se creara el PNG.
	 */
	void imprimirAPng(std::string archivo);
	/**
	 * Evento que se llama al pedir imprimir este workspace a PDF.
	 *
	 * @param archivo donde se creara el PDF.
	 */
	void imprimirAPdf(std::string archivo);

	Diagram* getDiagram();

	void print_or_preview(Glib::RefPtr<Gtk::PrintOperation> print);
	void on_menu_file_page_setup();
	void on_menu_file_print_preview();
	void on_menu_file_print();
	void on_draw_page(const Glib::RefPtr< Gtk::PrintContext >& context, int page_nr);

	void validateDiagram(std::string archivo);

	/**
	 * Se llama al cargar un nuevo diagrama, debe instanciar los componentes.
	 */
	void on_load(XmlReader& reader, Tabs* tabs);

	void store(XmlWriter& writer_rep, XmlWriter& writer_comp);

	VisualCompositeComponent* getVisualComponent(Component*);

	 void updateDiagramSize();

	 /**
	  * Obtiene el tamano que ocupara el workspace en pixeles.
	  *
	  * @param sizeX
	  * @param sizeY
	  */
	 void getSize(double& sizeX, double& sizeY) {
		 updateDiagramSize();
		 sizeX = m_diagram->getSizeX() + m_diagramOffsetX;
		 sizeY = m_diagram->getSizeY() + m_diagramOffsetY;
	 }

	/**
	 * Obtiene el tamano del papel referenciado por m_refPageSetup.
	 *
	 * @param sizeX
	 * @param sizeY
	 */
	void getPageSize(double& sizeX, double& sizeY) {
		sizeY = m_refPageSetup->get_page_height(Gtk::UNIT_POINTS);
		sizeX = m_refPageSetup->get_page_width(Gtk::UNIT_POINTS);
	}

	VisualCompositeComponent* getVisualCompositeComponent(unsigned id) {
		return m_visualComponentList[id];
	}

};

#endif /* WORKSPACE_H_ */
