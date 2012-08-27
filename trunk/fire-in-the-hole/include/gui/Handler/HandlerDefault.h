#ifndef HANDLERDEFAULT_H_
#define HANDLERDEFAULT_H_

#include "Handler.h"

class HandlerDefault: public Handler {
public:
	HandlerDefault(DrawingAreaPlusPlus* drawArea);

	virtual ~HandlerDefault();

	/**
	 * @brief de acuerdo sobre que o donde se clickeo crea un handler selected o un connect components
	 * o un handlear create selection o un edit segments.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_left_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	/**
	 * @brief dependiendo de donde se clickeo, puede crear un handler selected si se hizo
	 * click sobre un componente, o pintar de diferente color algun conector si es que
	 * se esta pasando por un lugar donde se pueda clickear para hacer una conexion(conector).
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_right_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	/**
	 * @brief sertea en selected los componentes sobre los que pasa.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent);

private:
	VisualComponent* m_lastTouched;
	VisualCompositeComponent* m_lastComponentTouched;

};

#endif /* HANDLERDEFAULT_H_ */
