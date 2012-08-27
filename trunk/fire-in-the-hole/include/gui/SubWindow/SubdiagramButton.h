#ifndef BOTONSUBDIAGRAM_H_
#define BOTONSUBDIAGRAM_H_

#define NOMBRE_SUBDIAGRAM "Subdiagram"

#include <gtkmm/messagedialog.h>
#include <gtkmm/button.h>
#include <glibmm.h>
#include "gui/Tabs.h"
#include "utils/Settings.h"

class SubdiagramButton: public Gtk::Button {
private:
	std::string m_xml;
	Tabs* m_tabs;
	Gtk::Image* m_image;

public:
	SubdiagramButton() {
		set_label(NOMBRE_SUBDIAGRAM);
		add_events(Gdk::BUTTON_PRESS_MASK);
		m_image = new Gtk::Image(Settings::getInstance().getValue("ImagesPath") + "SUBDIAGRAMA.png");
		m_image->show();
		set_image_position(Gtk::POS_TOP);
		set_image(*m_image);
	}
	virtual ~SubdiagramButton() {
		delete m_image;
	}

	virtual bool on_button_press_event(GdkEventButton* event);

	void setTabs(Tabs* t);
};

#endif /* BOTONSUBDIAGRAM_H_ */
