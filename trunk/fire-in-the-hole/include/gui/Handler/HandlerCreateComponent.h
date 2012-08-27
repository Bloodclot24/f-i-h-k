#ifndef HANDLERCREATECOMPONENT_H_
#define HANDLERCREATECOMPONENT_H_

#include "gui/Handler/Handler.h"

class HandlerCreateComponent : public Handler {

public:

	HandlerCreateComponent(DrawingAreaPlusPlus* drawArea, VisualCompositeComponent* comp);

	virtual ~HandlerCreateComponent();

	/**
	 * @brief va modificando la posicion del elemento creado, y redibujando la pantalla.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent);

	virtual void on_left_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	/**
	 * deja el componente que se venia arrastrando y pasa al handler default.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

private:
	VisualCompositeComponent* m_vComponent;

	void addComponent();
};

#endif /* HANDLERCREATECOMPONENT_H_ */
