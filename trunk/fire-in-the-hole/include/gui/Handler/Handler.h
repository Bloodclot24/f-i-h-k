#ifndef HANDLER_H_
#define HANDLER_H_

#include <gtkmm/viewport.h>
#include "gui/VisualComponents/VisualCompositeComponent.h"
#include <gdkmm-2.4/gdkmm/event.h>

#define ESC 65307
#define DELETE 65535

class DrawingAreaPlusPlus;

class Handler {
public:

	Handler(DrawingAreaPlusPlus* drawArea);

	virtual ~Handler();

	virtual void on_motion_notify_event(GdkEventMotion* event, VisualCompositeComponent* touchedComponent);

	virtual void on_left_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	virtual void on_left_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	virtual void on_right_click_release_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

	virtual void on_key_release_event(GdkEventKey* event, VisualCompositeComponent* touchedComponent);

	virtual void on_key_press_event(GdkEventKey* event, VisualCompositeComponent* touchedComponent);

	virtual void on_right_click_press_event(GdkEventButton* event, VisualCompositeComponent* touchedComponent);

protected:
	DrawingAreaPlusPlus* m_drawArea;
};

#endif /* HANDLER_H_ */
