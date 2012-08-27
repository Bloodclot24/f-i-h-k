#ifndef HANDLEREDITSEGMENTS_H_
#define HANDLEREDITSEGMENTS_H_

#include "gui/Handler/Handler.h"
#include "gui/VisualComponents/VisualComponentSegment.h"

class HandlerEditSegments : public Handler {
public:

	HandlerEditSegments( DrawingAreaPlusPlus* drawArea, VisualComponentVia* via, VisualComponentSegment* segment);

	virtual ~HandlerEditSegments();

	/**
	 * @brief va cambiando los puntos de los segmentos y redibujandolos de acuerdo
	 * a la posicion del cursor y el m_segment.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent);

	/**
	 * @brief habilita el handler default en la drawing area.
	 * @param event
	 * @param touchedComponent
	 */
	virtual void on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

private:
	VisualComponentVia* m_via;
	VisualComponentSegment* m_segment;

	void creatSegments();

};

#endif /* HANDLEREDITSEGMENTS_H_ */
