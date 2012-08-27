#ifndef DRAWINGAREAPLUSPLUS_H_
#define DRAWINGAREAPLUSPLUS_H_

#include <vector>
#include <gtkmm-2.4/gtkmm/viewport.h>
#include <gtkmm-2.4/gtkmm/adjustment.h>
#include <gtkmm-2.4/gtkmm/scrolledwindow.h>
#include <gtkmm-2.4/gtkmm/drawingarea.h>
#include <gdkmm-2.4/gdkmm/event.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/drawingarea.h>
#include "gui/Handler/Handler.h"
#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/menu.h>

class VisualCompositeComponent;
class VisualComponentSegment;

/**
 * @brief Representa una drawing area mejorada.
 * Representa una drawing area que permite adiccionalmente, agregar VisualComponent , @everything etc, etc, etc.
 */
class DrawingAreaPlusPlus : public Gtk::DrawingArea {
private:

	Handler* m_handler;
	InfluenceRectangle* m_selectionRectangle;
	VisualComponentSegment* m_connectingLine;
	Glib::RefPtr<Gtk::UIManager> m_UIManager;
	bool m_editable;

	void drawSelection(const Cairo::RefPtr<Cairo::Context> ptrContext, InfluenceRectangle& rectanguloDeInfluencia);

protected:
	/**
	 * Lista de componentes visuales que maneja la drawing area.
	 */
	std::vector<VisualCompositeComponent*> m_visualComponentList;
public:

	DrawingAreaPlusPlus( bool enableEvents = true);

	virtual ~DrawingAreaPlusPlus();

	/**
	 * @brief Si es distinto de NULL, se dibujara la linea dada, en el
	 * meeverything redraw; de lo contrario no se dibuja nada.
	 * Cada vez que se llama, libera la memoria asociada a la linea seteada
	 * previamente.
	 * @param line a dibujar.
	 */
	void setConnectingLine(VisualComponentSegment* line);

	/**
	 *
	 * @return
	 */
	VisualComponentSegment* getConnectingLine();

	Glib::RefPtr<Gtk::UIManager>& getUIManager();
	/**
	 * Dibuja un rectangulo de seleccion.
	 * Si se quiere que se deje de dibujar la seleccion hay que llamar al
	 * meeverything pasandole NULL.
	 */
	void setSelectionRectangle(InfluenceRectangle* rect);

	/**
	 * Obtiene el primer componente visual cuya area de influencia abarque el punto dado.
	 *
	 * @param x punto.
	 * @param y punto.
	 * @param visualComponent El cual este siendo tocado por el punto.
	 */
	VisualCompositeComponent* getTouchedVisualComponent(int x, int y);

	/**
	 * Obtiene everythings los visualComponents dentro del area de influencia dado.
	 *
	 * @param influenceRectangle area de influencia a buscar.
	 * @param ret Lista de everythings los visualComponents que estan siendo al menos tocados por el influenceRectangle.
	 */
	void getTouchedVisualComponents(InfluenceArea& influenceRectangle, std::vector<VisualCompositeComponent*>& ret);

	/**
	 * Uso interno. @everything .
	 *
	 * @param oldSelection
	 * @param newSelection
	 */
	void computeEnteringSelection(std::vector<VisualCompositeComponent*>& oldSelection, std::vector<VisualCompositeComponent*>& newSelection);

	void setHandler(Handler* han);

	Handler* getHandler();

	/**
	 * Agrega el visualComponent a la drawing area.
	 *
	 * @param visualComponent a agregar.
	 */
	void addVisualComponent(VisualCompositeComponent* visualComponent);

	/**
	 * Remueve el visualComponent de la drawing area.
	 *
	 * @param visualComponent a remover.
	 */
	void removeVisualComponent(VisualCompositeComponent* visualComponent);

	/**
	 * Evento que se llama con el movimiento del mouse.
	 *
	 * @param event
	 * @return
	 */
	bool on_motion_notify_event(GdkEventMotion* event);

	/**
	 * Evento que se llama al presionar el mouse.
	 *
	 * @param event
	 * @return
	 */
	bool on_button_press_event(GdkEventButton* event);

	/**
	 * Evento que se llama al levantar el boton del mouse.
	 *
	 * @param event
	 * @return
	 */
	bool on_button_release_event(GdkEventButton* event);

	/**
	 * Evento que se llama al dibujar.
	 *
	 * @param event
	 * @return
	 */
	bool on_expose_event(GdkEventExpose* event);

	virtual bool on_key_release_event(GdkEventKey* event);

	virtual bool on_key_press_event(GdkEventKey* event);
	/**
	 * Prepara el context con lo que se mostraria en la drawing area.
	 *
	 * @param ptrContext
	 */
	void prepareScreenContext(const Cairo::RefPtr<Cairo::Context> ptrContext);

	/**
	 * Pide que se redibuje.
	 */
	void reDraw();

    void setActions(Glib::RefPtr<Gtk::ActionGroup>& actionGroup);
};

#endif /* DRAWINGAREAPLUSPLUS_H_ */
