#ifndef HANDLERSELECTED_H_
#define HANDLERSELECTED_H_

#include "gui/Handler/Handler.h"
#include <gtkmm-2.4/gtkmm/menu.h>


class HandlerSelected : public Handler {

public:

	HandlerSelected( DrawingAreaPlusPlus* drawArea, std::vector< VisualCompositeComponent* >*, bool multipleSelection = false);

	virtual ~HandlerSelected();

	/**
	 * @brief de acuerdo a si se esta copiando cortando o moviendo o no, mueve
	 * los componentes de la seleccion.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent);

	/**
	 *@brief de acuerdo al estado anterior del handler puede crear un handler
	 * de edicion de segmentos o uno de crear seleccion o uno de conectar.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_left_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	/**
	 * deja el estado del handler en no clickeado.( m_clicked = false).
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	/**
	 * @brief si se presiono delete borra la seleccion.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_key_press_event(GdkEventKey* event, VisualCompositeComponent* touchedComponent);

	/**
	 * @brief despliega el popmenu de opciones sobre la seleccion, o sobre el componente sobre el
	 * que se clickeo.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_right_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	void deleteSelection();

	void showProperties();

	void copy();

	void cut();

	void createSubdiagram();

	void setDarea(DrawingAreaPlusPlus* drawArea) {
		m_drawArea = drawArea;
	}

	std::vector< VisualCompositeComponent* >* getSelection() {
		return m_selection;
	}

private:
	std::vector< VisualCompositeComponent* >* m_selection;
	bool m_clicked;

	std::vector< VisualCompositeComponent* >* duplicateSelection();

	bool onlyOneComponentSelected();

	void eraseSelection();

	void selectAll(bool select);

	void computeDifference(int &x, int &y, int mouseDownX, int mouseDownY);

	bool m_firstTime;
	int m_lastX, m_lastY;

	Gtk::Menu* m_popup;
	bool m_popupCalledBefore;

	VisualComponentConector* obtainCopyConnector(VisualComponentConector* connector,
		std::map< VisualCompositeComponent* , VisualCompositeComponent* > & index);
};

#endif /* HANDLERSELECTED_H_ */
