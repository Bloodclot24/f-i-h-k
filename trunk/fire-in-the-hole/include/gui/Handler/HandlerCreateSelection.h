#ifndef HANDLERCREATESELECTION_H_
#define HANDLERCREATESELECTION_H_

#include "gui/Handler/Handler.h"

class HandlerCreateSelection : public Handler {

public:

	HandlerCreateSelection( DrawingAreaPlusPlus* drawArea, int mouseX, int mouseY);

	virtual ~HandlerCreateSelection();

	/**
	 * @brief llama al dbujar del cuadro de seleccion de la drawing area.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent);

	/**
	 * @brief obtiene todos los objetos que quedaron incluidos en el area de seleccion
	 * y crea un handler selected pasandole como parametros a estos.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

private:
	int m_mouseX, m_mouseY;
};

#endif /* HANDLERCREATESELECTION_H_ */
