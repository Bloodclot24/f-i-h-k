#ifndef HANDLERCONNECTCOMPONENTS_H_
#define HANDLERCONNECTCOMPONENTS_H_

#include "Handler.h"

class HandlerConnectComponents: public Handler {

public:

	/**
	 * @param
	 * @param es el conector sobre el cual se clickeo y se quiere establecer
	 * una conexion.
	 */
	HandlerConnectComponents(DrawingAreaPlusPlus* drawArea, VisualComponentConector* conector);

	virtual ~HandlerConnectComponents();

	/**
	 * @brief va dibujando la linea de la conexion.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent);

	/**
	 * trata de conectar el conector anterior con el touchedComponent
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

private:
	//conector sobre el que se presiono
	VisualComponentConector* m_conector;
	VisualComponentConector* m_destinyConnector;

};

#endif /* HANDLERCONNECTCOMPONENTS_H_ */
