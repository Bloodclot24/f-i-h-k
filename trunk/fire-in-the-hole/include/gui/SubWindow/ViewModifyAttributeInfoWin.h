#ifndef VIEWMODIFYATTRIBUTEINFOWIN_H_
#define VIEWMODIFYATTRIBUTEINFOWIN_H_

#include "model/Component.h"
#include "gtkmm/dialog.h"
#include "gtkmm/frame.h"
#include "gtkmm/entry.h"
#include "gtkmm/label.h"
#include "gtkmm/box.h"

/**
 * @brief esta ventana despliega las propiedades del componente con el cual
 * fue creada (nombre y tipo).
 */

class ViewModifyAttributeInfoWin : public Gtk::Dialog {
public:
	ViewModifyAttributeInfoWin(Component* );
	virtual ~ViewModifyAttributeInfoWin();
	virtual int run();

private:
	Gtk::Frame m_mainFrame ;
	Gtk::Label m_componentNameLabel, m_typeLabel, m_title;
	Gtk::Entry m_typeEntry, m_componentNameEntry;
	Gtk::HBox m_typeHbox, m_componentNameHbox;
	Gtk::VBox m_mainbox;
	Gtk::RadioButton::Group m_radio, m_radio1;
	Gtk::RadioButton m_radioButton1,m_radioButton3, m_radioButton5;
	Gtk::CheckButton m_radioButton2, m_radioButton4, m_radioButton6;
	Gtk::HBox m_radioButton1Hbox, m_radioButton2Hbox, m_radioButton4Hbox;
	Component* m_component;
};

#endif /* VIEWMODIFYATTRIBUTEINFOWIN_H_ */
